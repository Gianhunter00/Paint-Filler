#pragma once
#include <string.h>
#include <stdlib.h>

static char *concat_path(const char *base, const char *name)
{
    int dest_size = (strlen(base) + strlen(name)) + 1;
    char *dest = (char *)malloc(dest_size);
    dest[0] = '\0';
    strcat_s(dest, dest_size, base);
    strcat_s(dest, dest_size, name);
    return dest;
}