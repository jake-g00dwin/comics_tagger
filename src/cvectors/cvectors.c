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

result_cvec_pt cvec_create(size_t element_size)
{
    // Check if the input argument is valid.
    if (element_size <= 0) { return ERR(status_std_invalid_arg, result_cvec_pt); }

    cvec_t *vec_ptr = malloc_fn(sizeof(cvec_t));
    // Check if the memory was sucessfully allocated.
    if (!vec_ptr)
    {
        return ERR(status_std_alloc_failure, result_cvec_pt);
    }

    // Initialize the vector to defaults.
    vec_ptr->element_size = element_size;
    vec_ptr->size         = 0;
    vec_ptr->capacity     = CVEC_DEFAULT_CAPACITY;
    vec_ptr->data         = calloc_fn(CVEC_DEFAULT_CAPACITY, element_size);
    // return vec_ptr;
    return OK(vec_ptr, result_cvec_pt);
}

result_int_t cvec_destroy(cvec_t *vec)
{
    if (vec == NULL)
    {
        return ERR(status_std_null_ptr, result_int_t);
    }

    free_fn(vec->data);
    vec->data = NULL;

    free_fn(vec);
    vec = NULL;

    return OK(0, result_int_t);
}

result_size_t cvec_size(cvec_t *vec)
{
    if (!vec)
    {
        return ERR(status_std_null_ptr, result_size_t);
    }
    return OK(vec->size, result_size_t);
}

result_size_t cvec_capacity(cvec_t *vec)
{
    if (!vec)
    {
        return ERR(status_std_null_ptr, result_size_t);
    }
    return OK(vec->capacity, result_size_t);
}

// void *cvec_get(cvec_t *vec, size_t index)
result_void_pt cvec_get(cvec_t *vec, size_t index)
{
    if (!vec)
    {
        return ERR(status_std_null_ptr, result_void_pt);
    }
    if (index >= vec->size)
    {
        return ERR(status_std_invalid_arg, result_void_pt);
    }

    // data_address + (index * size_of_data_type)

    // We need to use byte level pointer arithmatic to avoid compiler extensions.
    // return (char *)vec->data + index + vec->element_size;
    return OK(
        (char *)vec->data + index + vec->element_size,
        result_void_pt);
}

result_int_t cvec_append(cvec_t *vec, const void *in)
{
    // Check that the input's are valid aka not NULL.
    if (!vec) { return ERR(status_std_null_ptr, result_int_t); }
    if (!in) { return ERR(status_std_invalid_arg, result_int_t); }

    vec->size += 1;

    // handle the case for when the capacity needs to be increased.
    if (vec->size > vec->capacity)
    {
        void *tmp_data = calloc_fn(vec->capacity * 2, vec->element_size);
        if (!tmp_data) { return ERR(status_std_alloc_failure, result_int_t); }

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

    return OK(status_std_ok, result_int_t);
}

result_int_t cvec_pop(cvec_t *vec, void *out)
{
    if (!vec) { return ERR(status_std_null_ptr, result_int_t); }
    if (!out) { return ERR(status_std_invalid_arg, result_int_t); }
    if (vec->size <= 0) { return ERR(status_std_err, result_int_t); }

    void *src_data = (char *)vec->data + (vec->size * vec->element_size);
    memcpy(out, src_data, vec->element_size);
    vec->size -= 1;

    return OK(status_std_ok, result_int_t);
}

result_int_t cvec_insert(cvec_t *vec, const void *in, size_t index)
{
    return OK(status_std_ok, result_int_t);
}

result_int_t cvec_clear_vector(cvec_t *vec)
{
    return OK(status_std_ok, result_int_t);
}

result_cvec_pt cvec_clone(cvec_t *vec)
{
    if (!vec) { return ERR(status_std_null_ptr, result_cvec_pt); }
    result_cvec_pt rcv = cvec_create(vec->element_size);

    // If the creation failed we just pass it along.
    if (!rcv.is_ok) { return rcv; }

    // First free the default data.
    free_fn(rcv.value->data);

    // Copy the size and capacity into new clone.
    rcv.value->size     = vec->size;
    rcv.value->capacity = vec->capacity;

    rcv.value->data     = calloc_fn(vec->capacity, vec->element_size);

    // Check for alloc failure.
    if (!rcv.value->data)
    {
        // First free the newly created vector.
        free_fn(rcv.value);
        return ERR(status_std_alloc_failure, result_cvec_pt);
    }

    memcpy(rcv.value->data, vec->data, (vec->capacity * vec->element_size));

    // void *i_addr = (char *)i_addr + (i * vec->element_size);

    return rcv;
    // return OK(rcv.value, result_cvec_pt);
}
