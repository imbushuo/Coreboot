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

//Clock config.
static const cfg_op_t _display_config_1[4] = {
	{0x4E, 0x40000000}, //CLK_RST_CONTROLLER_CLK_SOURCE_DISP1
	{0x34, 0x4830A001}, //CLK_RST_CONTROLLER_PLLD_BASE
	{0x36, 0x20}, //CLK_RST_CONTROLLER_PLLD_MISC1
	{0x37, 0x2D0AAA} //CLK_RST_CONTROLLER_PLLD_MISC
};

//Display A config.
static const cfg_op_t _display_config_2[94] = {
	{0x40, 0},
	{DC_CMD_STATE_CONTROL, 0x100},
	{DC_CMD_STATE_CONTROL, 1},
	{0x43, 0x54},
	{DC_CMD_STATE_CONTROL, 0x100},
	{DC_CMD_STATE_CONTROL, 1},
	{0x42, 0x10},
	{0x42, 0x20},
	{0x42, 0x40},
	{0x480, 0},
	{0x403, 0},
	{0x404, 0},
	{0x36, 0x50155},
	{1, 0x100},
	{0x28, 0x109},
	{DC_CMD_STATE_CONTROL, 0xF00},
	{DC_CMD_STATE_CONTROL, 0xF},
	{0x40, 0},
	{0x42, 0x10},
	{0x700, 0},
	{0x42, 0x10},
	{0x70E, 0},
	{0x700, 0},
	{0x42, 0x10},
	{0x42, 0x10},
	{0x611, 0xF0},
	{0x612, 0x12A},
	{0x613, 0},
	{0x614, 0x198},
	{0x615, 0x39B},
	{0x616, 0x32F},
	{0x617, 0x204},
	{0x618, 0},
	{0x42, 0x20},
	{0x700, 0},
	{0x42, 0x20},
	{0x70E, 0},
	{0x700, 0},
	{0x42, 0x20},
	{0x42, 0x20},
	{0x611, 0xF0},
	{0x612, 0x12A},
	{0x613, 0},
	{0x614, 0x198},
	{0x615, 0x39B},
	{0x616, 0x32F},
	{0x617, 0x204},
	{0x618, 0},
	{0x42, 0x40},
	{0x700, 0},
	{0x42, 0x40},
	{0x70E, 0},
	{0x700, 0},
	{0x42, 0x40},
	{0x42, 0x40},
	{0x611, 0xF0},
	{0x612, 0x12A},
	{0x613, 0},
	{0x614, 0x198},
	{0x615, 0x39B},
	{0x616, 0x32F},
	{0x617, 0x204},
	{0x618, 0},
	{0x42, 0x10},
	{0x700, 0},
	{0x42, 0x20},
	{0x700, 0},
	{0x42, 0x40},
	{0x700, 0},
	{0x430, 8},
	{0x42F, 0},
	{0x307, 0x1000000},
	{0x309, 0},
	{0x4E4, 0},
	{0x300, 0},
	{DC_CMD_STATE_CONTROL, 0xF00},
	{DC_CMD_STATE_CONTROL, 0xF},
	{0x42, 0x10},
	{0x716, 0x10000FF},
	{0x42, 0x20},
	{0x716, 0x10000FF},
	{0x42, 0x40},
	{0x716, 0x10000FF},
	{0x31, 0},
	{0x42, 0x10},
	{0x700, 0},
	{0x42, 0x20},
	{0x700, 0},
	{0x42, 0x40},
	{0x700, 0},
	{0x402, 0},
	{0x32, 0},
	{DC_CMD_STATE_CONTROL, 0xF00},
	{DC_CMD_STATE_CONTROL, 0xF}
};

//DSI config.
static const cfg_op_t _display_config_3[60] = { 
	{0xA, 0},
	{0xC, 0},
	{0xD, 0},
	{0xE, 0},
	{0x1B, 0},
	{0x1C, 0},
	{0x1D, 0},
	{0x1E, 0},
	{0x33, 0},
	{0x23, 0},
	{0x25, 0},
	{0x27, 0},
	{0x29, 0},
	{0x2B, 0},
	{0x2D, 0},
	{0x24, 0},
	{0x26, 0},
	{0x28, 0},
	{0x2A, 0},
	{0x2C, 0},
	{0x2E, 0},
	{0x10, 0},
	{0x4C, 0},
	{0x11, 0x18},
	{0x12, 0x1E0},
	{0x13, 0},
	{0x1A, 0},
	{0x34, 0},
	{0x35, 0},
	{0x36, 0},
	{0x37, 0},
	{0x4F, 0},
	{0x3C, 0x6070601},
	{0x3D, 0x40A0E05},
	{0x3E, 0x30109},
	{0x3F, 0x190A14},
	{0x44, 0x2000FFFF},
	{0x45, 0x7652000},
	{0x46, 0},
	{0x4B, 0},
	{DSI_DSI_POWER_CONTROL, 1},
	{DSI_DSI_POWER_CONTROL, 1},
	{DSI_DSI_POWER_CONTROL, 0},
	{DSI_DSI_POWER_CONTROL, 0},
	{0x4F, 0},
	{0x3C, 0x6070601},
	{0x3D, 0x40A0E05},
	{0x3E, 0x30118},
	{0x3F, 0x190A14},
	{0x44, 0x2000FFFF},
	{0x45, 0x13432000},
	{0x46, 0},
	{0xF, 0x102003},
	{0x10, 0x31},
	{DSI_DSI_POWER_CONTROL, 1},
	{DSI_DSI_POWER_CONTROL, 1},
	{0x12, 0x40},
	{0x13, 0},
	{0x14, 0},
	{0x1A, 0}
};

//DSI config (if ver == 0x10).
static const cfg_op_t _display_config_4[43] = {
	{DSI_DSI_WR_DATA, 0x439},
	{DSI_DSI_WR_DATA, 0x9483FFB9},
	{DSI_DSI_TRIGGER, 2},
	{DSI_DSI_WR_DATA, 0xBD15},
	{DSI_DSI_TRIGGER, 2},
	{DSI_DSI_WR_DATA, 0x1939},
	{DSI_DSI_WR_DATA, 0xAAAAAAD8},
	{DSI_DSI_WR_DATA, 0xAAAAAAEB},
	{DSI_DSI_WR_DATA, 0xAAEBAAAA},
	{DSI_DSI_WR_DATA, 0xAAAAAAAA},
	{DSI_DSI_WR_DATA, 0xAAAAAAEB},
	{DSI_DSI_WR_DATA, 0xAAEBAAAA},
	{DSI_DSI_WR_DATA, 0xAA},
	{DSI_DSI_TRIGGER, 2},
	{DSI_DSI_WR_DATA, 0x1BD15},
	{DSI_DSI_TRIGGER, 2},
	{DSI_DSI_WR_DATA, 0x2739},
	{DSI_DSI_WR_DATA, 0xFFFFFFD8},
	{DSI_DSI_WR_DATA, 0xFFFFFFFF},
	{DSI_DSI_WR_DATA, 0xFFFFFFFF},
	{DSI_DSI_WR_DATA, 0xFFFFFFFF},
	{DSI_DSI_WR_DATA, 0xFFFFFFFF},
	{DSI_DSI_WR_DATA, 0xFFFFFFFF},
	{DSI_DSI_WR_DATA, 0xFFFFFFFF},
	{DSI_DSI_WR_DATA, 0xFFFFFFFF},
	{DSI_DSI_WR_DATA, 0xFFFFFFFF},
	{DSI_DSI_WR_DATA, 0xFFFFFF},
	{DSI_DSI_TRIGGER, 2},
	{DSI_DSI_WR_DATA, 0x2BD15},
	{DSI_DSI_TRIGGER, 2},
	{DSI_DSI_WR_DATA, 0xF39},
	{DSI_DSI_WR_DATA, 0xFFFFFFD8},
	{DSI_DSI_WR_DATA, 0xFFFFFFFF},
	{DSI_DSI_WR_DATA, 0xFFFFFFFF},
	{DSI_DSI_WR_DATA, 0xFFFFFF},
	{DSI_DSI_TRIGGER, 2},
	{DSI_DSI_WR_DATA, 0xBD15},
	{DSI_DSI_TRIGGER, 2},
	{DSI_DSI_WR_DATA, 0x6D915},
	{DSI_DSI_TRIGGER, 2},
	{DSI_DSI_WR_DATA, 0x439},
	{DSI_DSI_WR_DATA, 0xB9},
	{DSI_DSI_TRIGGER, 2}
};

//DSI config.
static const cfg_op_t _display_config_5[21] = {
	{0x4F, 0},
	{0x3C, 0x6070601},
	{0x3D, 0x40A0E05},
	{0x3E, 0x30172},
	{0x3F, 0x190A14},
	{0x44, 0x20000A40},
	{0x45, 0x5A2F2000},
	{0x46, 0},
	{0x23, 0x40000208},
	{0x27, 0x40000308},
	{0x2B, 0x40000308},
	{0x25, 0x40000308},
	{0x29, 0x3F3B2B08},
	{0x2A, 0x2CC},
	{0x2D, 0x3F3B2B08},
	{0x2E, 0x2CC},
	{0x34, 0xCE0000},
	{0x35, 0x87001A2},
	{0x36, 0x190},
	{0x37, 0x190},
	{0xF, 0},
};

//Clock config.
static const cfg_op_t _display_config_6[3] = {
	{0x34, 0x4810C001}, //CLK_RST_CONTROLLER_PLLD_BASE
	{0x36, 0x20}, //CLK_RST_CONTROLLER_PLLD_MISC1
	{0x37, 0x2DFC00} //CLK_RST_CONTROLLER_PLLD_MISC
};

//DSI config.
static const cfg_op_t _display_config_7[10] = {
	{0x13, 0},
	{0x10, 0},
	{0x11, 6},
	{0x12, 0x1E0},
	{DSI_DSI_POWER_CONTROL, 1},
	{0x10, 0x103032},
	{0xF, 0x33},
	{0x10, 0x103032},
	{0xF, 3},
	{0xF, 0x23}
};

//MIPI CAL config.
static const cfg_op_t _display_config_8[6] = {
	{0x18, 0},
	{2, 0xF3F10000},
	{0x16, 1},
	{0x18, 0},
	{0x18, 0x10010},
	{0x17, 0x300}
};

//DSI config.
static const cfg_op_t _display_config_9[4] = {
	{0x4F, 0},
	{0x50, 0},
	{0x51, 0x3333},
	{0x52, 0}
};

//MIPI CAL config.
static const cfg_op_t _display_config_10[16] = {
	{0xE, 0x200200},
	{0xF, 0x200200},
	{0x19, 0x200002},
	{0x1A, 0x200002},
	{5, 0},
	{6, 0},
	{7, 0},
	{8, 0},
	{9, 0},
	{0xA, 0},
	{0x10, 0},
	{0x11, 0},
	{0x1A, 0},
	{0x1C, 0},
	{0x1D, 0},
	{0, 0x2A000001}
};

//Display A config.
static const cfg_op_t _display_config_11[113] = {
	{0x40, 0},
	{0x42, 0x10},
	{0x700, 0},
	{0x42, 0x10},
	{0x70E, 0},
	{0x700, 0},
	{0x42, 0x10},
	{0x42, 0x10},
	{0x611, 0xF0},
	{0x612, 0x12A},
	{0x613, 0},
	{0x614, 0x198},
	{0x615, 0x39B},
	{0x616, 0x32F},
	{0x617, 0x204},
	{0x618, 0},
	{0x42, 0x20},
	{0x700, 0},
	{0x42, 0x20},
	{0x70E, 0},
	{0x700, 0},
	{0x42, 0x20},
	{0x42, 0x20},
	{0x611, 0xF0},
	{0x612, 0x12A},
	{0x613, 0},
	{0x614, 0x198},
	{0x615, 0x39B},
	{0x616, 0x32F},
	{0x617, 0x204},
	{0x618, 0},
	{0x42, 0x40},
	{0x700, 0},
	{0x42, 0x40},
	{0x70E, 0},
	{0x700, 0},
	{0x42, 0x40},
	{0x42, 0x40},
	{0x611, 0xF0},
	{0x612, 0x12A},
	{0x613, 0},
	{0x614, 0x198},
	{0x615, 0x39B},
	{0x616, 0x32F},
	{0x617, 0x204},
	{0x618, 0},
	{0x42, 0x10},
	{0x700, 0},
	{0x42, 0x20},
	{0x700, 0},
	{0x42, 0x40},
	{0x700, 0},
	{0x430, 8},
	{0x42F, 0},
	{0x307, 0x1000000},
	{0x309, 0},
	{0x4E4, 0},
	{0x300, 0},
	{DC_CMD_STATE_CONTROL, 0xF00},
	{DC_CMD_STATE_CONTROL, 0xF},
	{0x42, 0x10},
	{0x716, 0x10000FF},
	{0x42, 0x20},
	{0x716, 0x10000FF},
	{0x42, 0x40},
	{0x716, 0x10000FF},
	{0x31, 0},
	{0x42, 0x10},
	{0x700, 0},
	{0x42, 0x20},
	{0x700, 0},
	{0x42, 0x40},
	{0x700, 0},
	{0x402, 0},
	{0x32, 0},
	{DC_CMD_STATE_CONTROL, 0xF00},
	{DC_CMD_STATE_CONTROL, 0xF},
	{0x40, 0},
	{0x405, 0},
	{0x406, 0x10000},
	{0x407, 0x10048},
	{0x408, 0x90048},
	{0x409, 0x50002D0},
	{0x40A, 0xA0088},
	{0x431, 0x10001},
	{0x303, 0},
	{0x432, 5},
	{0x42F, 0},
	{0x42E, 0},
	{0x31, 0},
	{0x42, 0x10},
	{0x700, 0},
	{0x42, 0x20},
	{0x700, 0},
	{0x42, 0x40},
	{0x700, 0},
	{0x402, 0},
	{0x32, 0x20},
	{DC_CMD_STATE_CONTROL, 0x100},
	{DC_CMD_STATE_CONTROL, 1},
	{0x40, 5},
	{0x40A, 0xA0088},
	{0x40, 0},
	{DC_CMD_STATE_CONTROL, 0x100},
	{DC_CMD_STATE_CONTROL, 1},
	{0, 0x301},
	{0, 0x301},
	{DC_CMD_STATE_CONTROL, 0x100},
	{DC_CMD_STATE_CONTROL, 1},
	{0x40, 0},
	{0x42E, 4},
	{0x430, 8},
	{0x31, 0}
};

////Display A config.
static const cfg_op_t _display_config_12[17] = {
	{0x40A, 0xA0088},
	{0x38, 0},
	{0x40, 0},
	{0x39, 0},
	{0x28, 0},
	{0x32, 0},
	{DC_CMD_STATE_CONTROL, 0x100},
	{DC_CMD_STATE_CONTROL, 1},
	{DC_CMD_STATE_CONTROL, 0x100},
	{DC_CMD_STATE_CONTROL, 1},
	{0, 0x301},
	{0, 0x301},
	{DC_CMD_STATE_CONTROL, 0x100},
	{DC_CMD_STATE_CONTROL, 1},
	{0x36, 0},
	{DC_CMD_STATE_CONTROL, 0x100},
	{DC_CMD_STATE_CONTROL, 1}
};

//DSI config.
static const cfg_op_t _display_config_13[16] = {
	{DSI_DSI_POWER_CONTROL, 0},
	{0x4F, 0},
	{0x3C, 0x6070601},
	{0x3D, 0x40A0E05},
	{0x3E, 0x30109},
	{0x3F, 0x190A14},
	{0x44, 0x2000FFFF},
	{0x45, 0x7652000},
	{0x46, 0},
	{0xF, 0x102003},
	{0x10, 0x31},
	{DSI_DSI_POWER_CONTROL, 1},
	{0x12, 0x40},
	{0x13, 0},
	{0x14, 0},
	{0x1A, 0}
};

//DSI config (if ver == 0x10).
static const cfg_op_t _display_config_14[22] = {
	{DSI_DSI_WR_DATA, 0x439},
	{DSI_DSI_WR_DATA, 0x9483FFB9},
	{DSI_DSI_TRIGGER, 2},
	{DSI_DSI_WR_DATA, 0x2139},
	{DSI_DSI_WR_DATA, 0x191919D5},
	{DSI_DSI_WR_DATA, 0x19191919},
	{DSI_DSI_WR_DATA, 0x19191919},
	{DSI_DSI_WR_DATA, 0x19191919},
	{DSI_DSI_WR_DATA, 0x19191919},
	{DSI_DSI_WR_DATA, 0x19191919},
	{DSI_DSI_WR_DATA, 0x19191919},
	{DSI_DSI_WR_DATA, 0x19191919},
	{DSI_DSI_WR_DATA, 0x19},
	{DSI_DSI_TRIGGER, 2},
	{DSI_DSI_WR_DATA, 0xB39},
	{DSI_DSI_WR_DATA, 0x4F0F41B1},
	{DSI_DSI_WR_DATA, 0xF179A433},
	{DSI_DSI_WR_DATA, 0x2D81},
	{DSI_DSI_TRIGGER, 2},
	{DSI_DSI_WR_DATA, 0x439},
	{DSI_DSI_WR_DATA, 0xB9},
	{DSI_DSI_TRIGGER, 2}
};

//Display A config.
static const cfg_op_t cfg_display_one_color[8] = {
	{DC_CMD_DISPLAY_WINDOW_HEADER, 0x10}, //Enable window A.
	{DC_X_WIN_XD_WIN_OPTIONS, 0},
	{DC_CMD_DISPLAY_WINDOW_HEADER, 0x20}, //Enable window B.
	{DC_X_WIN_XD_WIN_OPTIONS, 0},
	{DC_CMD_DISPLAY_WINDOW_HEADER, 0x40}, //Enable window C.
	{DC_X_WIN_XD_WIN_OPTIONS, 0},
	{DC_DISP_DISP_WIN_OPTIONS, 0x20000000}, //DSI_ENABLE
	{DC_CMD_DISPLAY_COMMAND, 0x20} //DISPLAY_CTRL_MODE: continuous display.
};

//Display A config.
static const cfg_op_t cfg_display_framebuffer[32] = {
	{DC_CMD_DISPLAY_WINDOW_HEADER, 0x40}, //Enable window C.
	{DC_X_WIN_XD_WIN_OPTIONS, 0},
	{DC_CMD_DISPLAY_WINDOW_HEADER, 0x20}, //Enable window B.
	{DC_X_WIN_XD_WIN_OPTIONS, 0},
	{DC_CMD_DISPLAY_WINDOW_HEADER, 0x10}, //Enable window A.
	{DC_X_WIN_XD_WIN_OPTIONS, 0},
	{DC_DISP_DISP_WIN_OPTIONS, 0x20000000}, //DSI_ENABLE
	{DC_X_WIN_XD_COLOR_DEPTH, 0xD}, //T_A8B8G8R8
	{DC_X_WIN_XD_WIN_OPTIONS, 0},
	{DC_X_WIN_XD_WIN_OPTIONS, 0},
	{DC_X_WIN_XD_POSITION, 0}, //(0,0)
	{DC_X_WIN_XD_H_INITIAL_DDA, 0},
	{DC_X_WIN_XD_V_INITIAL_DDA, 0},
	{DC_X_WIN_XD_PRESCALED_SIZE, 0x5000B40}, //Pre-scaled size: 1280x2880 bytes (= 0x500 vertical lines x 0xB40 bytes).
	{DC_X_WIN_XD_DDA_INCREMENT, 0x10001000},
	{DC_X_WIN_XD_SIZE, 0x50002D0}, //Window size: 1280x720 (= 0x500 vertical lines x 0x2D0 horizontal pixels).
	{DC_X_WIN_XD_LINE_STRIDE, 0x6000C00}, //768*2x768*4 (= 0x600 x 0xC00) bytes, see TRM for alignment requirements.
	{0x702, 0},
	{DC_X_WINBUF_XD_SURFACE_KIND, 0}, //Regular surface.
	{DC_X_WINBUF_XD_START_ADDR, 0xC0000000}, //Framebuffer address.
	{DC_X_WINBUF_XD_ADDR_H_OFFSET, 0},
	{DC_X_WINBUF_XD_ADDR_V_OFFSET, 0},
	{DC_X_WIN_XD_WIN_OPTIONS, 0},
	{DC_DISP_DISP_WIN_OPTIONS, 0x20000000}, //DSI_ENABLE
	{DC_X_WIN_XD_WIN_OPTIONS, 0},
	{DC_DISP_DISP_WIN_OPTIONS, 0x20000000}, //DSI_ENABLE
	{DC_X_WIN_XD_WIN_OPTIONS, 0},
	{DC_DISP_DISP_WIN_OPTIONS, 0x20000000}, //DSI_ENABLE
	{DC_X_WIN_XD_WIN_OPTIONS, 0x40000000}, //Enable window AD.
	{DC_CMD_DISPLAY_COMMAND, 0x20}, //DISPLAY_CTRL_MODE: continuous display.
	{DC_CMD_STATE_CONTROL, 0x300}, //General update; window A update.
	{DC_CMD_STATE_CONTROL, 3} //General activation request; window A activation request.
};
