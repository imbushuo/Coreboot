/*
 * This file is part of the coreboot project.
 *
 * Copyright 2018 Andre Heider <a.heider@gmail.com>
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

#include <console/console.h>
#include <delay.h>
#include <device/i2c_simple.h>
#include <soc/addressmap.h>
#include <soc/clock.h>
#include <soc/funitcfg.h>
#include <soc/nvidia/tegra/i2c.h>
#include <soc/padconfig.h>
#include <soc/romstage.h>
#include <string.h>

#include "cbfs.h"
#include "gpio.h"
#include "pmic.h"
#include "display.h"
#include "timer.h"

#if 0
static const struct pad_config padcfgs[] = {
	/* AP_SYS_RESET_L - active low*/
	PAD_CFG_GPIO_OUT1(SDMMC1_DAT0, PINMUX_PULL_UP),
	/* WP_L - active low */
	PAD_CFG_GPIO_INPUT(GPIO_PK2, PINMUX_PULL_NONE),
	/* BTN_AP_PWR_L - active low */
	PAD_CFG_GPIO_INPUT(BUTTON_POWER_ON, PINMUX_PULL_UP),
	/* BTN_AP_VOLD_L - active low */
	PAD_CFG_GPIO_INPUT(BUTTON_VOL_DOWN, PINMUX_PULL_UP),
	/* BTN_AP_VOLU_L - active low */
	PAD_CFG_GPIO_INPUT(SDMMC1_DAT1, PINMUX_PULL_UP),
};
#endif

void romstage_mainboard_init(void)
{
	//soc_configure_pads(padcfgs, ARRAY_SIZE(padcfgs));

	printk(BIOS_INFO, "Switching to SDRAM backed CBFS\n");
	cbfs_switch_to_sdram();

	display_init();
	display_enable_backlight(1);

	// Early prep
	memset((void*) 0xc0000000, (unsigned char) 0xff, 0x480000);
	u32* lfb_base = display_init_framebuffer();
    u32* fbsq_base = lfb_base;

	for (int i = 0; i < 720; i++)
    {
        for (int j = 0; j < 900; j++)
        {
            *fbsq_base = CYAN;
            fbsq_base++;
        }
    }

	sleep(35000);
}

void mainboard_configure_pmc(void)
{
}

void mainboard_enable_vdd_cpu(void)
{
	/* VDD_CPU is already enabled in bootblock. */
}
