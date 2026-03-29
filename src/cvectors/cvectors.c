/*
 * Author: Jake G
 * Date: 2026
 * filename: cvectors.c
 * description: vector source.
 */

#include "cvectors.h"
#include <string.h>

/**
 * @brief The C void* vector structure.
 */
struct cvec_t
{
    void  *data;         /**<Holds vector elements*/
    size_t size;         /**<Number of elements actual in use.*/
    size_t capacity;     /**<Number of elements possible to use before reallocating.*/
    size_t element_size; /**<The size of the data elements in vector.*/
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
    if (vec->data == NULL) { return result_err; }
    free_fn(vec->data);
    vec->data = NULL;

    if (vec == NULL) { return result_err; }
    free_fn(vec);

    return result_ok;
}

result_size_t cvec_size(cvec_t *vec)
{
    result_size_t r_size = {.status = result_ok, .error = 0};
    if (!vec)
    {
        r_size.status = result_invalid_vector_ptr;
        r_size.error  = result_invalid_index_err;
        return r_size;
    }

    r_size.status = result_ok;
    r_size.value  = vec->size;
    return r_size;
}

size_t cvec_capacity(cvec_t *vec)
{
    if (!vec) { return result_err; }
    // if (vec->data == NULL) { return result_err; }
    return vec->capacity;
}

void *cvec_get(cvec_t *vec, size_t index)
{
    if (!vec) { return NULL; }
    if (index >= vec->size) { return NULL; }
    // data_address + (index * size_of_data_type)

    // We need to use byte level pointer arithmatic to avoid compiler extensions.
    return (char *)vec->data + index + vec->element_size;
}

int cvec_append(cvec_t *vec, const void *in)
{
    if (!vec) { return result_err; }
    if (in == NULL) { return result_err; }

    vec->size += 1;

    // handle the case for when the capacity needs to be increased.
    if (vec->size > vec->capacity)
    {
        void *tmp_data = calloc_fn(vec->capacity * 2, vec->element_size);
        if (!tmp_data) { return result_err; }

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

    return result_ok;
}

int cvec_pop(cvec_t *vec, int *out)
{
    return result_ok;
}

int cvec_insert(cvec_t *vec, const void *in, size_t index)
{
    return result_ok;
}

int cvec_clear_vector(cvec_t *vec)
{
    return result_ok;
}
