#include "CppUTest/TestHarness.h"

/*
extern C 
{
#include "simple.h"
}
*/


TEST_GROUP(simple_test)
{
    void setup()
    {

    }
    void teardown()
    {

    }
};

TEST(simple_test, passing_test)
{
    CHECK_TRUE(1);
}
