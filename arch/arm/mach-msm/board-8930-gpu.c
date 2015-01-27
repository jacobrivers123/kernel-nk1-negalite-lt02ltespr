/* Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/init.h>
#include <linux/platform_device.h>
#include <mach/kgsl.h>
#include <mach/msm_bus_board.h>
#include <mach/board.h>
#include <mach/socinfo.h>

#include "devices.h"
#include "board-8930.h"

#ifdef CONFIG_MSM_BUS_SCALING
static struct msm_bus_vectors grp3d_init_vectors[] = {
	{
		.src = MSM_BUS_MASTER_GRAPHICS_3D,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 0,
		.ib = 0,
	},
};

static struct msm_bus_vectors grp3d_low_vectors[] = {
	{
		.src = MSM_BUS_MASTER_GRAPHICS_3D,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 0,
		.ib = KGSL_CONVERT_TO_MBPS(1000),
	},
};

static struct msm_bus_vectors grp3d_nominal_vectors[] = {
	{
		.src = MSM_BUS_MASTER_GRAPHICS_3D,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 0,
		.ib = KGSL_CONVERT_TO_MBPS(2656),
	},
};

static struct msm_bus_vectors grp3d_max_vectors[] = {
	{
		.src = MSM_BUS_MASTER_GRAPHICS_3D,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 0,
#ifdef CONFIG_KGSL_GPUOC
		.ib = KGSL_CONVERT_TO_MBPS(4816),
#else
		.ib = KGSL_CONVERT_TO_MBPS(4264),
#endif
	},
};

static struct msm_bus_paths grp3d_bus_scale_usecases[] = {
	{
		ARRAY_SIZE(grp3d_init_vectors),
		grp3d_init_vectors,
	},
	{
		ARRAY_SIZE(grp3d_low_vectors),
		grp3d_low_vectors,
	},
	{
		ARRAY_SIZE(grp3d_nominal_vectors),
		grp3d_nominal_vectors,
	},
	{
		ARRAY_SIZE(grp3d_max_vectors),
		grp3d_max_vectors,
	},
};

static struct msm_bus_scale_pdata grp3d_bus_scale_pdata = {
	grp3d_bus_scale_usecases,
	ARRAY_SIZE(grp3d_bus_scale_usecases),
	.name = "grp3d",
};
#endif

static struct resource kgsl_3d0_resources[] = {
	{
		.name = KGSL_3D0_REG_MEMORY,
		.start = 0x04300000, /* GFX3D address */
		.end = 0x0431ffff,
		.flags = IORESOURCE_MEM,
	},
	{
		.name = KGSL_3D0_IRQ,
		.start = GFX3D_IRQ,
		.end = GFX3D_IRQ,
		.flags = IORESOURCE_IRQ,
	},
};

static const struct kgsl_iommu_ctx kgsl_3d0_iommu0_ctxs[] = {
	{ "gfx3d_user", 0 },
	{ "gfx3d_priv", 1 },
};

static struct kgsl_device_iommu_data kgsl_3d0_iommu_data[] = {
	{
		.iommu_ctxs = kgsl_3d0_iommu0_ctxs,
		.iommu_ctx_count = ARRAY_SIZE(kgsl_3d0_iommu0_ctxs),
		.physstart = 0x07C00000,
		.physend = 0x07C00000 + SZ_1M - 1,
	},
};

static struct kgsl_device_platform_data kgsl_3d0_pdata = {
	.pwrlevel = {
#ifdef CONFIG_KGSL_GPUOC
		{
			.gpu_freq = 400000000,
			.bus_freq = 4,
			.io_fraction = 0,
		},
		{
			.gpu_freq = 320000000,
			.bus_freq = 3,
			.io_fraction = 33,
		},		
		{
			.gpu_freq = 266667000,
			.bus_freq = 2,
			.io_fraction = 100,
		},		
		{
			.gpu_freq = 228571000,
			.bus_freq = 2,
			.io_fraction = 100,
		},			
		{
			.gpu_freq = 200000000,
			.bus_freq = 2,
			.io_fraction = 100,
		},		
		{
			.gpu_freq = 177778000,
			.bus_freq = 1,
			.io_fraction = 100,
		},		
		{
			.gpu_freq = 160000000,
			.bus_freq = 1,
			.io_fraction = 100,
		},		
		{
			.gpu_freq = 145455000,
			.bus_freq = 1,
			.io_fraction = 100,
		},		
		{
			.gpu_freq = 128000000,
			.bus_freq = 1,
			.io_fraction = 100,
		},
		{
			.gpu_freq = 96000000,
			.bus_freq = 0,
		},		
		{
			.gpu_freq = 76800000,
			.bus_freq = 0,
		},
		{
			.gpu_freq = 64000000,
			.bus_freq = 0,
		},
		{
			.gpu_freq = 54857000,
			.bus_freq = 0,
		},
		{
			.gpu_freq = 48000000,
			.bus_freq = 0,
		},								
		{
			.gpu_freq = 27000000,
			.bus_freq = 0,
		},
#else
		{
			.gpu_freq = 400000000,
			.bus_freq = 3,
			.io_fraction = 0,
		},
		{
			.gpu_freq = 320000000,
			.bus_freq = 2,
			.io_fraction = 33,
		},
		{
			.gpu_freq = 192000000,
			.bus_freq = 1,
			.io_fraction = 100,
		},
		{
			.gpu_freq = 27000000,
			.bus_freq = 0,
		},

#endif

	},
	.init_level = 1,
#ifdef CONFIG_KGSL_GPUOC
	.num_levels = 15,
#else
	.num_levels = 4,
#endif
	.set_grp_async = NULL,
	.idle_timeout = HZ/12,
	.nap_allowed = true,
	.strtstp_sleepwake = false,
	.clk_map = KGSL_CLK_CORE | KGSL_CLK_IFACE | KGSL_CLK_MEM_IFACE,
#ifdef CONFIG_MSM_BUS_SCALING
	.bus_scale_table = &grp3d_bus_scale_pdata,
#endif
	.iommu_data = kgsl_3d0_iommu_data,
	.iommu_count = ARRAY_SIZE(kgsl_3d0_iommu_data),
};

static struct platform_device device_kgsl_3d0 = {
	.name = "kgsl-3d0",
	.id = 0,
	.num_resources = ARRAY_SIZE(kgsl_3d0_resources),
	.resource = kgsl_3d0_resources,
	.dev = {
		.platform_data = &kgsl_3d0_pdata,
	},
};

#ifdef CONFIG_KGSL_GPUOC
void SetMAXGPUFreq(unsigned long freq)
{
	kgsl_3d0_pdata.pwrlevel[0].gpu_freq = freq;
}
#endif

void __init msm8930_init_gpu(void)
{
	unsigned int version = socinfo_get_version();

	/* Set the turbo speed for the AA and AB respectively */

	if (cpu_is_msm8930aa())
		kgsl_3d0_pdata.pwrlevel[0].gpu_freq = 450000000;
	else if (cpu_is_msm8930ab()) {
		kgsl_3d0_pdata.pwrlevel[0].gpu_freq = 500000000;
		grp3d_max_vectors[0].ib = KGSL_CONVERT_TO_MBPS(4816);
	}

	/* Set up the chip ID based on the SoC version */

	if (cpu_is_msm8930ab())
		kgsl_3d0_pdata.chipid = ADRENO_CHIPID(3, 0, 5, 3);
	else if ((SOCINFO_VERSION_MAJOR(version) == 1) &&
		(SOCINFO_VERSION_MINOR(version) == 2))
		kgsl_3d0_pdata.chipid = ADRENO_CHIPID(3, 0, 5, 2);
	else
		kgsl_3d0_pdata.chipid = ADRENO_CHIPID(3, 0, 5, 0);

	platform_device_register(&device_kgsl_3d0);
}
