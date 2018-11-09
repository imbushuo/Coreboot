/*
* Copyright (c) 2018 naehrwert
*
* This program is free software; you can redistribute it and/or modify it
* under the terms and conditions of the GNU General Public License,
* version 2, as published by the Free Software Foundation.
*
* This program is distributed in the hope it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _DI_H_
#define _DI_H_

#include "types.h"

/*! Display registers. */
#define _DIREG(reg) ((reg) * 4)
#define DC_CMD_DISPLAY_COMMAND 0x32
#define DC_CMD_STATE_ACCESS 0x40
#define DC_CMD_STATE_CONTROL 0x41
#define DC_CMD_DISPLAY_WINDOW_HEADER 0x42
#define DC_DISP_DISP_WIN_OPTIONS 0x402
#define DC_DISP_DISP_CLOCK_CONTROL 0x42E
#define DC_DISP_BLEND_BACKGROUND_COLOR 0x4E4
#define DC_WIN_AD_WIN_OPTIONS 0xB80
#define DC_WIN_BD_WIN_OPTIONS 0xD80
#define DC_WIN_CD_WIN_OPTIONS 0xF80

//The following registers are A/B/C shadows of the 0xB80/0xD80/0xF80 registers (see DISPLAY_WINDOW_HEADER).
#define DC_X_WIN_XD_WIN_OPTIONS 0x700
#define DC_X_WIN_XD_COLOR_DEPTH 0x703
#define DC_X_WIN_XD_POSITION 0x704
#define DC_X_WIN_XD_SIZE 0x705
#define DC_X_WIN_XD_PRESCALED_SIZE 0x706
#define DC_X_WIN_XD_H_INITIAL_DDA 0x707
#define DC_X_WIN_XD_V_INITIAL_DDA 0x708
#define DC_X_WIN_XD_DDA_INCREMENT 0x709
#define DC_X_WIN_XD_LINE_STRIDE 0x70A

//The following registers are A/B/C shadows of the 0xBC0/0xDC0/0xFC0 registers (see DISPLAY_WINDOW_HEADER).
#define DC_X_WINBUF_XD_START_ADDR 0x800
#define DC_X_WINBUF_XD_ADDR_H_OFFSET 0x806
#define DC_X_WINBUF_XD_ADDR_V_OFFSET 0x808
#define DC_X_WINBUF_XD_SURFACE_KIND 0x80B

/*! Display serial interface registers. */
#define _DSIREG(reg) ((reg) * 4)
#define DSI_DSI_RD_DATA 0x9
#define DSI_DSI_WR_DATA 0xA
#define DSI_DSI_POWER_CONTROL 0xB
#define DSI_HOST_DSI_CONTROL 0xF
#define DSI_DSI_TRIGGER 0x13
#define DSI_DSI_BTA_TIMING 0x3F
#define DSI_PAD_CONTROL 0x4B
#define DSI_DSI_VID_MODE_CONTROL 0x4E

void lcd_init(void);
void display_init(void);

/*! Init display in full 1280x720 resolution (32bpp, line stride 768, framebuffer size = 1280*768*4 bytes). */
u32 *display_init_framebuffer(void);

/*! Enable or disable the backlight. Should only be called when the screen is completely set up, to avoid flickering. */
void display_enable_backlight(u32 on);

#endif
