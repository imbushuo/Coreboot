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

extern uint8_t _usb_bounce[];
extern uint8_t _eusb_bounce[];
#define _usb_bounce_size (_eusb_bounce - _usb_bounce)

extern uint8_t _rom_copy[];
extern uint8_t _erom_copy[];
#define _rom_copy_size (_erom_copy - _rom_copy)

#define BOOTROM_RCM_TRANSPORT_ADDR	0x40003114

/* The RCM struct of the BootROM */
static const struct {
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
} *rcm_transport = (void *)BOOTROM_RCM_TRANSPORT_ADDR;

static uint32_t rom_recvbuf(void *buffer, uint32_t size)
{
	uint32_t num_xfer;
	rcm_transport->ep1_out_imm(buffer, size, &num_xfer);
	return num_xfer;
}

static uint32_t rom_sendbuf(void *buffer, uint32_t size)
{
	uint32_t num_xfer;
	rcm_transport->ep1_in_imm(buffer, size, &num_xfer);
	return num_xfer;
}

static void bounce_bewrite32(uint32_t offset, uint32_t value)
{
	_usb_bounce[offset + 0] = (value >> 24) & 0xff;
	_usb_bounce[offset + 1] = (value >> 16) & 0xff;
	_usb_bounce[offset + 2] = (value >> 8) & 0xff;
	_usb_bounce[offset + 3] = value & 0xff;
}

static ssize_t usb_readat(const struct region_device *rd, void *b,
			  size_t offset, size_t size)
{
	size_t left = size;
	size_t chunk;

	bounce_bewrite32(0, offset);
	bounce_bewrite32(4, size);
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
};

static struct mmap_helper_region_device mdev_usb =
	MMAP_HELPER_REGION_INIT(&usb_ops, 0, CONFIG_ROM_SIZE);

static struct mem_region_device mdev_sdram =
	MEM_REGION_DEV_RO_INIT(_rom_copy, CONFIG_ROM_SIZE);

/* romstage start out with USB but switches to SDRAM.
 * ramstage uses SDRAM backed CBFS exclusively.
 */
#if ENV_RAMSTAGE
static bool rom_in_sdram = true;
#else
static bool rom_in_sdram = false;
#endif

void cbfs_switch_to_sdram(void)
{
	usb_readat(&mdev_usb.rdev, _rom_copy, 0, CONFIG_ROM_SIZE);

	/* Signal host with offset=0 and length=0 that we're done. */
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
