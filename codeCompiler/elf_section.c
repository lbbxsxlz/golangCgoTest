/******************************************************************************
 * elf_section.c
 *
 * Author : lbbxsxlz <lbbxsxlz@gmail.com>
 * Version: V1.0.1   Created@2019年12月16日 10:51:58
 *
 * Description: Support Find Section Interface
 *
 *****************************************************************************/
//#include "elf_section.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <elf.h>
#include <sys/mman.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define elfhdr        Elf64_Ehdr
#define elf_phdr    Elf64_Phdr
#define elf_shdr    Elf64_Shdr
#define elf_note    Elf64_Nhdr
#define elf_addr_t    Elf64_Off
#define Elf_Half    Elf64_Half

int findSection(char* path, char* section_name, char* data_buf)
{
    int fd = -1, i;
    char *mem = NULL;
    struct stat st;
    char *StringTable;
    int flag = -1;
    int ret = -1;

    elfhdr *ehdr;
    elf_shdr *shdr;

    unsigned long offset = 0;
    unsigned long size = 0;

    if ((fd = open(path, O_RDONLY)) < 0) {
        perror("open");
        goto quit;
    }

    if (fstat(fd, &st) < 0) {
        perror("fstat");
        goto quit;
    }

    /* Map 可执行文件到内存 */
    mem = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mem == MAP_FAILED) {
        perror("mmap");
        goto quit;
    }

    ehdr = (elfhdr *)mem;
    /* shdr table 偏移 e_shoff */
    shdr = (elf_shdr *)&mem[ehdr->e_shoff];

    /* 校验 ELF magic (The first 4 bytes) match up as 0x7f E L F */
    if (mem[0] != 0x7f && strcmp(&mem[1], "ELF")) {
        printf("%s is not an ELF file\n", path);
        goto quit;
    }

    /* 判断文件是否是可执行文件 */
    if (ehdr->e_type != ET_EXEC) {
        printf("%s is not an executable\n", path);
        printf("ehdr->e_type = %x, ET_EXEC = %x\n",ehdr->e_type, ET_EXEC);
        goto quit;
    }

    /* 根据e_shstrndx对应的 section name */
    StringTable = &mem[shdr[ehdr->e_shstrndx].sh_offset];

    /* 遍历section name，找到匹配的section_name */
    for (i = 1; i < ehdr->e_shnum; i++) {
        if (strncmp(&StringTable[shdr[i].sh_name], section_name, strlen(section_name)) == 0) {
            offset = shdr[i].sh_offset;
            size = shdr[i].sh_size;
            flag = 1;
            break;
        }
    }

    if (1 == flag) {
        memcpy(data_buf, mem + offset, size);
        ret = 0;
    }

quit:
    if (mem) {
        if(munmap(mem, st.st_size) < 0)
            printf("munmap fail! \n");
        mem = NULL;
    }

    if (fd > 0) {
        close(fd);
        fd = -1;
    }
    return ret;
}

