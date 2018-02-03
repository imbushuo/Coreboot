/*
 * This file is part of the coreboot project.
 *
 * Copyright 2018 Andre Heider <a.heider@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <boot_device.h>
#include <string.h>
#include <symbols.h>

#include "cbfs_switch.h"

#define UINT32TOBUF(val, x, o) \
	do { \
		x[o + 0] = (val >> 24) & 0xff; \
		x[o + 1] = (val >> 16) & 0xff; \
		x[o + 2] = (val >> 8) & 0xff; \
		x[o + 3] = val & 0xff; \
	} while (0);

extern u8 _usb_bounce[];
extern u8 _eusb_bounce[];
#define _usb_bounce_size (_eusb_bounce - _usb_bounce)

extern u8 _rom_copy[];
extern u8 _erom_copy[];
#define _rom_copy_size (_erom_copy - _rom_copy)

typedef struct {
	char is_usb3;
	char init_hw_done;
	char init_proto_done;
	char unk0;

	int (*init_hw)(void);
	int (*init_proto)(void);

	void *ep1_out;
	void *ep1_out_get_len_proc_ep0;
	void (*ep1_out_imm)(void *buffer, uint32_t size, uint32_t *num_xfer);

	void *ep1_in;
	void *ep1_in_get_len_proc_ep0;
	int (*ep1_in_imm)(void *buffer, uint32_t size, uint32_t *num_xfer);

	void *ep0_stall;
} rcm_transport_t;

static const rcm_transport_t *rcm_transport = (rcm_transport_t *)0x40003114;

static u32 rom_recvbuf(void *buffer, u32 size) {
	u32 num_xfer;
	rcm_transport->ep1_out_imm(buffer, size, &num_xfer);
	return num_xfer;
}

static u32 rom_sendbuf(void *buffer, u32 size) {
	u32 num_xfer;
	rcm_transport->ep1_in_imm(buffer, size, &num_xfer);
	return num_xfer;
}

static ssize_t usb_readat(const struct region_device *rd, void *b,
				size_t offset, size_t size)
{
	size_t left = size;
	size_t chunk;

	UINT32TOBUF(offset, _usb_bounce, 0);
	UINT32TOBUF(size, _usb_bounce, 4);
	rom_sendbuf(_usb_bounce, 8);

	while (left > 0) {
		chunk = left;
		if (chunk > _usb_bounce_size)
			chunk = _usb_bounce_size;

		chunk = rom_recvbuf(_usb_bounce, chunk);
		memcpy(b, _usb_bounce, chunk);

		b += chunk;
		left -= chunk;
	}

	return size - left;
}

static const struct region_device_ops usb_ops = {
	.mmap = mmap_helper_rdev_mmap,
	.munmap = mmap_helper_rdev_munmap,
	.readat = usb_readat,
}
;
static struct mmap_helper_region_device mdev_usb =
	MMAP_HELPER_REGION_INIT(&usb_ops, 0, CONFIG_ROM_SIZE);

static struct mem_region_device mdev_sdram =
	MEM_REGION_DEV_RO_INIT(_rom_copy, CONFIG_ROM_SIZE);

#if ENV_RAMSTAGE
static bool rom_in_sdram = true;
#else
static bool rom_in_sdram = false;
#endif

void cbfs_switch_to_sdram(void)
{
	usb_readat(NULL, _rom_copy, 0, CONFIG_ROM_SIZE);

	memset(_usb_bounce, 0, 8);
	rom_sendbuf(_usb_bounce, 8);

	rom_in_sdram = true;
}

const struct region_device *boot_device_ro(void)
{
	if (rom_in_sdram)
		return &mdev_sdram.rdev;

	return &mdev_usb.rdev;
}

void boot_device_init(void)
{
	void *cache;
	size_t size;

	if (ENV_ROMSTAGE) {
		cache = _postram_cbfs_cache;
		size = _postram_cbfs_cache_size;
	} else {
		cache = _cbfs_cache;
		size = _cbfs_cache_size;
	}

	mmap_helper_device_init(&mdev_usb, cache, size);
}
