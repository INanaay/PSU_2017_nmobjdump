//
// Created by NANAA on 16/02/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/nm.h"

static char char_to_lower(char c)
{
    if (c >= 'A' && c < 'Z')
        return (char) (c + 32);
    return c;
}

char *to_lower_and_ignore_underscore(const char *s)
{
    char *new = calloc(strlen(s) + 1, 1);
    unsigned int beg = 0, y = 0;

    for (unsigned int i = beg; i < strlen(s); i++) {
        if (s[i] == '_' || s[i] == '@')
        {
            continue;
        }
        new[y] = char_to_lower(s[i]);
        y++;
    }
    return new;
}