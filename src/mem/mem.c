/*
 * Author: username
 * Date: 2026
 * filename: mem.c
 * description: module_purpose
 */

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

void *wrap_malloc(size_t size)
{
    return malloc(size);
}

void *wrap_calloc(size_t number, size_t size)
{
    return calloc(number, size);
}

void wrap_free(void *ptr)
{
    free(ptr);
}

bool wrap_free_sec(void **ptr)
{
    if (ptr == NULL || *ptr == NULL)
    {
        return false;
    }

    free(*ptr);
    *ptr = NULL;

    return true;
}
