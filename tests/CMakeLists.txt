project(Tests)

# TEST_DIRS
add_subdirectory(result_returns)
add_subdirectory(cvectors)
add_subdirectory(cbz)
add_subdirectory(simple_test)

add_subdirectory(shared)


# TEST_RUNNER
add_executable(AllTests
    AllTests.cpp    
)

target_link_libraries(AllTests
    ${CPPUTEST_LIBRARIES}
    # TEST_LINKS
    test_result_returns
    test_cvectors
    test_cbz
    simple_test
)
