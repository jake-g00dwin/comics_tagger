/*
 * Author: Jake G
 * Date: 2026
 * filename: result_returns.c
 * description: module_purpose
 */

#include "result_returns.h"

// dumb test function
result_int_t add_two(int a)
{
    int b = a;
    b += 2;
    if (b == 42)
    {
        return ERR(-1, result_int_t);
    }
    return OK(b, result_int_t);
}
