/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/02 by NANAA
*/

#include "stdio.h"
#include <elf.h>
#include <string.h>
#include <ctype.h>
#include "../include/objdump.h"
#include "../include/nm.h"


static int elf_check_file32(Elf32_Ehdr *hdr) {
	if(!hdr)
		return 0;
	return (hdr->e_ident[EI_MAG0] == ELFMAG0 && hdr->e_ident[EI_MAG1] == ELFMAG1
		&& hdr->e_ident[EI_MAG2] == ELFMAG2 && hdr->e_ident[EI_MAG3] == ELFMAG3);
}

static void show_header(Elf32_Ehdr *hdr, const char *filename)
{
	printf("\n%s     file format elf32-x86-32\n", filename);
	printf("architecture: %s,", get_machine_type32(hdr->e_machine));
	printf(" flags 0x%08x:\n\n", hdr->e_flags);
	printf("start address 0x%016lx\n\n", hdr->e_entry);
}

static void print_letters(int start, unsigned char *buffer, int size)
{
	int i = 0;

	printf("  ");
	for (i = 0; i < 16 && i + start < size; i++) {
		if (isprint(buffer[i + start]) != 0)
			printf("%c", buffer[i + start]);
		else
			printf(".");
	}
	for (int y = i; y < 16; y++) {
		printf(" ");
	}
}

static int print_section32(Elf32_Shdr *shdr, char *data)
{
	unsigned int i = 0, j = 0;
	int adr = (int) shdr->sh_addr;
	unsigned char *buffer = (unsigned char *) (data + shdr->sh_offset);

	while (j < (unsigned int) shdr->sh_size) {
		printf(" %04x ", adr);
		for (i = 0; i < 16; i++) {
			if (i + j < shdr->sh_size)
				printf("%02x", buffer[i + j]);
			else
				printf("  ");
			if (i == 3 || i == 7 || i == 11) {
				printf(" ");
			}
		}
		print_letters(j, buffer, (int) shdr->sh_size);
		j += 16;
		adr += 16;
		printf("\n");
	}
}

int parse32(char *data, const char *filename)
{
	Elf32_Ehdr *hdr;
	const char *sectionName;
	Elf32_Shdr *sh_strtab, *shdr;

	hdr = (Elf32_Ehdr *) data;
	if (elf_check_file32(hdr) == FALSE)
		return print_errors(filename, WRONGFILE);
	shdr = (Elf32_Shdr * )(data + hdr->e_shoff);
	show_header(hdr, filename);
	sh_strtab = &shdr[hdr->e_shstrndx];
	for (int i = 1; i < hdr->e_shnum; i++) {
		sectionName = data + sh_strtab->sh_offset + shdr[i].sh_name;
		if (strcmp(sectionName, ".strtab") != 0 && strcmp(sectionName, ".symtab") != 0 &&
		    strcmp(sectionName, ".shstrtab") != 0 && strcmp(sectionName, ".bss") != 0) {
			printf("Contents of section %s:\n", sectionName);
			print_section32(&shdr[i], data);
		}
	}
	return 0;
}
