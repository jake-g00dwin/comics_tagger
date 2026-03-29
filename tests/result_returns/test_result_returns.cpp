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

TEST(tg_result_returns, FirstTest)
{
   FAIL("Fail me!");
}

TEST(tg_result_returns, SecondTest)
{
   STRCMP_EQUAL("hello", "world");
   LONGS_EQUAL(1, 2);
   CHECK(false);
}

