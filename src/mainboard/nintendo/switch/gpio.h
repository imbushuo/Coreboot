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

#ifndef __MAINBOARD_NINTENDO_SWITCH_CBFS_GPIO_H__
#define __MAINBOARD_NINTENDO_SWITCH_CBFS_GPIO_H__

#include <gpio.h>

enum {
	/* Warm reset */
	//AP_SYS_RESET_L		= GPIO(M5),

	/* Power button */
	//BTN_AP_PWR_L		= GPIO(X5),
	//POWER_BUTTON		= BTN_AP_PWR_L,

	/* Panel related GPIOs */
	LCD_EN			= GPIO(V1),
	LCD_RST_L		= GPIO(V2),
	EN_VDD18_LCD		= GPIO(I0),
	EN_VDD_LCD		= GPIO(I1),
};

#endif /* __MAINBOARD_NINTENDO_SWITCH_CBFS_GPIO_H__ */
