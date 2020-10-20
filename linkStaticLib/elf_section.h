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

#define elfhdr		Elf64_Ehdr
#define elf_phdr	Elf64_Phdr
#define elf_shdr	Elf64_Shdr
#define elf_note	Elf64_Nhdr
#define elf_addr_t	Elf64_Off
#define Elf_Half	Elf64_Half

int findSection(char* path, char* section_name, char* data_buf);
#endif