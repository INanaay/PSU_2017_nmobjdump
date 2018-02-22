/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/02 by NANAA
*/

#include <stdio.h>
#include "../include/flags.h"
#include "../include/objdump.h"

static int get_flags2(t_flags *flags, Elf64_Ehdr *hdr, char *data)
{
	int res = 0;
	Elf64_Shdr *shdr =  (Elf64_Shdr *) (data + hdr->e_shoff);

	for (int i = 0; i < hdr->e_shnum; i++) {
		if (shdr[i].sh_type == SHT_SYMTAB ||
		shdr[i].sh_type == SHT_DYNSYM) {
			flags->has_syms = 1;
			res += HAS_SYMS;
			break;
		}
	}
	return (res);
}

int get_flags(t_flags *flags, Elf64_Ehdr *hdr, char *data)
{
	int res = 0;

	if (hdr->e_type == ET_REL) {
		flags->has_reloc = 1;
		res += HAS_RELOC;
	}
	else if (hdr->e_type == ET_EXEC) {
		flags->paged = 1;
		flags->exec = 1;
		res += EXEC_P + D_PAGED;
	}
	else if (hdr->e_type == ET_DYN) {
		flags->paged = 1;
		flags->dyn = 1;
		res += DYNAMIC + D_PAGED;
	}
	res += get_flags2(flags, hdr, data);
	return (res);
}

static int get_flags232(t_flags *flags, Elf32_Ehdr *hdr, char *data)
{
	int res = 0;
	Elf64_Shdr *shdr =  (Elf64_Shdr *) (data + hdr->e_shoff);

	for (int i = 0; i < hdr->e_shnum; i++) {
		if (shdr[i].sh_type == SHT_SYMTAB ||
		shdr[i].sh_type == SHT_DYNSYM) {
			flags->has_syms = 1;
			res += HAS_SYMS;
			break;
		}
	}
	return (res);
}

int get_flags32(t_flags *flags, Elf32_Ehdr *hdr, char *data)
{
	int res = 0;

	if (hdr->e_type == ET_REL) {
		flags->has_reloc = 1;
		res += HAS_RELOC;
	}
	else if (hdr->e_type == ET_EXEC) {
		flags->paged = 1;
		flags->exec = 1;
		res += EXEC_P + D_PAGED;
	}
	else if (hdr->e_type == ET_DYN) {
		flags->paged = 1;
		flags->dyn = 1;
		res += DYNAMIC + D_PAGED;
	}
	res += get_flags232(flags, hdr, data);
	return (res);
}

void print_flags(t_flags *flags)
{
	const char *tab[6];
	int i = 0, y;

	if (flags->exec == 1)
		tab[i++] = "EXEC_P";
	if (flags->has_syms == 1)
		tab[i++] = "HAS_SYMS";
	if (flags->paged == 1)
		tab[i++] = "D_PAGED";
	if (flags->has_reloc == 1)
		tab[i++] = "HAS RELOC";
	if (flags->dyn == 1)
		tab[i++] = "DYNAMIC";
	for (y = 0; y < i - 1; y++)
		printf("%s, ", tab[y]);
	if (tab[y] != 0)
		printf("%s\n", tab[y]);
}
