#include "CppUTest/CommandLineTestRunner.h"


//ImportTestGroups
IMPORT_TEST_GROUP(simple_test);
IMPORT_TEST_GROUP(tg_cbz);
IMPORT_TEST_GROUP(tg_cvectors);
IMPORT_TEST_GROUP(tg_result_returns);

//START: main
int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}
//END: main
