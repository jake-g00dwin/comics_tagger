/*
 * Author: username
 * Date: todays_date 
 * filename: test_result_returns.c
 * description: module_purpose
 */

#include "CppUTest/CommandLineTestRunner.h"

extern "C" 
{
#include "result_returns.h"
}

TEST_GROUP(tg_result_returns)
{
    void setup()
    {

    }
    void teardown()
    {

    }
};

TEST(tg_result_returns, inttypeworks)
{
    int a = 8;
    result_int_t result_int = add_two(a);
    if(!result_int.is_ok){
        FAIL("Issues, status is not okay.");
    }
    CHECK_EQUAL(8+2, result_int.value);
}

TEST(tg_result_returns, inttypeworks_err)
{
    int a = 40;
    result_int_t result_int = add_two(a);
    if(!result_int.is_ok){
        CHECK_EQUAL(42, a + 2);
        CHECK_EQUAL(-1, result_int.error);
    }
    else{
    FAIL("Incorrect status type.");
    }
}

