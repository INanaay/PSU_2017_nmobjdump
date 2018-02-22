/*
** EPITECH PROJECT, 2018
** main
** File description:
** main
*/

#include <stdio.h>
#include "../include/nm.h"
#include <stdlib.h>

static int add_symbol_to_tab(t_symbolInfo **symbols, const char *name,
			size_t value, size_t index)
{
	symbols[index] = malloc(sizeof(t_symbolInfo));
	if (!symbols[index])
		return (FALSE);
	symbols[index]->name = name;
	symbols[index]->value = value;
	return (TRUE);
}

static t_symbolInfo **parse_sections(size_t nbSymbols, const char *nameAdr,
				Elf32_Sym *symtab, Elf32_Shdr *shdr)
{
	t_symbolInfo **symbols;
	const char *name;
	size_t index = 0;

	if ((symbols = calloc(sizeof (t_symbolInfo *) * nbSymbols,
			sizeof(t_symbolInfo *))) == NULL)
		return (NULL);
	for (size_t y = 0; y < nbSymbols; y++) {
		name = nameAdr + symtab[y].st_name;
		if (name[0] != 0 && name[0] != '\n' && symtab[y].st_info !=
		STT_FILE) {
			if ((add_symbol_to_tab(symbols, name,
					symtab[y].st_value,
					index)) == FALSE)
				return (NULL);
			symbols[index]->type = get_type32(symtab[y], shdr);
			index++;
		}
	}
	return (symbols);
}

static t_symbolInfo **fill_symbol_tab(Elf32_Ehdr *hdr, char *data, int i)
{
	Elf32_Shdr *shdr = (Elf32_Shdr *)(data + hdr->e_shoff);
	Elf32_Sym *symtab;
	size_t nbSymbols;
	const char *nameAdr;

	nbSymbols = shdr[i].sh_size / sizeof(Elf32_Sym);
	symtab = (Elf32_Sym *) (data + shdr[i].sh_offset);
	nameAdr = data + shdr[shdr[i].sh_link].sh_offset;
	return (parse_sections(nbSymbols, nameAdr, symtab, shdr));
}

t_symbolInfo **create_symbols_tab32(Elf32_Ehdr *hdr, char *data)
{
	Elf32_Shdr *shdr = (Elf32_Shdr *)(data + hdr->e_shoff);
	int shnum = hdr->e_shnum;

	if (hdr->e_shstrndx == SHN_UNDEF)
		return (NULL);
	for (int i = 0; i < shnum; i++) {
		if (shdr[i].sh_type == SHT_SYMTAB) {
			return (fill_symbol_tab(hdr, data, i));
		}
	}
	return (NULL);
}
