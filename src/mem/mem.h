/**
 * @brief Module description
 * @details This file is an <Purpose here>
 * @author Jake G
 * @date 2026
 * @copyright None
 * @file mem.h
 */

// #pragma once
#ifndef mem_H
#define mem_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

    void *wrap_malloc(size_t size);
    void *wrap_calloc(size_t number, size_t size);
    void  wrap_free(void *ptr);

    bool  wrap_free_sec(void **ptr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // mem_H
