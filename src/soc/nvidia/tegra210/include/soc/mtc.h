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

#ifndef __SOC_NVIDIA_TEGRA210_MTC_H__
#define __SOC_NVIDIA_TEGRA210_MTC_H__

#include <boot/coreboot_tables.h>

#if IS_ENABLED(CONFIG_HAVE_MTC)

typedef struct {
        unsigned int        rev;
        char                dvfs_ver[60];
        unsigned int        rate;
        unsigned int        min_volt;
        unsigned int        gpu_min_volt;
        char                clock_src[32];
        unsigned int        clk_src_emc;
        unsigned int        needs_training;
        unsigned int        training_pattern;
        unsigned int        trained;
        unsigned int        periodic_training;
        unsigned int        trained_dram_clktree_c0d0u0;
        unsigned int        trained_dram_clktree_c0d0u1;
        unsigned int        trained_dram_clktree_c0d1u0;
        unsigned int        trained_dram_clktree_c0d1u1;
        unsigned int        trained_dram_clktree_c1d0u0;
        unsigned int        trained_dram_clktree_c1d0u1;
        unsigned int        trained_dram_clktree_c1d1u0;
        unsigned int        trained_dram_clktree_c1d1u1;
        unsigned int        current_dram_clktree_c0d0u0;
        unsigned int        current_dram_clktree_c0d0u1;
        unsigned int        current_dram_clktree_c0d1u0;
        unsigned int        current_dram_clktree_c0d1u1;
        unsigned int        current_dram_clktree_c1d0u0;
        unsigned int        current_dram_clktree_c1d0u1;
        unsigned int        current_dram_clktree_c1d1u0;
        unsigned int        current_dram_clktree_c1d1u1;
        unsigned int        run_clocks;
        unsigned int        tree_margin;
        unsigned int        num_burst;
        unsigned int        num_burst_per_ch;
        unsigned int        num_trim;
        unsigned int        num_trim_per_ch;
        unsigned int        num_mc_regs;
        unsigned int        num_up_down;
        unsigned int        vref_num;
        unsigned int        training_mod_num;
        unsigned int        dram_timing_num;

        unsigned int        burst_regs[221];
        unsigned int        burst_reg_per_ch[8];
        unsigned int        shadow_regs_ca_train[221];
        unsigned int        shadow_regs_quse_train[221];
        unsigned int        shadow_regs_rdwr_train[221];
        unsigned int        trim_regs[138];
        unsigned int        trim_perch_regs[10];

        /* Vref regs, impacted by training. */
        unsigned int        vref_perch_regs[4];

        /* DRAM timing parameters are required in some calculations. */
        unsigned int        dram_timings[5];
        unsigned int        training_mod_regs[20];
        unsigned int        save_restore_mod_regs[12];
        unsigned int        burst_mc_regs[33];
        unsigned int        la_scale_regs[24];

        unsigned int        min_mrs_wait;
        unsigned int        emc_mrw;
        unsigned int        emc_mrw2;
        unsigned int        emc_mrw3;
        unsigned int        emc_mrw4;
        unsigned int        emc_mrw9;
        unsigned int        emc_mrs;
        unsigned int        emc_emrs;
        unsigned int        emc_emrs2;
        unsigned int        emc_auto_cal_config;
        unsigned int        emc_auto_cal_config2;
        unsigned int        emc_auto_cal_config3;
        unsigned int        emc_auto_cal_config4;
        unsigned int        emc_auto_cal_config5;
        unsigned int        emc_auto_cal_config6;
        unsigned int        emc_auto_cal_config7;
        unsigned int        emc_auto_cal_config8;
        unsigned int        emc_cfg_2;
        unsigned int        emc_sel_dpd_ctrl;
        unsigned int        emc_fdpd_ctrl_cmd_no_ramp;
        unsigned int        dll_clk_src;
        unsigned int        clk_out_enb_x_0_clk_enb_emc_dll;
        unsigned int        latency;
} tegra210_emc_table;

int tegra210_run_mtc(void);
void soc_add_mtc(struct lb_header *header);

#else

static inline int tegra210_run_mtc(void) { return 0; }
static inline void soc_add_mtc(struct lb_header *header) {}

#endif /* CONFIG_HAVE_MTC */

#endif /* __SOC_NVIDIA_TEGRA210_MTC_H__ */
