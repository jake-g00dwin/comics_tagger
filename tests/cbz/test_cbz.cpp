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
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
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

bool file_exists(const char *filename)
{
    struct stat st;
    if(stat(filename, &st) == 0){
        //File Exists, so we need to remove it.
        return true;
    }
    return false;
}

TEST(tg_cbz, initmetadata_allocates)
{
    cbz_metadata_t md; 
    CHECK_EQUAL(STATUS_OK, cbz_init_metadata(&md));
   
    CHECK_TRUE(md.is_initialized);

    STRCMP_EQUAL("default_title", md.title);
    STRCMP_EQUAL("", md.series);
    STRCMP_EQUAL("", md.author);
    STRCMP_EQUAL("", md.publisher);
    CHECK_EQUAL(CBZ_DEFAULT_YEAR, md.year);
    CHECK_EQUAL(CBZ_DEFAULT_MONTH, md.month);
    CHECK_EQUAL(CBZ_DEFAULT_DAY, md.day);

    CHECK_TRUE(cbz_free_metadata(&md) == STATUS_OK);

    CHECK_EQUAL(NULL, md.title);
    CHECK_EQUAL(NULL, md.series);
    CHECK_EQUAL(NULL, md.author);
    CHECK_EQUAL(NULL, md.publisher);
}

TEST(tg_cbz, free_metadata_ignoresNulls)
{
    cbz_metadata_t md;
    CHECK_TRUE(cbz_free_metadata(&md) == STATUS_ERR);
}

/*
TEST(tg_cbz, cbzcreate_makesfile){
    CHECK(false);
    
    const char * filename = "/tmp/example.cbz";
    struct stat st;

    //Check for existance of file before test.

    if(stat(filename, &st) == 0){
        //File Exists, so we need to remove it.
    }

    //Create the cbz file.
    cbz_t test_comic;
    CHECK_TRUE(cbz_create() == 0);
    
    //Check if the CBZ was correctly created.
    if(stat(filename, &st) != 0){
        FAIL("The expected file doesn't exist.");
    }

    //Cleanup/delete the test file.
    if(remove(filename) != 0){
        FAIL("Error: failed to remove file.")
    }
}
*/
