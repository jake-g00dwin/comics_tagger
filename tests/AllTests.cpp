#include "CppUTest/CommandLineTestRunner.h"


//ImportTestGroups
IMPORT_TEST_GROUP(simple_test);

//START: main
int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}
//END: main
