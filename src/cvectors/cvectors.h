/**
 * @brief Vector implimentation written in C.
 * @details This file is the header for the cvector lib.
 * @author Jake G
 * @date 2026
 * @copyright None
 * @file cvectors.h
 */

// #pragma once
#ifndef cvectors_H
#define cvectors_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
    /*
    typedef struct{
        void *ptrs;
        size_t length;
        size_t capacity;
    }cvec_ptr_t;

    typedef struct{
        int (*len)(void);
        int (*append)(cvec_type);
        int (*pop)(void);
        int (*push)(void);
    }cvec_t;
    */

#ifndef CVEC_DEFAULT_CAPACITY
#define CVEC_DEFAULT_CAPACITY 8
#endif

    enum
    {
        cvec_ok                = 0,
        cvec_err               = 1,
        cvec_alloc_err         = 2,
        cvec_invalid_index_err = 3,
    };

    typedef struct cvec_status
    {
        int status;
    } cvec_status;

    typedef struct cvec_t cvec_t;

    cvec_t               *cvec_create(size_t element_size);
    int                   cvec_destroy(cvec_t *vec);

    void                 *cvec_get(cvec_t *vec, size_t index);
    int                   cvec_push(cvec_t *vec, const void *in);
    int                   cvec_pop(cvec_t *vec, int *out);

    size_t                cvec_size(cvec_t *vec);
    size_t                cvec_capacity(cvec_t *vec);

    // Externally defined function pointer.
    extern void *(*malloc_fn)(size_t size);
    extern void *(*calloc_fn)(size_t number, size_t size);
    extern void (*free_fn)(void *ptr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // cvectors_H
