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
static int fail_after = -1;
static int fail_after_count = 0; 

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
        fail_after = -1;
        fail_after_count = 0;
    }
    void teardown()
    {

    }
};

void *calloc_impl(size_t number, size_t size)
{
    if(fail_after >= 0)
    {
        fail_after_count += 1;
        if(fail_after <= fail_after_count){
            //reset the failure mode.
            fail_after = -1;
            return NULL;
        }
    }

    calloc_count += 1;
    return calloc(number, size);
}

void *malloc_impl(size_t size)
{

    if(fail_after >= 0)
    {
        fail_after_count += 1;
        if(fail_after <= fail_after_count){
            //reset the failure mode.
            fail_after = -1;
            return NULL;
        }
    }

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
    result_cvec_pt rcv = cvec_create(element_size);

    CHECK_FALSE_TEXT(rcv.is_ok, "The vector ptr should be null on create failure.");
    CHECK_TRUE(rcv.value != NULL);
}

TEST(tg_cvectors, createHandlesFailedAlloc)
{
    fail_after = 0; //Causes malloc call to fail on first call.
    
    result_cvec_pt rvec = cvec_create(sizeof(uint8_t));

    CHECK_FALSE(rvec.is_ok);
    CHECK_EQUAL(status_std_alloc_failure, rvec.error);

}

TEST(tg_cvectors, createallocatesmemory)
{
    result_int_t ri;
    result_size_t rs;
    result_cvec_pt rcv = cvec_create(sizeof(uint8_t));
    cvec_t *vec_u8_ptr = rcv.value; 

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
    result_cvec_pt rcv = cvec_create(sizeof(uint8_t));
    cvec_t *vec = rcv.value;
    
    result_void_pt rvp = cvec_get(vec, 0);
    
    CHECK_FALSE(rvp.is_ok);
    CHECK_EQUAL(status_std_invalid_arg, rvp.error);

    CHECK_TRUE(cvec_destroy(vec).is_ok);
}

TEST(tg_cvectors, appendFailsOnNullVec)
{
    cvec_t *vec = NULL;
    uint8_t value = 255;
    result_int_t ri = cvec_append(vec, &value);

    CHECK_FALSE(ri.is_ok);
    CHECK_EQUAL(status_std_null_ptr, ri.error);
}

TEST(tg_cvectors, appendFailsOnNullData)
{
    result_cvec_pt rcv = cvec_create(sizeof(uint8_t));
    cvec_t *vec = rcv.value;
    result_int_t ri = cvec_append(vec, NULL);

    CHECK_FALSE(ri.is_ok);
    CHECK_EQUAL(status_std_invalid_arg, ri.error);

    CHECK_TRUE(cvec_destroy(vec).is_ok);
}

TEST(tg_cvectors, appendGetOkOnValidVec)
{
    result_size_t rsz;
    result_void_pt rvp;
    result_int_t ri;

    result_cvec_pt rcv = cvec_create(sizeof(uint8_t));
    cvec_t *vec = rcv.value;
    uint8_t value = 255;

    ri = cvec_append(vec, &value);
    CHECK_TRUE(ri.is_ok);
    
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

    result_cvec_pt rcv = cvec_create(sizeof(uint8_t));
    cvec_t *vec = rcv.value;

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

TEST(tg_cvectors, popFailsOnNullVector)
{
    uint8_t out_val = 0;
    result_int_t ri = cvec_pop(NULL, &out_val);
    CHECK_FALSE(ri.is_ok);
    CHECK_EQUAL(status_std_null_ptr, ri.error);
}

TEST(tg_cvectors, popFailsOnNullOut)
{
    cvec_t *vec = cvec_create(sizeof(uint8_t)).value;
    result_int_t ri = cvec_pop(vec, NULL);
    CHECK_FALSE(ri.is_ok);
    CHECK_EQUAL(status_std_invalid_arg, ri.error);
}

TEST(tg_cvectors, popFailsOnEmptyVector)
{
    cvec_t *vec = cvec_create(sizeof(uint8_t)).value;
    uint8_t out_val = 0;

    result_int_t ri = cvec_pop(vec, &out_val);
    CHECK_FALSE(ri.is_ok);

}


TEST_GROUP(tg_cvec_populated)
{
    const size_t prealloced_elements = 16;
    result_cvec_pt rcv;
    cvec_t *vec_ptr; 
    void setup()
    {
        UT_PTR_SET(calloc_fn, calloc_impl);
        UT_PTR_SET(malloc_fn, malloc_impl);
        UT_PTR_SET(free_fn, free_impl);

        rcv = cvec_create(sizeof(uint8_t));
        CHECK_TRUE(rcv.is_ok);
        vec_ptr = rcv.value;

        for(uint8_t i = 0; i < prealloced_elements; i++){
            cvec_append(vec_ptr, &i);
        }

        calloc_count = 0;
        malloc_count = 0;
        free_count = 0;
        fail_after = -1;
        fail_after_count = 0;
    }
    void teardown()
    {
        CHECK_TRUE_TEXT(free_count == (calloc_count + malloc_count), "Number of allocated call != free'd calls.");
        CHECK_TRUE(cvec_destroy(vec_ptr).is_ok);
    }
};

TEST(tg_cvec_populated, appendHandlesFailedAlloc)
{
    //result_size_t vec_size = cvec_size(vec_ptr);
    //result_size_t vec_size = cvec_size(vec_ptr);
    //size_t vec_size = cvec_size(vec_ptr).value;
    size_t vec_cap = cvec_capacity(vec_ptr).value;
    uint8_t u8val = 128;
    fail_after = 0;

    //Append until it will attempts to allocate memory.
    while(cvec_size(vec_ptr).value < vec_cap - 1){
        CHECK_TRUE(cvec_append(vec_ptr, &u8val).is_ok);
        CHECK_TRUE(*(uint8_t *)cvec_get(vec_ptr, cvec_size(vec_ptr).value).value == u8val);
    }
    
    result_int_t ri = cvec_append(vec_ptr, &u8val);
    CHECK_FALSE(ri.is_ok);
    CHECK_EQUAL(status_std_alloc_failure, ri.error);
}


TEST(tg_cvec_populated, popReducesVectorSize)
{
    uint8_t out_val = 0;
    size_t old_size = cvec_size(vec_ptr).value;

    //First confirm the value of the last element.

    CHECK_TRUE(cvec_pop(vec_ptr, &out_val).is_ok);
    CHECK_EQUAL_TEXT(old_size - 1, cvec_size(vec_ptr).value, "The vector size was not correctly reduced.");
}

TEST(tg_cvec_populated, popReturnsCorrectValues)
{
    uint8_t out_val = 0;

    CHECK_TRUE(cvec_pop(vec_ptr, &out_val).is_ok);
    CHECK_EQUAL(prealloced_elements - 1, out_val);
}

TEST(tg_cvec_populated, cloneFailsOnNullVector)
{
    result_cvec_pt rcv = cvec_clone(NULL);
    CHECK_FALSE(rcv.is_ok);
}

TEST(tg_cvec_populated, cloneHandlesFailedVecAlloc)
{
    fail_after = 0;
    result_cvec_pt rcv = cvec_clone(vec_ptr);
    CHECK_FALSE(rcv.is_ok);
    CHECK_EQUAL(status_std_alloc_failure, rcv.error);

    if(rcv.is_ok){
        cvec_destroy(rcv.value);
    }
}

TEST(tg_cvec_populated, cloneHandlesFailedDataAlloc)
{
    //The second allocation takes place for the data of the cloned vec.
    fail_after = 1;
    result_cvec_pt rcv = cvec_clone(vec_ptr);
    CHECK_FALSE(rcv.is_ok);
    CHECK_EQUAL(status_std_alloc_failure, rcv.error);

    if(rcv.is_ok){
        cvec_destroy(rcv.value);
    }
}

TEST(tg_cvec_populated, cloneHasCorrectShape)
{
    result_cvec_pt rcv = cvec_clone(vec_ptr);
    CHECK_TRUE(rcv.is_ok);
    CHECK_EQUAL(cvec_size(vec_ptr).value, cvec_size(rcv.value).value);
    CHECK_EQUAL(cvec_capacity(vec_ptr).value, cvec_capacity(rcv.value).value);

    if(rcv.is_ok){
        cvec_destroy(rcv.value);
    }
}

TEST(tg_cvec_populated, cloneHasCorrectData)
{
    result_cvec_pt rcv = cvec_clone(vec_ptr);
    CHECK_TRUE(rcv.is_ok);

    for(size_t i = 0; i < cvec_size(vec_ptr).value; i++){
        //Equivalent: CHECK_EQUAL(vec_ptr[i] == rcv[i])
        CHECK_EQUAL(*(uint8_t *)(cvec_get(vec_ptr, i).value), *(uint8_t *)(cvec_get(rcv.value, i).value));
    }

    cvec_destroy(rcv.value);
}

TEST(tg_cvec_populated, sliceFailsOnNullVec)
{
    result_cvec_pt rcv = cvec_slice(NULL, 0, 8);
    CHECK_FALSE(rcv.is_ok);
    CHECK_EQUAL(status_std_null_ptr, rcv.error);
}

TEST(tg_cvec_populated, sliceFailsOnInvalidStart)
{
    result_cvec_pt rcv = cvec_slice(vec_ptr, prealloced_elements + 1, prealloced_elements - 1);
    CHECK_FALSE(rcv.is_ok);
    CHECK_EQUAL(status_std_invalid_arg, rcv.error);
}

TEST(tg_cvec_populated, sliceFailsOnInvalidEnd)
{
    result_cvec_pt rcv = cvec_slice(vec_ptr, 0, prealloced_elements + 1);
    CHECK_FALSE(rcv.is_ok);
    CHECK_EQUAL(status_std_invalid_arg, rcv.error);
}

TEST(tg_cvec_populated, sliceFailsOnNegativeRange)
{
    //We give it slice values where the end is less than the start, but both
    //are valid indecies themselves.
    result_cvec_pt rcv = cvec_slice(vec_ptr, prealloced_elements - 1, prealloced_elements - 2);
    CHECK_FALSE(rcv.is_ok);
    CHECK_EQUAL(status_std_invalid_arg, rcv.error);
}

TEST(tg_cvec_populated, sliceHandlesAllocVecFailure)
{
    fail_after = 0;

    //Try to get copy from zeroth element to near last.
    result_cvec_pt rcv = cvec_slice(vec_ptr, 0, prealloced_elements - 1);

    CHECK_FALSE(rcv.is_ok);
    CHECK_EQUAL(status_std_alloc_failure, rcv.error);
    
    if(rcv.is_ok){
        cvec_destroy(rcv.value);
    }
}

TEST(tg_cvec_populated, sliceHandlesAllocDataFailure)
{
    //Allow the cvec to be allocated/created then fail on data alloc.
    fail_after = 1;

    //Try to get copy from zeroth element to near last.
    result_cvec_pt rcv = cvec_slice(vec_ptr, 0, prealloced_elements - 1);

    CHECK_FALSE(rcv.is_ok);
    CHECK_EQUAL(status_std_alloc_failure, rcv.error);

}

TEST(tg_cvec_populated, slcieHasCorrectShape)
{
    const size_t slice_start = 2;
    const size_t slice_end = prealloced_elements - 1;
    const size_t slice_size = (slice_end - slice_start) + 1;

    result_cvec_pt rcv = cvec_slice(vec_ptr, slice_start, slice_end);
    CHECK_TRUE(rcv.is_ok);

    result_size_t rsize = cvec_size(rcv.value);
    CHECK_TRUE(rsize.is_ok);
    CHECK_EQUAL_TEXT(slice_size, rsize.value, "The slices size is incorrect.");

    result_size_t rcap = cvec_capacity(rcv.value);
    CHECK_TRUE(rcap.is_ok);
    CHECK_EQUAL_TEXT(slice_size, rcap.value, "The slices capacity is incorrect.");

    cvec_destroy(rcv.value);
}

TEST(tg_cvec_populated, sliceHoldsCorrectData)
{
    const size_t slice_start = 2;
    const size_t slice_end = prealloced_elements - 1; //16-1 = 15
    const size_t slice_size = (slice_end - slice_start); //(15 - 2) = 13

    result_cvec_pt rcv = cvec_slice(vec_ptr, slice_start, slice_end);
    CHECK_TRUE(rcv.is_ok);

    //We check the elements against eachother taking into account the offset.
    result_void_pt rvp;
    for(size_t i = 0; i < slice_size; i++){
        rvp = cvec_get(vec_ptr, i + slice_start);
        CHECK_TRUE(rvp.is_ok);
        uint8_t expected = *(uint8_t *)rvp.value;

        rvp = cvec_get(rcv.value, i);
        CHECK_TRUE(rvp.is_ok);
        uint8_t val = *(uint8_t *)rvp.value;

        //uint8_t expected = *(uint8_t *)cvec_get(vec_ptr, i + slice_start - 1).value;
        //uint8_t val = *(uint8_t *)cvec_get(rcv.value, i).value;
        //CHECK_EQUAL(i+2, val);

        CHECK_EQUAL_TEXT(expected, val, "Elements from original and slice vectors don't match.");
    }

    cvec_destroy(rcv.value);
}








