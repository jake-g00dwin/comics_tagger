/*
 * Author: Jake G
 * Date: 2026
 * filename: cvectors.c
 * description: vector source.
 */

#include "cvectors.h"
#include <string.h>

struct cvec_t
{
    void  *data;
    size_t size;         // Number of elements actual in use.
    size_t capacity;     // Number of elements possible to use before reallocating.
    size_t element_size; // The size of the data elements in vector.
};

cvec_t *cvec_create(size_t element_size)
{
    if (element_size <= 0) { return NULL; }

    cvec_t *vec_ptr = malloc_fn(sizeof(cvec_t));
    if (!vec_ptr) { return NULL; }

    vec_ptr->element_size = element_size;
    vec_ptr->size         = 0;
    vec_ptr->capacity     = CVEC_DEFAULT_CAPACITY;
    vec_ptr->data         = calloc_fn(CVEC_DEFAULT_CAPACITY, element_size);
    return vec_ptr;
}

int cvec_destroy(cvec_t *vec)
{
    if (vec->data == NULL) { return cvec_err; }
    free_fn(vec->data);
    vec->data = NULL;

    if (vec == NULL) { return cvec_err; }
    free_fn(vec);

    return cvec_ok;
}

size_t cvec_size(cvec_t *vec)
{
    if (!vec) { return cvec_err; }
    // if (vec->data == NULL) { return cvec_err; }
    return vec->size;
}

size_t cvec_capacity(cvec_t *vec)
{
    if (!vec) { return cvec_err; }
    // if (vec->data == NULL) { return cvec_err; }
    return vec->capacity;
}

void *cvec_get(cvec_t *vec, size_t index)
{
    if (!vec) { return NULL; }
    if (index >= vec->size) { return NULL; }
    // data_address + (index * size_of_data_type)

    // We need to use byte level pointer arithmatic to avoid compiler extensions.
    /*
    char* data_ptr = (char *)vec->data;
    data_ptr = (data_ptr + (index * vec->element_size));
    return data_ptr;
    */
    return (char *)vec->data + index + vec->element_size;
}

int cvec_append(cvec_t *vec, const void *in)
{
    if (!vec) { return cvec_err; }
    if (in == NULL) { return cvec_err; }

    vec->size += 1;

    // handle the case for when the capacity needs to be increased.
    if (vec->size > vec->capacity)
    {
        void *tmp_data = calloc_fn(vec->capacity * 2, vec->element_size);
        if (!tmp_data) { return cvec_err; }

        memcpy((char *)tmp_data,
               (char *)vec->data,
               vec->element_size * vec->size);
        free_fn(vec->data);
        vec->data     = tmp_data;
        vec->capacity = vec->capacity * 2;
    }

    memcpy((char *)vec->data + vec->size * vec->element_size,
           in,
           vec->element_size);

    return cvec_ok;
}
