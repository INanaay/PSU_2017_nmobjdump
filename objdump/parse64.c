//
// Created by NANAA on 19/02/18.
//

#include "stdio.h"
#include <elf.h>
#include <string.h>
#include <ctype.h>
#include "../include/objdump.h"
#include "../include/nm.h"

static void show_header(Elf64_Ehdr *hdr, const char *filename, char *data)
{
	t_flags flags;

	printf("\n%s:     file format elf64-x86-64\n", filename);
	printf("architecture: %s,", get_machine_type64(hdr->e_machine));
	printf(" flags 0x%08x:\n", get_flags(&flags, hdr, data));
	print_flags(&flags);
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

int print_section(Elf64_Shdr *shdr, char *data)
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

int parse64(char *data, const char *filename)
{
	Elf64_Ehdr *hdr;
	const char *sectionName;
	Elf64_Shdr *sh_strtab, *shdr;

	hdr = (Elf64_Ehdr *) data;
	if (elf_check_file(hdr) == FALSE)
		return print_errors(filename, WRONGFILE); // print_error
	shdr = (Elf64_Shdr * )(data + hdr->e_shoff);
	show_header(hdr, filename, data);
	sh_strtab = &shdr[hdr->e_shstrndx];
	for (int i = 1; i < hdr->e_shnum; i++) {
		sectionName = data + sh_strtab->sh_offset + shdr[i].sh_name;
		if (strcmp(sectionName, ".strtab") != 0 && strcmp(sectionName, ".symtab") != 0 &&
		    strcmp(sectionName, ".shstrtab") != 0 && strcmp(sectionName, ".bss") != 0) {
			printf("Contents of section %s:\n", sectionName);
			print_section(&shdr[i], data);
		}
	}
	return 0;
}
