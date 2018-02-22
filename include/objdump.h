//
// Created by NANAA on 19/02/18.
//

#ifndef PSU_2017_NMOBJDUMP_OBJDUMP_H
#define PSU_2017_NMOBJDUMP_OBJDUMP_H

#include <elf.h>

#define NOFILE 1
#define ORDINARYFILE 2
#define WRONGFILE 3

int elf_check_file(Elf64_Ehdr *hdr);
int parse64(char *data, const char *filename);
int print_errors(const char *name, int type);
const char* get_machine_type64(Elf64_Half type);
int parse32(char *data, const char *filename);
const char* get_machine_type32(Elf32_Half type);

#endif //PSU_2017_NMOBJDUMP_OBJDUMP_H
