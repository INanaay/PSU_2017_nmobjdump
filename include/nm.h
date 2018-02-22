//
// Created by NANAA on 14/02/18.
//

#ifndef PSU_2017_NMOBJDUMP_NM_H
#define PSU_2017_NMOBJDUMP_NM_H

#include <elf.h>

#define TRUE 1
#define FALSE 0
#define NO_FILE 0
#define WRONG_FILE 1
#define ORDINARY_FILE 2
#define NO_SYMBOLS 3

struct s_symbolInfo {
    const char *name;
    size_t value;
    char type;
};

typedef struct s_symbolInfo t_symbolInfo;

int get_size(t_symbolInfo **symbols);
t_symbolInfo **create_symbols_tab(Elf64_Ehdr *hdr, char *data);
void print_symbols(t_symbolInfo **symbols);
void free_tab(t_symbolInfo **symbols);
void bubble_sort(t_symbolInfo **symbols);
t_symbolInfo **create_symbols_tab32(Elf32_Ehdr *hdr, char *data);
int print_errors(const char *filename, int type);
int elf_check_file(Elf64_Ehdr *hdr);
int parse32(char *data, const char *filename);
void print_symbols32(t_symbolInfo **symbols);


#endif //PSU_2017_NMOBJDUMP_NM_H
