/*
 * This file is part of the coreboot project.
 *
 * Copyright 2015 Google Inc.
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
#include <console/console.h>
#include <soc/addressmap.h>
#include <reset.h>

#define PMC_CTLR_BASE		((void *)(TEGRA_PMC_BASE))
#define PMC_CNTRL		0x000
#define  PMC_CNTRL_MAIN_RST	(1 << 4)
#define PMC_SCRATCH0		0x050
#define  PMC_SCRATCH0_MODE_RCM	(1 << 1)

void do_hard_reset(void)
{
	uint32_t val;
	
	val = read32(PMC_CTLR_BASE + PMC_SCRATCH0);
	val |= PMC_SCRATCH0_MODE_RCM;
	write32(PMC_CTLR_BASE + PMC_SCRATCH0, val);

	val = read32(PMC_CTLR_BASE + PMC_CNTRL);
	val |= PMC_CNTRL_MAIN_RST;
	write32(PMC_CTLR_BASE + PMC_CNTRL, val);
}

void die_notify(void)
{
	do_hard_reset();
}
