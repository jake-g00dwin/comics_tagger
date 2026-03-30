/**
 * @brief Comperhensive result returns module.
 * @details Designed to provide custon return types for error handling.
 * @author Jake G
 * @date 2026
 * @copyright None
 * @file result_returns.h
 *
 * To use this module simply include the header and you can define your own
 * custom return types using the `DEFINE_RESULT` macro.
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

/**
 * @brief Ok status return macro.
 * @param[in] val The value of the result type to return.
 * @param[in] type The result return type to hold the value.
 *
 */
#define OK(val, type) ((type){.is_ok = true, .value = (val)})
/**
 * @brief ERR status return macro.
 * @param[in] err The error code `int` type to return int the result.
 * @param[in] type The result return type to hold the value.
 */
#define ERR(err, type) ((type){.is_ok = false, .error = (err)})

/**
 * @brief Macro `DEFINE_RESULT` creates new result type for verbose returns.
 * @param[in] T The type of the value it should hold on ok returns.
 * @param[in] name The new typedef name to use for the created result type.
 *
 * The macro's generated types make use of the a `union` type to allow it to
 * hold either a value of the passed type, or a error code of the int type that
 * we can use enums for.
 *
 * To quickly return a result from a function without any errors we can use
 * the `OK` macro or the `ERR` macro.
 */
#define DEFINE_RESULT(T, name) \
    typedef struct             \
    {                          \
        bool is_ok;            \
        union                  \
        {                      \
            T   value;         \
            int error;         \
        };                     \
    } name;

    // Typedefs, structures and custom types.
    typedef enum
    {
        status_std_ok = 0,
        status_std_err,
        status_std_null_ptr,
        status_std_invalid_arg,
        status_std_alloc_failure,
    } result_std_status;

    /**
     * @brief Simple no value return type, used in palce of bools.
     */
    typedef struct
    {
        bool is_okay;
        int  error;
    } result_t;

    // Built-in Result Types.
    DEFINE_RESULT(int, result_int_t)
    DEFINE_RESULT(char, result_char_t)
    DEFINE_RESULT(bool, result_bool_t)
    DEFINE_RESULT(unsigned int, result_uint_t)
    DEFINE_RESULT(float, result_float_t)

    DEFINE_RESULT(size_t, result_size_t)

    // Fixed width portable types.
    DEFINE_RESULT(uint8_t, result_u8_t)
    DEFINE_RESULT(uint16_t, result_u16_t)
    DEFINE_RESULT(uint32_t, result_u32_t)
    DEFINE_RESULT(uint64_t, result_u64_t)
    DEFINE_RESULT(int8_t, result_i8_t)
    DEFINE_RESULT(int16_t, result_i16_t)
    DEFINE_RESULT(int32_t, result_i32_t)
    DEFINE_RESULT(int64_t, result_i64_t)

    // Pointer result types.
    DEFINE_RESULT(void *, result_void_pt)
    DEFINE_RESULT(int *, result_i_pt)
    DEFINE_RESULT(unsigned int *, result_ui_pt)
    DEFINE_RESULT(char *, result_char_pt)
    DEFINE_RESULT(float *, result_float_pt)

    // Function Prototypes.

    /**
     * @brief A simple test function, don't use.
     */
    result_int_t add_two(int a);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // result_returns_H
