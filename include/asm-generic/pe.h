/* SPDX-License-Identifier: GPL-2.0+ */
/*
 *  Portable Executable and Common Object Constants
 *
 *  Copyright (c) 2018 Heinrich Schuchardt
 *
 *  based on the "Microsoft Portable Executable and Common Object File Format
 *  Specification", revision 11, 2017-01-23
 */

#ifndef _ASM_PE_H
#define _ASM_PE_H

/* Characteristics */
#define IMAGE_FILE_RELOCS_STRIPPED		0x0001
#define IMAGE_FILE_EXECUTABLE_IMAGE		0x0002
#define IMAGE_FILE_LINE_NUMS_STRIPPED		0x0004
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED		0x0008
#define IMAGE_FILE_AGGRESSIVE_WS_TRIM		0x0010
#define IMAGE_FILE_LARGE_ADDRESS_AWARE		0x0020
/* Reserved					0x0040 */
#define IMAGE_FILE_BYTES_REVERSED_LO		0x0080
#define IMAGE_FILE_32BIT_MACHINE		0x0100
#define IMAGE_FILE_DEBUG_STRIPPED		0x0200
#define IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP	0x0400
#define IMAGE_FILE_NET_RUN_FROM_SWAP		0x0800
#define IMAGE_FILE_SYSTEM			0x1000
#define IMAGE_FILE_DLL				0x2000
#define IMAGE_FILE_UP_SYSTEM_ONLY		0x4000
#define IMAGE_FILE_BYTES_REVERSED_HI		0x8000

/* Machine types */
#define IMAGE_FILE_MACHINE_I386			0x014c
#define IMAGE_FILE_MACHINE_ARM			0x01c0
#define IMAGE_FILE_MACHINE_THUMB		0x01c2
#define IMAGE_FILE_MACHINE_ARMNT		0x01c4
#define IMAGE_FILE_MACHINE_AMD64		0x8664
#define IMAGE_FILE_MACHINE_ARM64		0xaa64
#define IMAGE_FILE_MACHINE_RISCV32		0x5032
#define IMAGE_FILE_MACHINE_RISCV64		0x5064

/* Header magic constants */
#define IMAGE_NT_OPTIONAL_HDR32_MAGIC		0x010b
#define IMAGE_NT_OPTIONAL_HDR64_MAGIC		0x020b
#define IMAGE_DOS_SIGNATURE			0x5a4d     /* MZ   */
#define IMAGE_NT_SIGNATURE			0x00004550 /* PE00 */

/* Subsystem type */
#define IMAGE_SUBSYSTEM_EFI_APPLICATION		10
#define IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER	11
#define IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER	12
#define IMAGE_SUBSYSTEM_EFI_ROM			13

/* DLL characteristics */
#define IMAGE_DLLCHARACTERISTICS_NX_COMPAT	0x100

/* Section flags */
#define IMAGE_SCN_CNT_CODE			0x00000020
#define IMAGE_SCN_CNT_INITIALIZED_DATA		0x00000040
#define IMAGE_SCN_CNT_UNINITIALIZED_ DATA	0x00000080
#define IMAGE_SCN_LNK_NRELOC_OVFL		0x01000000
#define IMAGE_SCN_MEM_DISCARDABLE		0x02000000
#define IMAGE_SCN_MEM_NOT_CACHED		0x04000000
#define IMAGE_SCN_MEM_NOT_PAGED			0x08000000
#define IMAGE_SCN_MEM_SHARED			0x10000000
#define IMAGE_SCN_MEM_EXECUTE			0x20000000
#define IMAGE_SCN_MEM_READ			0x40000000
#define IMAGE_SCN_MEM_WRITE			0x80000000

#define LINUX_ARM64_MAGIC			0x644d5241

#endif /* _ASM_PE_H */
