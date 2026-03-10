// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2013-2016, Linux Foundation. All rights reserved.
 * Copyright (C) 2023-2024 Linaro Limited
 * Authors:
 * - Bhupesh Sharma <bhupesh.sharma@linaro.org>
 * - Neil Armstrong <neil.armstrong@linaro.org>
 *
 * Based on Linux driver
 */

#include <asm/io.h>
#include <clk.h>
#include <dm.h>
#include <dm/device_compat.h>
#include <generic-phy.h>
#include <ufs.h>
#include <asm/gpio.h>
#include <interconnect.h>

#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/err.h>

#include "ufs.h"

static struct ufs_hba_ops ufs_qemu_hba_ops = { };

static int ufs_qemu_probe(struct udevice *dev)
{
	int ret;

    printf("enter in ufs_qemu_probe !!!\n\n");

	ret = ufshcd_probe(dev, &ufs_qemu_hba_ops);
	if (ret) {
		dev_err(dev, "ufshcd_probe() failed, ret:%d\n", ret);
		return ret;
	}

	return 0;
}

static const struct udevice_id ufs_qemu_ids[] = {
	{ .compatible = "qemu,ufshc" },
	{},
};

U_BOOT_DRIVER(qemu_ufshcd) = {
	.name		= "qemu-ufshcd",
	.id		= UCLASS_UFS,
	.of_match	= ufs_qemu_ids,
	.probe		= ufs_qemu_probe,
};
