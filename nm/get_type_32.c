/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/02 by NANAA
*/

#include "../include/nm.h"

static char get_type3(Elf32_Sym sym, Elf32_Shdr *shdr)
{
	if (sym.st_shndx == SHN_UNDEF)
		return ('U');
	else if (sym.st_shndx == SHN_ABS)
		return ('A');
	else if (sym.st_shndx == SHN_COMMON)
		return ('C');
	else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
		&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		return ('B');
	return (-1);
}

static char get_type2(Elf32_Sym sym, Elf32_Shdr *shdr)
{
	if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
	&& shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
		return ('R');
	else if (ELF32_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
		return ('u');
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
		&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		return ('D');
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
		&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		return ('T');
	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
		return ('D');
	else if (get_type3(sym, shdr) != -1)
		return (get_type3(sym, shdr));
	return (-1);
}

char get_type32(Elf32_Sym sym, Elf32_Shdr *shdr)
{
	char type;

	if (ELF32_ST_BIND(sym.st_info) == STB_WEAK) {
		type = 'W';
		if (sym.st_shndx == SHN_UNDEF)
			type = 'w';
	}
	else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK
		&& ELF32_ST_TYPE(sym.st_info) == STT_OBJECT) {
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
	return (type);
}
