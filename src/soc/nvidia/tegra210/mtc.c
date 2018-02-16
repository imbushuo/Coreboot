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
#include <cbfs.h>
#include <cbmem.h>
#include <console/console.h>
#include <soc/mtc.h>
#include <soc/addressmap.h>
#include <soc/clock.h>
#include <boardid.h>
#include <string.h>

static size_t mtc_table_size;

#define MAX_MTC_TABLE_ENTRIES	20
#define MTC_TABLE_ENTRY_SIZE	4880
#define MTC_TABLE_MAX_SIZE	(MAX_MTC_TABLE_ENTRIES * MTC_TABLE_ENTRY_SIZE)

#define TRAIN_FUNC 0x5100

#define OP_SWITCH 0
#define OP_TRAIN 1

static int train_all(void *mtc)
{
	void * const mtc_entry = (void *)(((uintptr_t)mtc) + TRAIN_FUNC);
	int (*train_one)(int z, unsigned int to, unsigned int from,
					 void *table, int count, int mode) = (void *)(mtc_entry);
	char filename[32];
	int entries;
	struct region_device fh;
	struct cbfsf mtc_file;
	int ret = 0;

	snprintf(filename, sizeof(filename), "tegra_mtc_table_%d.bin", ram_code());

	if (cbfs_boot_locate(&mtc_file, filename, NULL)) {
		printk(BIOS_ERR, "MTC: Table file not found: %s\n", filename);
		return -1;
	}

	cbfs_file_data(&fh, &mtc_file);
	mtc_table_size = region_device_sz(&fh);

	entries = mtc_table_size / sizeof(tegra210_emc_table);

	printk(BIOS_ERR, "MTC: Using MTC table %s (size: 0x%lx / %d entries)\n",
		   filename, mtc_table_size, entries);

	void *cbmem_tab = cbmem_add(CBMEM_ID_MTC, mtc_table_size);
	if (cbmem_tab == NULL) {
		printk(BIOS_ERR, "MTC table allocation in cbmem failed!\n");
		return -1;
	}

	printk(BIOS_INFO, "MTC: table is at %p\n", cbmem_tab);
	printk(BIOS_INFO, "MTC: entry is at %p\n", train_one);

	ssize_t nread = rdev_readat(&fh, cbmem_tab, 0, mtc_table_size);
	if (nread != region_device_sz(&fh)) {
		printk(BIOS_ERR, "MTC bytes read (%zu) != file length(%zu)!\n",
		       nread, region_device_sz(&fh));
		goto cleanup;
	}

	tegra210_emc_table *table = cbmem_tab;

	int boot_index = 0;
	u32 reg = read32(CLK_RST_REG(clk_src_emc));
	printk(BIOS_INFO, "MTC: clk_src_emc=0x%08x\n", reg);
	for (boot_index = 0; boot_index < entries; boot_index++) {
		if (reg == table[boot_index].clk_src_emc)
			break;
	}

	if (boot_index >= entries) {
		printk(BIOS_ERR, "MTC: failed to find boot entry\n");
		goto cleanup;
	}

	printk(BIOS_INFO, "MTC: booted using entry #%d (%d kHz): %s\n", boot_index,
		table[boot_index].rate, table[boot_index].dvfs_ver);

	printk(BIOS_INFO, "MTC: running training\n");

	for (int i = 0; i < entries; i++) {
		printk(BIOS_INFO, "MTC: Training %d kHz -> %d kHz\n",
			   table[boot_index].rate, table[i].rate);
		ret = train_one(0, table[i].rate, table[boot_index].rate,
						table, entries, OP_TRAIN);
		if (ret) {
			printk(BIOS_ERR, "MTC: Training failed (%d)\n", ret);
			goto cleanup;
		} else {
			printk(BIOS_ERR, "MTC: Training OK\n");
		}
	}

	printk(BIOS_INFO, "MTC: increasing memory clocks\n");

	for (int i = boot_index + 1; i < entries; i++) {
		if (table[i].periodic_training)
			break;

		printk(BIOS_INFO, "MTC: Switching %d kHz -> %d kHz\n",
			   table[i - 1].rate, table[i].rate);
		ret = train_one(0, table[i].rate, table[i - 1].rate,
						table, entries, OP_SWITCH);
		if (ret) {
			printk(BIOS_ERR, "MTC: Switch failed (%d)\n", ret);
			goto cleanup;
		}
	}

	printk(BIOS_INFO, "MTC: successful\n");
	return 0;

cleanup:
	cbmem_entry_remove(cbmem_entry_find(CBMEM_ID_MTC));
	mtc_table_size = 0;
	return -1;
}

int tegra210_run_mtc(void)
{
	ssize_t nread;
	struct region_device fh;
	struct cbfsf mtc_file;

	void * const mtc = (void *)(uintptr_t)CONFIG_MTC_ADDRESS;
	void *dvfs_table;
	size_t (*mtc_fw)(void **dvfs_table) = (void *)mtc;

	if (cbfs_boot_locate(&mtc_file, "tegra_mtc.bin", NULL)) {
		printk(BIOS_ERR, "MTC file not found: tegra_mtc.bin\n");
		return -1;
	}

	cbfs_file_data(&fh, &mtc_file);

	/* Read MTC file into predefined region. */
	nread = rdev_readat(&fh, mtc, 0, region_device_sz(&fh));

	if (nread != region_device_sz(&fh)) {
		printk(BIOS_ERR, "MTC bytes read (%zu) != file length(%zu)!\n",
		       nread, region_device_sz(&fh));
		return -1;
	}

	printk(BIOS_INFO, "MTC: %zu bytes loaded @ %p\n", nread, mtc);

#if !IS_ENABLED(CONFIG_HAVE_MTC_TABLES)
	mtc_table_size = (*mtc_fw)(&dvfs_table);

	if ((mtc_table_size == 0) || (mtc_table_size > MTC_TABLE_MAX_SIZE)) {
		printk(BIOS_ERR, "MTC Training table size is invalid.!\n");
		return -1;
	}

	printk(BIOS_INFO, "MTC: Done. Entries size 0x%zx located at %p\n",
	       mtc_table_size, dvfs_table);

	void *cbmem_tab = cbmem_add(CBMEM_ID_MTC, mtc_table_size);
	if (cbmem_tab == NULL) {
		printk(BIOS_ERR, "MTC table allocation in cbmem failed!\n");
		return -1;
	}

	memcpy(cbmem_tab, dvfs_table, mtc_table_size);
	printk(BIOS_INFO, "MTC: Copied 0x%zx bytes from %p to %p\n",
	       mtc_table_size, dvfs_table, cbmem_tab);
#else
	return train_all(mtc);
#endif

	return 0;
}

void soc_add_mtc(struct lb_header *header)
{
	struct lb_range *mtc;
	mtc = (struct lb_range *)lb_new_record(header);
	mtc->tag = LB_TAG_MTC;
	mtc->size = sizeof(*mtc);

	mtc->range_start = (uintptr_t)cbmem_find(CBMEM_ID_MTC);
	mtc->range_size = mtc_table_size;
}
