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

#include <memlayout.h>
#include <rules.h>

#include <arch/header.ld>

/*
 * Note: The BootROM uses the address range [0x4000_0000:0x4000_E000) itself,
 * so the bootblock loading address must be placed after that.
 */

SECTIONS
{
	SRAM_START(0x40000000)
#if ENV_ARM64
	STACK(0x4000E000, 3K)
#else	/* AVP gets a separate stack to avoid any chance of handoff races. */
	STACK(0x4000EC00, 3K)
#endif
	TIMESTAMP(0x4000F800, 2K)
	BOOTBLOCK(0x40010000, 28K)
	ROMSTAGE(0x40017000, 56K)
	PRERAM_CBMEM_CONSOLE(0x40025000, 8K)
	PRERAM_CBFS_CACHE(0x40027000, 92K)
	REGION(usb_bounce, 0x4003e000, 8K, 4)
	SRAM_END(0x40040000)

	DRAM_START(0x80000000)
	RAMSTAGE(0x80200000, 256K)
	POSTRAM_CBFS_CACHE(0xd0000000, 8M)
	REGION(rom_copy, 0xd0800000, CONFIG_ROM_SIZE, 4)
	TTB(0x100000000 - CONFIG_TTB_SIZE_MB * 1M, CONFIG_TTB_SIZE_MB * 1M)
}
