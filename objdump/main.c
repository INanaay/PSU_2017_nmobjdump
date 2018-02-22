/*
** EPITECH PROJECT, 2018
** dfd
** File description:
** df
*/

#include "stdio.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "../include/objdump.h"

int elf_check_file(Elf64_Ehdr *hdr)
{
	if (!hdr)
		return (0);
	return (hdr->e_ident[EI_MAG0] == ELFMAG0 &&
			hdr->e_ident[EI_MAG1] == ELFMAG1
		&& hdr->e_ident[EI_MAG2] == ELFMAG2 &&
			hdr->e_ident[EI_MAG3] == ELFMAG3);
}

int print_errors(const char *name, int type)
{
	if (type == NOFILE)
		printf("objdump: '%s': No such file\n", name);
	else if (type == ORDINARYFILE)
		printf("objdump: Warning: '%s' is not an ordinary file\n",
			name);
	else if (type == WRONGFILE)
		printf("objdump: %s: File format not recognized\n", name);
	return (84);
}

static int start_objump(const char *filename)
{
	char *data;
	struct stat s;
	int fd, res = 84;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (print_errors(filename, NOFILE));
	fstat(fd, &s);
	if (S_ISREG(s.st_mode) == 0)
		return (print_errors(filename, ORDINARYFILE));
	data = mmap(NULL, (size_t) s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (data != NULL) {
		if (data[EI_CLASS] == ELFCLASS64)
			parse64(data, filename);
		else if (data[EI_CLASS] == ELFCLASS32)
			parse32(data, filename);
		return (res);
	}
	return (print_errors(filename, WRONGFILE));
}

int main(int ac, char **av)
{
	int res = 0;

	if (ac == 1)
		return (start_objump("a.out"));
	for (int i = 1; i < ac; i++)
		res = start_objump(av[i]);
	return (res);
}
