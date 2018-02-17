//
// Created by NANAA on 16/02/18.
//

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

int get_size(t_symbolInfo **symbols)
{
    int i;

    for (i = 0; symbols[i] != NULL; i++);
    return i;
}

void free_tab(t_symbolInfo **symbols)
{
    for (int i = 0; symbols[i] != NULL; i++) {
        free(symbols[i]);
    }
    free(symbols);
}

void reorder(t_symbolInfo **symbols)
{
    int size = get_size(symbols);
    t_symbolInfo *temp;

    for (int i = 0; i < size; i++) {
        if (strcmp(symbols[i]->name, "data_start") == 0)
        {
            temp = symbols[i + 1];
            symbols[i + 1] = symbols[i];
            symbols[i] = temp;
            i++;
        }
    }
}

void bubble_sort(t_symbolInfo **symbols)
{
    char *first;
    char *second;
    t_symbolInfo *temp;

    for (int i = get_size(symbols); i > 1; i--) {
        for (int j = 0; j < i - 1; j++) {
            second = to_lower_and_ignore_underscore(symbols[j + 1]->name);
            first = to_lower_and_ignore_underscore(symbols[j]->name);
            if (strcmp(first, second) > 0) {
                temp = symbols[j];
                symbols[j] = symbols[j + 1];
                symbols[j + 1] = temp;
            }
            free(second);
            free(first);
        }
    }
    reorder(symbols);
}