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

#ifndef _T210_H_
#define _T210_H_

#include "types.h"

#define HOST1X_BASE ((void*) 0x50000000)
#define DISPLAY_A_BASE ((void*) 0x54200000)
#define DSI_BASE ((void*) 0x54300000)
#define VIC_BASE ((void*) 0x54340000)
#define TSEC_BASE ((void*) 0x54500000)
#define SOR1_BASE ((void*) 0x54580000)
#define PG_UP_BASE ((void*) 0x60000000)
#define TMR_BASE ((void*) 0x60005000)
#define CLOCK_BASE ((void*) 0x60006000)
#define FLOW_CTLR_BASE ((void*) 0x60007000)
#define SYSREG_BASE ((void*) 0x6000C000)
#define SB_BASE (SYSREG_BASE + 0x200)
#define GPIO_BASE ((void*) 0x6000D000)
#define GPIO_1_BASE (GPIO_BASE)
#define GPIO_2_BASE (GPIO_BASE + 0x100)
#define GPIO_3_BASE (GPIO_BASE + 0x200)
#define GPIO_4_BASE (GPIO_BASE + 0x300)
#define GPIO_5_BASE (GPIO_BASE + 0x400)
#define GPIO_6_BASE (GPIO_BASE + 0x500)
#define GPIO_7_BASE (GPIO_BASE + 0x600)
#define GPIO_8_BASE (GPIO_BASE + 0x700)
#define EXCP_VEC_BASE ((void*) 0x6000F000)
#define APB_MISC_BASE ((void*) 0x70000000)
#define PINMUX_AUX_BASE ((void*) 0x70003000)
#define UART_BASE ((void*) 0x70006000)
#define PMC_BASE ((void*) 0x7000E400)
#define SYSCTR0_BASE ((void*) 0x7000F000)
#define FUSE_BASE ((void*) 0x7000F800)
#define KFUSE_BASE ((void*) 0x7000FC00)
#define SE_BASE ((void*) 0x70012000)
#define MC_BASE ((void*) 0x70019000)
#define EMC_BASE ((void*) 0x7001B000)
#define MIPI_CAL_BASE ((void*) 0x700E3000)
#define I2S_BASE ((void*) 0x702D1000)

#define _REG(base, off) *(vu32 *)((base) + (off))

#define HOST1X(off) _REG(HOST1X_BASE, off)
#define DISPLAY_A(off) _REG(DISPLAY_A_BASE, off)
#define DSI(off) _REG(DSI_BASE, off)
#define VIC(off) _REG(VIC_BASE, off)
#define TSEC(off) _REG(TSEC_BASE, off)
#define SOR1(off) _REG(SOR1_BASE, off)
#define TMR(off) _REG(TMR_BASE, off)
#define CLOCK(off) _REG(CLOCK_BASE, off)
#define FLOW_CTLR(off) _REG(FLOW_CTLR_BASE, off)
#define SYSREG(off) _REG(SYSREG_BASE, off)
#define SB(off) _REG(SB_BASE, off)
#define GPIO(off) _REG(GPIO_BASE, off)
#define GPIO_1(off) _REG(GPIO_1_BASE, off)
#define GPIO_2(off) _REG(GPIO_2_BASE, off)
#define GPIO_3(off) _REG(GPIO_3_BASE, off)
#define GPIO_4(off) _REG(GPIO_4_BASE, off)
#define GPIO_5(off) _REG(GPIO_5_BASE, off)
#define GPIO_6(off) _REG(GPIO_6_BASE, off)
#define GPIO_7(off) _REG(GPIO_7_BASE, off)
#define GPIO_8(off) _REG(GPIO_8_BASE, off)
#define EXCP_VEC(off) _REG(EXCP_VEC_BASE, off)
#define APB_MISC(off) _REG(APB_MISC_BASE, off)
#define PINMUX_AUX(off) _REG(PINMUX_AUX_BASE, off)
#define PMC(off) _REG(PMC_BASE, off)
#define SYSCTR0(off) _REG(SYSCTR0_BASE, off)
#define FUSE(off) _REG(FUSE_BASE, off)
#define KFUSE(off) _REG(KFUSE_BASE, off)
#define SE(off) _REG(SE_BASE, off)
#define MC(off) _REG(MC_BASE, off)
#define EMC(off) _REG(EMC_BASE, off)
#define MIPI_CAL(off) _REG(MIPI_CAL_BASE, off)
#define I2S(off) _REG(I2S_BASE, off)

/*! System registers. */
#define AHB_ARBITRATION_XBAR_CTRL 0xE0

/*! APB MISC registers. */
#define APB_MISC_GP_SDMMC1_CLK_LPBK_CONTROL 0x8D4
#define APB_MISC_GP_SDMMC3_CLK_LPBK_CONTROL 0x8D8
#define APB_MISC_GP_SDMMC1_PAD_CFGPADCTRL 0xA98
#define APB_MISC_GP_VGPIO_GPIO_MUX_SEL 0xB74

/*! Secure boot registers. */
#define SB_CSR 0x0
#define SB_AA64_RESET_LOW 0x30
#define SB_AA64_RESET_HIGH 0x34

/*! SYSCTR0 registers. */
#define SYSCTR0_CNTFID0 0x20

#endif
