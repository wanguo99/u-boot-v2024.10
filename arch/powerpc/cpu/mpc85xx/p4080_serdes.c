// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2009-2010 Freescale Semiconductor, Inc.
 */

#include <asm/io.h>
#include <asm/fsl_serdes.h>
#include <asm/processor.h>
#include <asm/io.h>
#include "fsl_corenet_serdes.h"

static u8 serdes_cfg_tbl[][SRDS_MAX_LANES] = {
	[0x2] = {PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1,
		AURORA, AURORA, XAUI_FM2, XAUI_FM2, XAUI_FM2, XAUI_FM2,
		XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1},
	[0x5] = {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2, PCIE2, PCIE2,
		AURORA, AURORA, XAUI_FM2, XAUI_FM2, XAUI_FM2, XAUI_FM2,
		XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1},
	[0x8] = {PCIE1, PCIE1, PCIE3, PCIE3, PCIE2, PCIE2, PCIE2, PCIE2,
		AURORA, AURORA, XAUI_FM2, XAUI_FM2, XAUI_FM2, XAUI_FM2,
		XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1},
	[0xd] = {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2, SGMII_FM2_DTSEC3,
		SGMII_FM2_DTSEC4, AURORA, AURORA, XAUI_FM2, XAUI_FM2, XAUI_FM2,
		XAUI_FM2, XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1},
	[0xe] = {PCIE1, PCIE1, PCIE3, PCIE3, PCIE2, PCIE2, SGMII_FM2_DTSEC3,
		SGMII_FM2_DTSEC4, AURORA, AURORA, XAUI_FM2, XAUI_FM2, XAUI_FM2,
		XAUI_FM2, XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1},
	[0xf] = {PCIE1, PCIE1, PCIE1, PCIE1, SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4, AURORA, AURORA, XAUI_FM2,
		XAUI_FM2, XAUI_FM2, XAUI_FM2, NONE, NONE, NONE, NONE},
	[0x10] = {PCIE1, PCIE1, PCIE3, PCIE3, SGMII_FM2_DTSEC1,
		SGMII_FM2_DTSEC2, SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4,
		AURORA, AURORA, XAUI_FM2, XAUI_FM2, XAUI_FM2, XAUI_FM2,
		NONE, NONE, NONE, NONE},
	[0x13] = {SRIO2, SRIO2, SRIO2, SRIO2, SRIO1, SRIO1, SRIO1, SRIO1,
		AURORA, AURORA, XAUI_FM2, XAUI_FM2, XAUI_FM2, XAUI_FM2,
		XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1},
	[0x16] = {SRIO2, SRIO2, SRIO2, SRIO2, SRIO1, SRIO1, SRIO1, SRIO1,
		AURORA, AURORA, SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4},
	[0x19] = {SRIO2, SRIO2, SRIO2, SRIO2, SRIO1, SRIO1, SRIO1, SRIO1,
		AURORA, AURORA, PCIE3, PCIE3, PCIE3, PCIE3, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4},
	[0x1d] = {PCIE1, PCIE1, PCIE3, PCIE3, NONE, SRIO2, NONE, SRIO1,
		AURORA, AURORA, XAUI_FM2, XAUI_FM2, XAUI_FM2, XAUI_FM2,
		XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1},
	[0x22] = {PCIE1, PCIE1, PCIE1, PCIE1, SRIO1, SRIO1, SRIO1, SRIO1,
		AURORA, AURORA, XAUI_FM2, XAUI_FM2, XAUI_FM2, XAUI_FM2,
		XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1},
	[0x25] = {PCIE1, PCIE1, PCIE3, PCIE3, SRIO1, SRIO1, SRIO1, SRIO1,
		AURORA, AURORA, XAUI_FM2, XAUI_FM2, XAUI_FM2, XAUI_FM2,
		XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1},
};

#ifdef CONFIG_SYS_P4080_ERRATUM_SERDES8
uint16_t srds_lpd_b[SRDS_MAX_BANK];
#endif

enum srds_prtcl serdes_get_prtcl(int cfg, int lane)
{
	if (!serdes_lane_enabled(lane))
		return NONE;

	return serdes_cfg_tbl[cfg][lane];
}

int is_serdes_prtcl_valid(u32 prtcl) {
	int i;

	if (prtcl >= ARRAY_SIZE(serdes_cfg_tbl))
		return 0;

	for (i = 0; i < SRDS_MAX_LANES; i++) {
		if (serdes_cfg_tbl[prtcl][i] != NONE)
			return 1;
	}

	return 0;
}
