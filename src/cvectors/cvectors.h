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

#include "result_returns.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef CVEC_DEFAULT_CAPACITY
#define CVEC_DEFAULT_CAPACITY 8
#endif

    typedef struct cvec_t cvec_t;

    DEFINE_RESULT(cvec_t *, result_cvec_pt)

    typedef enum
    {
        result_ok                  = 0,
        result_err                 = 1,
        result_alloc_err           = 2,
        result_invalid_index_err   = 3,
        result_invalid_vector_ptr  = 4,
        result_invalid_element_ptr = 5,
    } result_status;

    /*
    typedef struct
    {
        result_status status;
        union
        {
            void  *value;
            size_t size;
            int    error;
        };
    } result_t;
    */

    /*
    typedef struct
    {
        result_status status;
        union
        {
            size_t value;
            int    error;
        };
    } result_size_t;
    */

    /*
    typedef struct
    {
        result_status status;
        union
        {
            cvec_t *value;
            int     error;
        };
    } result_cvec_t;
    */

    /**
     * @brief Creates new vector in dynamic memory.
     * @param[in] element_size The size of the elements in bytes.
     * @return C vector type(`cvec_t`), initialized to CVEC_DEFAULT_CAPACITY that is allocated.
     * @see cvec_t The C vector structure type.
     */
    result_cvec_pt cvec_create(size_t element_size);

    /**
     * @brief Destroy's and frees all used memory allocated by the vector.
     * @param[in] vec pointer to the vector to be destroyed.
     * @return Status code.
     * The function frees the data allocated to the data field as well as the
     * vector structure itself.
     */
    result_int_t cvec_destroy(cvec_t *vec);

    /**
     * @brief Gets a indexed values address from the passed vector.
     * @param[in] C vector type pointer.
     * @param[in] index the index of the desired element.
     * @return A void pointer to the indexed element.
     * On failure the function returns NULL.
     */
    result_void_pt cvec_get(cvec_t *vec, size_t index);

    /**
     * @brief Appends passed value onto the end of the vector.
     * @param[in] vec C vector type pointer.
     * @param[in] in The address of the value/variable to append.
     * @return Status code.
     * The two passed parameter's must be valid non-null addresses.
     */
    result_int_t cvec_append(cvec_t *vec, const void *in);

    /**
     * @brief Pops last element off the vector.
     * @param[in] vec C vector type pointer.
     * @param[out] out The address of the place to store the poped value.
     * @return Status code.
     */
    int cvec_pop(cvec_t *vec, int *out);

    /**
     * @brief Inserts the passed value into the indexed location.
     * @param[in] vec C vector type pointer.
     * @param[in] in The address of the element to insert.
     * @return Status code.
     * The insert operation can only insert with the current size of the
     * vector, not the capacity.
     *
     */
    int cvec_insert(cvec_t *vec, const void *in, size_t index);

    /**
     * @brief Deletes the indexed value from the vector.
     * @param[in] vec C vector type pointer.
     * @param[in] index The index of the element to be deleted.
     * @return Status code.
     * The delete operation is computationally expensive as it requires we
     * shift the existing elements.
     *
     */
    int cvec_delete_element(cvec_t *vec, size_t index);

    /**
     * @brief Deletes all elements in the vector.
     * @param[in] vec C vector type pointer.
     * @param[in] free_memory Free's allocated memory if true.
     * @return Status code.
     *
     * This function changes the structures size value to zero. The capacity
     * of the vector isn't changed unless the free_memory flag is passed as
     * true.
     */
    int cvec_delete_data(cvec_t *vec, bool free_memory);

    /**
     * @brief Creates a new vector in memory using supplied range.
     * @param[in] vec C vector type pointer.
     * @param[in] start The starting index of the slice(inclusive).
     * @param[in] end The ending index of the slice(inclusive).
     * @return C vector slice with size [`start`, `end`].
     */
    cvec_t *cvec_slice(cvec_t *vec, size_t start, size_t end);

    /**
     * @brief Creates a new vector in memory that's an exact copy.
     * @param[in] vec C vector type pointer.
     * @return C vector with same size and contents.
     */
    cvec_t *cvec_clone(cvec_t *vec);

    /**
     * @brief Gets the size of the vector, number of elements.
     * @param[in] vec C vector type pointer.
     * @return Number of elements in vector.
     */
    result_size_t cvec_size(cvec_t *vec);

    /**
     * @brief Gets the capacity of the vector, allocated elements.
     * @param[in] vec C vector type pointer.
     * @return The capacity of the vector in terms of elements.
     *
     * The capacity of the vector is how much memory has actually been allocated
     * for the vector to store elements.
     *
     * When the capacity of the vector is exceeded the vector reallocates
     * more memory and copies over the elements from the previous address if
     * needed.
     */
    result_size_t cvec_capacity(cvec_t *vec);

    // Externally defined function pointer.
    /**
     * @brief Externally defined memory allocation function pointer.
     * @param[in] size The size in bytes of memory to be allocated.
     * @return Pointer address to the allocated memory.
     * Used mostly for testing for TDD.
     */
    extern void *(*malloc_fn)(size_t size);

    /**
     * @brief Externally defined memory allocation function pointer.
     * @param[in] number The number of elements to allocate for.
     * @param[in] size The size in bytes of memory to be allocated.
     * @return Pointer address to the allocated memory.
     *
     * Used mostly for testing for TDD. For examples of useage see the
     * `tests/cvectors/test_cvectors.cpp` file.
     */
    extern void *(*calloc_fn)(size_t number, size_t size);

    /**
     * @brief Externally defined memory freeing function pointer.
     * @param[in] ptr The pointer to the memory to be free'd.
     *
     * Used mostly for testing for TDD.
     */
    extern void (*free_fn)(void *ptr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // cvectors_H
