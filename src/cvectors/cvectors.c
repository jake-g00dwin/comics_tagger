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

    memcpy(rcv.value->data, vec->data, (vec->size * vec->element_size));
    return rcv;
}

static bool increase_capacity(cvec_t *vec, size_t new_capacity)
{
    // I don't do any null vec checking here as this is only for internal use.

    // Check if new capacity is larger than old capacity.
    if (new_capacity <= vec->capacity) { return false; }

    // Hold the old memory data address.
    void *old_data = vec->data;

    // Allocate new memory.
    vec->data = NULL;
    vec->data = calloc_fn(new_capacity, vec->element_size);
    if (!vec->data) { return false; }

    // Now that we know the memory allocated set the size/capacity fields.
    vec->size     = 0;
    vec->capacity = new_capacity;

    // arguments: destination, source, number of bytes.
    memcpy(vec->data, old_data, (vec->size * vec->element_size));

    // Fre The old address.
    free_fn(old_data);

    return true;
}

result_cvec_pt cvec_slice(cvec_t *vec, size_t start, size_t end)
{
    if (!vec) { return ERR(status_std_null_ptr, result_cvec_pt); }
    if (start > vec->size) { return ERR(status_std_invalid_arg, result_cvec_pt); }
    if (end > vec->size) { return ERR(status_std_invalid_arg, result_cvec_pt); }
    if (end <= start) { return ERR(status_std_invalid_arg, result_cvec_pt); }

    result_cvec_pt rcv = cvec_create(vec->element_size);
    if (!rcv.is_ok) { return rcv; }

    // Add the specified range of elements using memcpy function.
    // Example: say we get the range [0-7] = 8 elements. --> (7-0)+1 = num.
    size_t new_size = (end - start) + 1;

    if (!increase_capacity(rcv.value, new_size))
    {
        // We failed to reallocate the neede memory.
        // Free the newly created cvector and return the error.
        free_fn(rcv.value);
        ERR(status_std_alloc_failure, result_cvec_pt);
    }

    // Calculate the first element's address that we will copy into the slice.
    void *src_addr = (char *)vec->data + (start * vec->element_size);
    memcpy(rcv.value->data, src_addr, (new_size * vec->element_size));
    rcv.value->size = new_size;

    return rcv;
}
