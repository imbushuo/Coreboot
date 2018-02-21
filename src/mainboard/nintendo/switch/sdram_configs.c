/*
 * This file is part of the coreboot project.
 *
 * Copyright 2018 Andre Heider <a.heider@gmail.com>
 * Copyright 2014 Google Inc.
 * Copyright (c) 2015, NVIDIA CORPORATION.  All rights reserved.
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

#include <arch/io.h>
#include <boardid.h>
#include <console/console.h>
#include <soc/addressmap.h>
#include <soc/sdram_configs.h>

static const struct sdram_params sdram_configs[] = {
#include "bct/sdram-nintendo-switch-0.inc"		/* ram_code = 0000 */
#include "bct/sdram-nintendo-switch-1.inc"		/* ram_code = 0001 */
#include "bct/sdram-nintendo-switch-2.inc"		/* ram_code = 0010 */
#include "bct/sdram-nintendo-switch-3.inc"		/* ram_code = 0011 */
#include "bct/sdram-nintendo-switch-4.inc"		/* ram_code = 0100 */
};

#define FUSE_BASE		((void *)TEGRA_FUSE_BASE)
#define  FUSE_RESERVED_ODM4	0x1d8

static uint32_t switch_sdram_get_id(void)
{
	return (read32(FUSE_BASE + FUSE_RESERVED_ODM4) >> 3) & 7;
}

const struct sdram_params *get_sdram_config()
{
	uint32_t id = switch_sdram_get_id();

	printk(BIOS_INFO, "Fuse SDRAM ID: %d\n", id);

	if (id >= ARRAY_SIZE(sdram_configs) ||
		sdram_configs[id].MemoryType == NvBootMemoryType_Unused) {
		die("Invalid SDRAM ID.");
	}

	return &sdram_configs[id];
}

uint32_t ram_code(void)
{
	return switch_sdram_get_id();
}
