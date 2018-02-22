//
// Created by NANAA on 17/02/18.
//

#include <elf.h>
#include <stddef.h>
#include "../include/nm.h"

static int elf_check_file32(Elf32_Ehdr *hdr) {
    if(!hdr)
        return 0;
    return (hdr->e_ident[EI_MAG0] == ELFMAG0 && hdr->e_ident[EI_MAG1] == ELFMAG1
            && hdr->e_ident[EI_MAG2] == ELFMAG2 && hdr->e_ident[EI_MAG3] == ELFMAG3);
}

int parse32(char *data, const char *filename)
{
    Elf32_Ehdr *hdr;
    t_symbolInfo **symbols;

    hdr = (Elf32_Ehdr *) data;
    if (elf_check_file32(hdr) == FALSE)
        return print_errors(filename, WRONG_FILE);
    if ((symbols = create_symbols_tab32(hdr, data)) == NULL)
        return print_errors(filename, NO_FILE);
    bubble_sort(symbols);
    print_symbols32(symbols);
    free_tab(symbols);
    return 0;
}
