/*
 * Author: username
 * Date: todays_date 
 * filename: test_cbz.c
 * description: module_purpose
 */

#include "CppUTest/CommandLineTestRunner.h"

extern "C" 
{
#include "cbz.h"
}

TEST_GROUP(tg_cbz)
{
    void setup()
    {

    }
    void teardown()
    {

    }
};

TEST(tg_cbz, FirstTest)
{
   FAIL("Fail me!");
}

TEST(tg_cbz, SecondTest)
{
   STRCMP_EQUAL("hello", "world");
   LONGS_EQUAL(1, 2);
   CHECK(false);
}

