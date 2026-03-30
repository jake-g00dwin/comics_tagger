/*
 * Author: username
 * Date: todays_date 
 * filename: test_cvectors.c
 * description: module_purpose
 */

#include "CppUTest/CommandLineTestRunner.h"

extern "C" 
{
#include "cvectors.h"
}


static size_t calloc_count = 0;
static size_t malloc_count = 0;
static size_t free_count = 0;

static void *calloc_impl(size_t number, size_t size);
static void *malloc_impl(size_t size);
static void free_impl(void *ptr);

TEST_GROUP(tg_cvectors)
{
    void setup()
    {
        UT_PTR_SET(calloc_fn, calloc_impl);
        UT_PTR_SET(malloc_fn, malloc_impl);
        UT_PTR_SET(free_fn, free_impl);
        calloc_count = 0;
        malloc_count = 0;
        free_count = 0;
    }
    void teardown()
    {

    }
};

void *calloc_impl(size_t number, size_t size)
{
    calloc_count += 1;
    return calloc(number, size);
}

void *malloc_impl(size_t size)
{
    malloc_count += 1;
    return malloc(size);
}

void free_impl(void *ptr)
{
    free_count += 1;
    free(ptr);
}

TEST(tg_cvectors, cvec_sizeFailsOnNull)
{
    cvec_t *vec = NULL;
    result_size_t r = cvec_size(vec);
    CHECK_TRUE(!r.is_ok);
    CHECK_TRUE(r.error == status_std_null_ptr);
}


TEST(tg_cvectors, cvec_capacityFailsOnNull)
{
    cvec_t *vec = NULL;
    result_size_t r = cvec_capacity(vec);
    CHECK_TRUE(!r.is_ok);
    CHECK_TRUE(r.error == status_std_null_ptr);
}

TEST(tg_cvectors, createfailsonzerosize)
{
    size_t element_size = 0;
    cvec_t *vec_ptr = cvec_create(element_size);

    CHECK_EQUAL_TEXT(NULL, vec_ptr,"The vector ptr should be null on create failure.");
}

TEST(tg_cvectors, createallocatesmemory)
{
    result_int_t ri;
    result_size_t rs;
    cvec_t *vec_u8_ptr = cvec_create(sizeof(uint8_t));
    if(!vec_u8_ptr){
        FAIL("Returned vector is NULL");
    }
    
    CHECK_EQUAL_TEXT(1, malloc_count, "Incorrect value: malloc_count");
    CHECK_EQUAL_TEXT(1, calloc_count, "Incorrect value: calloc_count");

    rs = cvec_capacity(vec_u8_ptr);
    CHECK_EQUAL_TEXT(
            CVEC_DEFAULT_CAPACITY,
            rs.value,
            "Initialized with incorrect capacity.");
    rs = cvec_size(vec_u8_ptr);
    CHECK_EQUAL_TEXT(0, rs.value, "Initialized with incorrect size.");


    ri = cvec_destroy(vec_u8_ptr);
    CHECK_TRUE_TEXT(ri.is_ok, "Result of cvec_destroy() is not ok.");
    CHECK_EQUAL_TEXT(2, free_count, "Incorrect value: free_count");
}

TEST(tg_cvectors, getElementFailsOnNull)
{
    cvec_t *vec = NULL;
    result_void_pt rvp = cvec_get(vec, 0);
    CHECK_FALSE(rvp.is_ok);
    CHECK_EQUAL(status_std_null_ptr, rvp.error);
}

TEST(tg_cvectors, getElementFailsOnInvalidIndexLessThan)
{
    cvec_t *vec = cvec_create(sizeof(uint8_t));
    result_void_pt rvp = cvec_get(vec, 0);
    
    CHECK_FALSE(rvp.is_ok);
    CHECK_EQUAL(status_std_invalid_arg, rvp.error);

    CHECK_TRUE(cvec_destroy(vec).is_ok);
}

TEST(tg_cvectors, appendFailsOnNullVec)
{
    cvec_t *vec = NULL;
    uint8_t value = 255;
    CHECK_FALSE(cvec_append(vec, &value).is_ok);
}

TEST(tg_cvectors, appendFailsOnNullData)
{
    cvec_t *vec = cvec_create(sizeof(uint8_t));

    CHECK_FALSE(cvec_append(vec, NULL).is_ok);
    CHECK_TRUE(cvec_destroy(vec).is_ok);
}

TEST(tg_cvectors, appendGetOkOnValidVec)
{
    result_size_t rsz;
    result_void_pt rvp;

    cvec_t *vec = cvec_create(sizeof(uint8_t));
    uint8_t value = 255;
    CHECK_TRUE(cvec_append(vec, &value).is_ok);
    
    rsz = cvec_size(vec);
    CHECK_EQUAL(1, rsz.value); 

    rvp = cvec_get(vec, 0);    
    uint8_t *out = (uint8_t *)rvp.value;

    CHECK_TRUE(out != NULL);
    CHECK_EQUAL(value, (*out));

    CHECK_TRUE(cvec_destroy(vec).is_ok);
}

TEST(tg_cvectors, appendGetGrowsCapacity)
{
    result_size_t rsize;
    result_size_t rcap;
    cvec_t *vec = cvec_create(sizeof(uint8_t));
    size_t calloc_count_init = calloc_count;
    size_t free_count_init = free_count;

    for(uint8_t i = 0; i < 255; i++){
        //CHECK_EQUAL(result_ok, cvec_append(vec, &i));
        CHECK_TRUE(cvec_append(vec, &i).is_ok);
        rsize = cvec_size(vec);
        CHECK_EQUAL(i + 1, rsize.value);
    }

    //Assuming doubling we should see an equal number of frees and allocs
    CHECK_TRUE(calloc_count - calloc_count_init == free_count - free_count_init);

    rsize = cvec_size(vec);
    rcap = cvec_capacity(vec);
    CHECK_TRUE(rcap.value > rsize.value);
    CHECK_TRUE(cvec_capacity(vec).value > cvec_size(vec).value);

    CHECK_TRUE(cvec_destroy(vec).is_ok);
}

TEST(tg_cvectors, popFailsOnEmptyVector)
{

}

TEST(tg_cvectors, popFailsOnNullVector)
{

}


TEST_GROUP(tg_cvec_populated)
{
    const size_t prealloced_elements = 16;
    cvec_t *vec_ptr; 
    void setup()
    {
        UT_PTR_SET(calloc_fn, calloc_impl);
        UT_PTR_SET(malloc_fn, malloc_impl);
        UT_PTR_SET(free_fn, free_impl);

        vec_ptr = cvec_create(sizeof(uint8_t));
        CHECK_TRUE(vec_ptr != NULL);

        for(uint8_t i = 0; i < prealloced_elements; i++){
            cvec_append(vec_ptr, &i);
        }

        calloc_count = 0;
        malloc_count = 0;
        free_count = 0;
    }
    void teardown()
    {
        CHECK_TRUE_TEXT(free_count == (calloc_count + malloc_count), "Number of allocated call != free'd calls.");
        CHECK_TRUE(cvec_destroy(vec_ptr).is_ok);
    }
};

TEST(tg_cvec_populated, popShrinksVectorCapacity)
{
    
}
