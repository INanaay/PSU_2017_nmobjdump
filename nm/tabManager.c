/*
** EPITECH PROJECT, 2018
** tab
** File description:
** tab
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/nm.h"

void print_symbols(t_symbolInfo **symbols)
{
	for (int i = 0; symbols[i] != NULL; i++) {
		if (symbols[i]->value != 0)
			printf("%016lx ", symbols[i]->value);
		else
			printf("                 ");
		printf("%c ", symbols[i]->type);
		printf("%s\n", symbols[i]->name);
	}
}

void print_symbols32(t_symbolInfo **symbols)
{
	for (int i = 0; symbols[i] != NULL; i++) {
		if (symbols[i]->value != 0)
			printf("%08lx ", symbols[i]->value);
		else
			printf("         ");
		printf("%c ", symbols[i]->type);
		printf("%s\n", symbols[i]->name);
	}
}

int get_size(t_symbolInfo **symbols)
{
	int i;

	for (i = 0; symbols[i] != NULL; i++);
	return (i);
}

void free_tab(t_symbolInfo **symbols)
{
	for (int i = 0; symbols[i] != NULL; i++) {
		free(symbols[i]);
	}
	free(symbols);
}

void bubble_sort(t_symbolInfo **symbols)
{
	t_symbolInfo *temp;
	int size = get_size(symbols);

	for (int i = size; i > 1; i--) {
		for (int j = 0; j < i - 1; j++) {
			if (strcoll(symbols[j]->name,
				symbols[j + 1]->name) > 0) {
				temp = symbols[j];
				symbols[j] = symbols[j + 1];
				symbols[j + 1] = temp;
			}
		}
	}
}
