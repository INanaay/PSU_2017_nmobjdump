/*
** EPITECH PROJECT, 2018
** main
** File description:
** main
*/

#include <stdio.h>
#include "../include/nm.h"
#include <stdlib.h>

static char get_type2(Elf32_Sym sym, Elf32_Shdr *shdr)
{
	if (sym.st_shndx == SHN_UNDEF)
		return'U';
	else if (sym.st_shndx == SHN_ABS)
		return 'A';
	else if (sym.st_shndx == SHN_COMMON)
		return'C';
	else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
		 && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		return 'B';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
		 && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
		return 'R';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
		 && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		return 'D';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
		 && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		return 'T';
	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
		return 'D';
	return -1;
}

static char get_type(Elf32_Sym sym, Elf32_Shdr *shdr)
{
	char type;
	if (ELF32_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
		type = 'u';
	else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK) {
		type = 'W';
		if (sym.st_shndx == SHN_UNDEF)
			type = 'w';
	}
	else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK && ELF32_ST_TYPE(sym.st_info) == STT_OBJECT) {
		type = 'V';
		if (sym.st_shndx == SHN_UNDEF)
			type = 'v';
	}
	else if (get_type2(sym, shdr) != -1)
		type = get_type2(sym, shdr);
	else
		type = 'T';
	if (ELF32_ST_BIND(sym.st_info) == STB_LOCAL && type != '?')
		type = (char) (type + 32);
	return type;
}

static int add_symbol_to_tab(t_symbolInfo **symbols, const char *name,
			size_t value, size_t index, char type)
{
	symbols[index] = malloc(sizeof(t_symbolInfo));
	if (!symbols[index])
		return FALSE;
	symbols[index]->name = name;
	symbols[index]->value = value;
	symbols[index]->type = type;
	return TRUE;
}

static t_symbolInfo **fill_symbol_tab(Elf32_Ehdr *hdr, char *data, int i)
{
	Elf32_Shdr *shdr = (Elf32_Shdr *)(data + hdr->e_shoff);
	Elf32_Sym * symtab;
	size_t nbSymbols, index = 0;
	t_symbolInfo **symbols;
	const char *nameAdr, *name;

	nbSymbols = shdr[i].sh_size / sizeof(Elf32_Sym);
	if ((symbols = calloc(sizeof (t_symbolInfo *) * nbSymbols, sizeof(t_symbolInfo *))) == NULL)
		return NULL;
	symtab = (Elf32_Sym *) (data + shdr[i].sh_offset);
	nameAdr = data + shdr[shdr[i].sh_link].sh_offset;
	for (size_t y = 0; y < nbSymbols; y++) {
		name = nameAdr + symtab[y].st_name;
		if (name[0] != 0 && name[0] != '\n' && symtab[y].st_info != STT_FILE) {
			if ((add_symbol_to_tab(symbols, name, symtab[y].st_value, index, get_type(symtab[y], shdr))) == FALSE)
				return NULL;
			index++;
		}
	}
	return (symbols);
}

t_symbolInfo **create_symbols_tab32(Elf32_Ehdr *hdr, char *data)
{
	Elf32_Shdr *shdr = (Elf32_Shdr *)(data + hdr->e_shoff);
	int shnum = hdr->e_shnum;

	if (hdr->e_shstrndx == SHN_UNDEF)
		return NULL;
	for (int i = 0; i < shnum; i++) {
		if (shdr[i].sh_type == SHT_SYMTAB) {
			return fill_symbol_tab(hdr, data, i);
		}
	}
	return NULL;
}
