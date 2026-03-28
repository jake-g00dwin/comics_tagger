/*
 * Author: username
 * Date: todays_date 
 * filename: test_cbz.c
 * description: module_purpose
 */

#include "CppUTest/CommandLineTestRunner.h"
//#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C" 
{
#include "cbz.h"
//#include "mem_mock.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
}

size_t calloc_count = 0;
size_t malloc_count = 0;
size_t free_count = 0;


void *calloc_impl(size_t number, size_t size);
void free_impl(void *ptr);

TEST_GROUP(tg_cbz)
{

    void setup()
    {

        UT_PTR_SET(calloc_fn, calloc_impl);
        UT_PTR_SET(free_fn, free_impl);
        calloc_count = 0;
        malloc_count = 0;
        free_count = 0;
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


void *calloc_impl(size_t number, size_t size)
{
    calloc_count += 1;
    return calloc(number, size);
}
//void *(*calloc_fn)(size_t number, size_t size) = calloc_impl;

void free_impl(void *ptr)
{
    free_count += 1;
    free(ptr);
}
//void (*free_fn)(void *ptr) = free_impl;

TEST(tg_cbz, dynamicmemorytrackercounts)
{
    int *mem_ptr = (int *)calloc_fn(8, sizeof(int));
    if(!mem_ptr){
        FAIL("mem_ptr == NULL");
    }

    CHECK_EQUAL_TEXT(1, calloc_count, "calloc_count != 1");

    free_fn(mem_ptr);

    CHECK_EQUAL_TEXT(calloc_count, free_count, "Number of allocs and free !=");
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
    CHECK_EQUAL(CBZ_DEFAULT_ISSUE, md.issue);
    STRCMP_EQUAL("english", md.language);
    STRCMP_EQUAL("", md.description);
    CHECK_EQUAL(0, md.tag_vector.length);
    CHECK_EQUAL(CBZ_DEFAULT_TAGVEC_CAP, md.tag_vector.capacity);

    CHECK_TRUE(cbz_free_metadata(&md) == STATUS_OK);

    CHECK_EQUAL(NULL, md.title);
    CHECK_EQUAL(NULL, md.series);
    CHECK_EQUAL(NULL, md.author);
    CHECK_EQUAL(NULL, md.publisher);
    CHECK_EQUAL(NULL, md.language);
    CHECK_EQUAL(NULL, md.description);

    CHECK_EQUAL(NULL, md.tag_vector.tags);
    CHECK_EQUAL(0, md.tag_vector.length);
    CHECK_EQUAL(0, md.tag_vector.capacity);

    CHECK_EQUAL_TEXT(calloc_count, free_count, "Number of allocs and free !=");
}

TEST(tg_cbz, free_metadata_ignoresNulls)
{
    cbz_metadata_t md;
    CHECK_TRUE(cbz_free_metadata(&md) == STATUS_ERR);
}

TEST(tg_cbz, tag_vector_inits_empty)
{
    metadata_tag_vec_t tag_vec;
    CHECK_EQUAL(STATUS_OK, cbz_tag_vec_init(&tag_vec));

    CHECK_EQUAL(NULL, tag_vec.tags);
    CHECK_EQUAL(0, tag_vec.length);
    CHECK_EQUAL(0, tag_vec.capacity);
    
    //CHECK_EQUAL_TEXT(1, calloc_count, "Expected memory not allocated.");
}

TEST(tg_cbz, tag_vector_inits_rejects_nullptr)
{
    metadata_tag_vec_t *tag_vec = NULL;
    CHECK_EQUAL(STATUS_ERR, cbz_tag_vec_init(tag_vec));
}

TEST(tg_cbz, tag_vector_set_capacity)
{
    metadata_tag_vec_t tag_vec;
    CHECK_EQUAL(STATUS_OK, cbz_tag_vec_init(&tag_vec));
    
    CHECK_EQUAL(STATUS_OK, cbz_tag_vec_set_capacity(&tag_vec, 10));
    CHECK_EQUAL(10, tag_vec.capacity);
    CHECK_TRUE(tag_vec.tags != NULL);
    CHECK_EQUAL(10, calloc_count);
    
    CHECK_EQUAL(STATUS_OK, cbz_tag_vec_set_capacity(&tag_vec, 12));
    CHECK_EQUAL(12, tag_vec.capacity);
    CHECK_TRUE(tag_vec.tags != NULL);
    CHECK_EQUAL(12, calloc_count);
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
