/*
 * This file is part of the coreboot project.
 *
 * Copyright 2018 Andre Heider <a.heider@gmail.com>
 * Copyright 2015 Google Inc.
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
#include <arch/mmu.h>
#include <bootmode.h>
#include <boot/coreboot_tables.h>
#include <delay.h>
#include <device/device.h>
#include <device/i2c_simple.h>
#include <soc/addressmap.h>
#include <soc/clk_rst.h>
#include <soc/clock.h>
#include <soc/funitcfg.h>
#include <soc/padconfig.h>
#include <soc/nvidia/tegra/i2c.h>
#include <soc/nvidia/tegra/pingroup.h>
#include <soc/nvidia/tegra/dc.h>
#include <soc/display.h>
#include <soc/mtc.h>
#include <soc/pmc.h>
#include <soc/power.h>

#include "gpio.h"
#include "pmic.h"
#include "display.h"
#include "timer.h"

static const struct pad_config padcfgs[] = {
	PAD_CFG_GPIO_INPUT(USB_VBUS_EN1, PINMUX_PULL_NONE | PINMUX_PARKED |
			   PINMUX_INPUT_ENABLE | PINMUX_LPDR | PINMUX_IO_HV),
};

#if 0
static const struct pad_config audio_codec_pads[] = {
	/* GPIO_X1_AUD(BB3) is CODEC_RST_L and DMIC1_DAT(E1) is AUDIO_ENABLE */
	PAD_CFG_GPIO_OUT1(GPIO_X1_AUD, PINMUX_PULL_DOWN),
	PAD_CFG_GPIO_OUT1(DMIC1_DAT, PINMUX_PULL_DOWN),
};

static const struct pad_config i2s1_pad[] = {
	/* I2S1 */
	PAD_CFG_SFIO(DAP1_SCLK, PINMUX_INPUT_ENABLE, I2S1),
	PAD_CFG_SFIO(DAP1_FS, PINMUX_INPUT_ENABLE, I2S1),
	PAD_CFG_SFIO(DAP1_DOUT, PINMUX_INPUT_ENABLE, I2S1),
	PAD_CFG_SFIO(DAP1_DIN, PINMUX_INPUT_ENABLE | PINMUX_TRISTATE, I2S1),
	/* codec MCLK via AUD SFIO */
	PAD_CFG_SFIO(AUD_MCLK, PINMUX_PULL_NONE, AUD),
};

static const struct funit_cfg audio_funit[] = {
	/* We need 1.5MHz for I2S1. So we use CLK_M */
	FUNIT_CFG(I2S1, CLK_M, 1500, i2s1_pad, ARRAY_SIZE(i2s1_pad)),
};
#endif

static const struct funit_cfg funits[] = {
	FUNIT_CFG_USB(USBD),
	FUNIT_CFG(SDMMC4, PLLP, 48000, NULL, 0),
	/* I2C6 for audio, temp sensor, etc. Enable codec via GPIOs/muxes */
	//FUNIT_CFG(I2C6, PLLP, 400, audio_codec_pads, ARRAY_SIZE(audio_codec_pads)),
};

#if 0
/* Audio init: clocks and enables/resets */
static void setup_audio(void)
{
	/* Audio codec (RT5677) uses 12MHz CLK1/EXTPERIPH1 */
	clock_configure_source(extperiph1, PLLP, 12000);

	/* Configure AUD_MCLK pad drive strength */
	write32((unsigned int *)TEGRA_APB_MISC_GP_BASE + 0xF4,
		(0x10 << PINGROUP_DRVUP_SHIFT | 0x10 << PINGROUP_DRVDN_SHIFT));

	/* Set up audio peripheral clocks/muxes */
	soc_configure_funits(audio_funit, ARRAY_SIZE(audio_funit));

	/* Enable CLK1_OUT */
	clock_external_output(1);

	/*
	 * As per NVIDIA hardware team, we need to take ALL audio devices
	 * connected to AHUB (AUDIO, APB2APE, I2S, SPDIF, etc.) out of reset
	 * and clock-enabled, otherwise reading AHUB devices (in our case,
	 * I2S/APBIF/AUDIO<XBAR>) will hang.
	 */
	soc_configure_ape();
	clock_enable_audio();
}
#endif

static void configure_display_clocks(void)
{
	u32 lclks = CLK_L_HOST1X | CLK_L_DISP1;	/* dc */
	u32 hclks = CLK_H_MIPI_CAL | CLK_H_DSI;	/* mipi phy, mipi-dsi a */
	u32 uclks = CLK_U_DSIB;			/* mipi-dsi b */
	u32 xclks = CLK_X_UART_FST_MIPI_CAL;	/* uart_fst_mipi_cal */

	clock_enable_clear_reset(lclks, hclks, uclks, 0, 0, xclks, 0);

	/* Give clocks time to stabilize. */
	udelay(IO_STABILIZATION_DELAY);

	/* CLK72MHZ_CLK_SRC */
	clock_configure_source(uart_fst_mipi_cal, PLLP_OUT3, 68000);
}

static int enable_lcd_vdd(void)
{
	return 0;
}

static int configure_display_blocks(void)
{
	/* enable display related clocks */
	display_enable_backlight(1);

	return 0;
}

static void powergate_unused_partitions(void)
{
	static const uint32_t partitions[] = {
		POWER_PARTID_PCX,
		POWER_PARTID_SAX,
		POWER_PARTID_XUSBA,
		POWER_PARTID_XUSBB,
		POWER_PARTID_XUSBC,
		POWER_PARTID_NVDEC,
		POWER_PARTID_NVJPG,
		POWER_PARTID_DFD,
	};

	int i;
	for (i = 0; i < ARRAY_SIZE(partitions); i++)
		power_gate_partition(partitions[i]);
}

static void mainboard_init(device_t dev)
{
	soc_configure_pads(padcfgs, ARRAY_SIZE(padcfgs));
	soc_configure_funits(funits, ARRAY_SIZE(funits));

#if 0
	/* I2C6 bus (audio, etc.) */
	soc_configure_i2c6pad();
	i2c_init(I2C6_BUS);
	setup_audio();
#endif

	/* if panel needs to bringup */
	if (display_init_required())
		configure_display_blocks();

	powergate_unused_partitions();
}

void display_startup(device_t dev)
{
	// dsi_display_startup(dev);
}

static void mainboard_enable(device_t dev)
{
	dev->ops->init = &mainboard_init;
}

struct chip_operations mainboard_ops = {
	.name   = "switch",
	.enable_dev = mainboard_enable,
};

void lb_board(struct lb_header *header)
{
	soc_add_mtc(header);
}
