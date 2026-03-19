/*
 * Author: username
 * Date: todays_date 
 * filename: test_module_name.c
 * description: module_purpose
 */

#include "CppUTest/CommandLineTestRunner.h"

extern "C" 
{
#include "module_name.h"
}

TEST_GROUP(tg_module_name)
{
    void setup()
    {

    }
    void teardown()
    {

    }
};

TEST(tg_module_name, FirstTest)
{
   FAIL("Fail me!");
}

TEST(tg_module_name, SecondTest)
{
   STRCMP_EQUAL("hello", "world");
   LONGS_EQUAL(1, 2);
   CHECK(false);
}

