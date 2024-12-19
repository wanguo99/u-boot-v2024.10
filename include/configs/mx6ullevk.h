/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 *
 * Configuration settings for the Freescale i.MX6UL 14x14 EVK board.
 */
#ifndef __MX6ULLEVK_CONFIG_H
#define __MX6ULLEVK_CONFIG_H

#include <asm/arch/imx-regs.h>
#include <linux/sizes.h>
#include <linux/stringify.h>
#include "mx6_common.h"
#include <asm/mach-imx/gpio.h>

#define PHYS_SDRAM_SIZE	SZ_512M

#define CFG_MXC_UART_BASE		UART1_BASE

/* MMC Configs */
#ifdef CONFIG_FSL_USDHC
#define CFG_SYS_FSL_ESDHC_ADDR	USDHC2_BASE_ADDR
#define CFG_SYS_FSL_USDHC_NUM	2
#endif

/* user env Configs */
#define CFG_EXTRA_USER_ENV_SETTINGS \
	"ethaddr=00:11:22:33:44:55\0" \
	"eth1addr=01:11:22:33:44:55\0" \
	"ipaddr=10.10.0.221\0" \
	"gatewayip=10.10.0.101\0" \
	"serverip=10.10.0.201\0" \
	"sddev=0\0" \
	"sdpart=1\0" \
	"dl_kernel=tftp ${loadaddr} ${image}; echo Download ${image} ok.\0" \
	"dl_fdt=tftp ${fdt_addr} ${fdt_file}; echo Download ${fdt_file} ok.\0" \
	"update_zImage=run dl_kernel;" \
		"fatwrite mmc ${sddev}:${sdpart} ${loadaddr} ${image} ${filesize};" \
		"echo update kernel ok.\0" \
	"update_fdt=run dl_fdt;"\
		"fatwrite mmc ${sddev}:${sdpart} ${fdt_addr} ${fdt_file} ${filesize};" \
		"echo update fdt ok.\0" \
	"dk=run findfdt; mmc dev ${sddev}; run update_zImage; run update_fdt\0" \
	"sdroot=/dev/mmcblk0p2 rootwait rw\0" \
	"sdargs=setenv bootargs console=${console},${baudrate} root=${sdroot}\0" \
	"boot_with_tftp=yes\0" \
	"emmcboot=echo Booting from eMMC Card ...; " \
		"mmc dev ${mmcdev}; run mmcargs; " \
		"run findfdt; run loadfdt; run loadimage; " \
		"bootz ${loadaddr} - ${fdt_addr};\0" \
	"sdboot=echo Booting from SD Card ...; " \
		"mmc dev ${sddev}; run sdargs; " \
		"if test ${boot_with_tftp} = 1; then " \
			"echo Boot with tftp; " \
			"run dl_kernel; run dl_fdt; " \
		"else " \
			"echo Boot without tftp; " \
			"run findfdt; run loadfdt; run loadimage; " \
		"fi; " \
		"bootz ${loadaddr} - ${fdt_addr};\0" \


#define CFG_EXTRA_ENV_SETTINGS \
	"script=boot.scr\0" \
	"image=zImage\0" \
	"console=ttymxc0\0" \
	"fdt_high=0xffffffff\0" \
	"initrd_high=0xffffffff\0" \
	"fdt_file=imx6ull-14x14-evk.dtb\0" \
	"fdt_addr=0x83000000\0" \
	"boot_fdt=try\0" \
	"ip_dyn=no\0" \
	"videomode=video=ctfb:x:480,y:272,depth:24,pclk:108695,le:8,ri:4,up:2,lo:4,hs:41,vs:10,sync:0,vmode:0\0" \
	"mmcdev="__stringify(CONFIG_SYS_MMC_ENV_DEV)"\0" \
	"mmcpart=1\0" \
	"mmcroot=/dev/mmcblk1p2 rootwait rw\0" \
	"mmcautodetect=yes\0" \
	"mmcargs=setenv bootargs console=${console},${baudrate} " \
		"root=${mmcroot}\0" \
	"loadbootscript=" \
		"fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${script};\0" \
	"bootscript=echo Running bootscript from mmc ...; " \
		"source\0" \
	"loadimage=fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${image}\0" \
	"loadfdt=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" \
	"mmcboot=echo Booting from mmc ...; " \
		"run mmcargs; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if run loadfdt; then " \
				"bootz ${loadaddr} - ${fdt_addr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0" \
		"findfdt="\
			"if test $fdt_file = undefined; then " \
				"if test $board_name = ULZ-EVK && test $board_rev = 14X14; then " \
					"setenv fdt_file imx6ulz-14x14-evk.dtb; fi; " \
				"if test $board_name = EVK && test $board_rev = 14X14; then " \
					"setenv fdt_file imx6ull-14x14-evk.dtb; fi; " \
				"if test $fdt_file = undefined; then " \
					"echo WARNING: Could not determine dtb to use; " \
				"fi; " \
			"fi;\0" \
	"netargs=setenv bootargs console=${console},${baudrate} " \
		"root=/dev/nfs " \
	"ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp\0" \
		"netboot=echo Booting from net ...; " \
		"run netargs; " \
		"if test ${ip_dyn} = yes; then " \
			"setenv get_cmd dhcp; " \
		"else " \
			"setenv get_cmd tftp; " \
		"fi; " \
		"${get_cmd} ${image}; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if ${get_cmd} ${fdt_addr} ${fdt_file}; then " \
				"bootz ${loadaddr} - ${fdt_addr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0" \
	CFG_EXTRA_USER_ENV_SETTINGS

/* Miscellaneous configurable options */

/* Physical Memory Map */
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR

#define CFG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CFG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CFG_SYS_INIT_RAM_SIZE	IRAM_SIZE

/* environment organization */

#ifdef CONFIG_CMD_NET
#define CFG_FEC_ENET_DEV		1
#endif

#endif
