
# TEST_RUNNER
add_library(simple_test 
    simple_test.cpp    
)

target_link_libraries(simple_test
    ${CPPUTEST_LIBRARIES}/libCppUTest.a
    ${CPPUTEST_LIBRARIES}/libCppUTestExt.a
)

