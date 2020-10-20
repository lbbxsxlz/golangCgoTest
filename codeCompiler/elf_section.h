/******************************************************************************
 * elf_section.h
 *
 * Copyright (C) 2011-2013 ZheJiang Dahua Technology CO.,LTD.
 *
 * Author : li_binbin1 <li_binbin1@dahuatech.com>
 * Version: V1.0.1   Created@2019年12月10日 10:51:58
 *
 * Description: Find section Interface Declare
 *
 *****************************************************************************/
#ifndef _ELF_SECTION_H_
#define _ELF_SECTION_H_

/* Hi3559AV100 64位架构 */
#if ELF_CLASS == ELFCLASS64
#define elfhdr		Elf64_Ehdr
#define elf_phdr	Elf64_Phdr
#define elf_shdr	Elf64_Shdr
#define elf_note	Elf64_Nhdr
#define elf_addr_t	Elf64_Off
#define Elf_Half	Elf64_Half
/* 其他平台32位架构 */
#else
#define elfhdr		Elf32_Ehdr
#define elf_phdr	Elf32_Phdr
#define elf_shdr	Elf32_Shdr
#define elf_note	Elf32_Nhdr
#define elf_addr_t	Elf32_Off
#define Elf_Half	Elf32_Half
#endif

int findSection(char* path, char* section_name, char* data_buf)
#endif