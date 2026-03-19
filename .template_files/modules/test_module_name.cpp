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

TEST_GROUP(FirstTestGroup)
{
    void setup()
    {

    }
    void teardown()
    {

    }
};

TEST(FirstTestGroup, FirstTest)
{
   FAIL("Fail me!");
}

TEST(FirstTestGroup, SecondTest)
{
   STRCMP_EQUAL("hello", "world");
   LONGS_EQUAL(1, 2);
   CHECK(false);
}

