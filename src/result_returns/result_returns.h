/**
 * @brief Comperhensive result returns module.
 * @details Designed to provide custon return types for error handling.
 * @author Jake G
 * @date 2026
 * @copyright None
 * @file result_returns.h
 */

// #pragma once
#ifndef result_returns_H
#define result_returns_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define OK(val, type) ((type){.is_ok = 1, .value = (val)})
#define ERR(err, type) ((type){.is_ok = 0, .error = (err)})

#define DEFINE_RESULT(T, name) \
    typedef struct             \
    {                          \
        int is_ok;             \
        union                  \
        {                      \
            T   value;         \
            int error;         \
        };                     \
    } name;

    typedef enum
    {
        status_std_ok = 0,
        status_std_err,
        status_std_null_ptr,
        status_std_invalid_arg,
    } result_std_status;

    DEFINE_RESULT(int, result_int_t)
    DEFINE_RESULT(char, result_char_t)
    DEFINE_RESULT(bool, result_bool_t)
    DEFINE_RESULT(unsigned int, result_uint_t)
    DEFINE_RESULT(float, result_float_t)
    DEFINE_RESULT(void *, result_voidp_t)

    DEFINE_RESULT(size_t, result_size_t)

    DEFINE_RESULT(uint8_t, result_u8_t)
    DEFINE_RESULT(uint16_t, result_u16_t)
    DEFINE_RESULT(uint32_t, result_u32_t)
    DEFINE_RESULT(uint64_t, result_u64_t)
    DEFINE_RESULT(int8_t, result_i8_t)
    DEFINE_RESULT(int16_t, result_i16_t)
    DEFINE_RESULT(int32_t, result_i32_t)
    DEFINE_RESULT(int64_t, result_i64_t)

    result_int_t add_two(int a);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // result_returns_H
