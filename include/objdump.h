//
// Created by NANAA on 19/02/18.
//

#ifndef PSU_2017_NMOBJDUMP_OBJDUMP_H
#define PSU_2017_NMOBJDUMP_OBJDUMP_H

#include <elf.h>

#define NOFILE 1
#define ORDINARYFILE 2
#define WRONGFILE 3


struct s_flags {
	int has_reloc;
	int paged;
	int exec;
	int dyn;
	int has_syms;
};

typedef struct s_flags t_flags;

int elf_check_file(Elf64_Ehdr *hdr);
int parse64(char *data, const char *filename);
int print_errors(const char *name, int type);
const char* get_machine_type64(Elf64_Half type);
int parse32(char *data, const char *filename);
const char* get_machine_type32(Elf32_Half type);
int get_flags(t_flags *flags, Elf64_Ehdr *hdr, char *data);
void print_flags(t_flags *flags);
int get_flags32(t_flags *flags, Elf32_Ehdr *hdr, char *data);

#endif //PSU_2017_NMOBJDUMP_OBJDUMP_H
