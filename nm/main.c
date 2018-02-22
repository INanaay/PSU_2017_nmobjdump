/*
** EPITECH PROJECT, 2018
** main
** File description:
** main
*/

#include <stdio.h>
#include "../include/nm.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <locale.h>

int print_errors(const char *filename, int type)
{
	if (type == NO_FILE)
		printf("my_nm: '%s': No such file\n", filename);
	else if (type == WRONG_FILE)
		printf("my_nm: %s: File format not recognized\n", filename);
	else if (type == ORDINARY_FILE)
		printf("my_nm: Warning: '%s' is not an ordinary file\n",
	filename);
	else if (type == NO_SYMBOLS)
		printf("my_nm: %s: No symbols\n", filename);
	return (84);

}

int elf_check_file(Elf64_Ehdr *hdr)
{
	if (!hdr)
		return (0);
	return (hdr->e_ident[EI_MAG0] == ELFMAG0 &&
	hdr->e_ident[EI_MAG1] == ELFMAG1
	&& hdr->e_ident[EI_MAG2] == ELFMAG2 &&
	hdr->e_ident[EI_MAG3] == ELFMAG3);
}

static int parse64(char *data, const char *filename)
{
	Elf64_Ehdr *hdr;
	t_symbolInfo **symbols;

	hdr = (Elf64_Ehdr *) data;
	if (elf_check_file(hdr) == FALSE)
		return (print_errors(filename, WRONG_FILE));
	if ((symbols = create_symbols_tab(hdr, data)) == NULL)
		return (print_errors(filename, NO_SYMBOLS));
	bubble_sort(symbols);
	print_symbols(symbols);
	free_tab(symbols);
	return (0);
}

static int start_nm(const char *filename)
{
	char *data;
	struct stat s;
	int fd, res;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (print_errors(filename, NO_FILE));
	fstat(fd, &s);
	if (S_ISREG(s.st_mode) == 0)
		return (print_errors(filename, ORDINARY_FILE));
	data = mmap(NULL, (size_t) s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (data != NULL) {
		if (data[EI_CLASS] == ELFCLASS64)
			res = parse64(data, filename);
		else if (data[EI_CLASS] == ELFCLASS32)
			res = parse32(data, filename);
		else
			return (print_errors(filename, WRONG_FILE));
		return (res);
	}
	return (84);
}

int main (int ac , char ** av)
{
	int res, returnValue = 0;

	setlocale(LC_COLLATE, "");
	if (ac == 1)
		return (start_nm("a.out"));
	if (ac == 2)
		return (start_nm(av[1]));
	for (int i = 1; i < ac; i++) {
		printf("\n%s:\n", av[i]);
		res = start_nm(av[i]);
		if (res == 1)
			returnValue = 0;
	}
	return (returnValue);
}
