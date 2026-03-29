# File: tests/result_returns/CMakeLists.txt

add_subdirectory(mocks)
add_subdirectory(fakes)
add_subdirectory(stubs)

# TEST_RUNNER
add_library(test_result_returns
    test_result_returns.cpp    
)

target_link_libraries(test_result_returns
    ${CPPUTEST_LIBRARIES}
    result_returns
)

target_include_directories(test_result_returns PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    #Next comes the shared and non-module specific test depencencies.
    ${CMAKE_SOURCE_DIR}/tests/shared/mocks/
    ${CMAKE_SOURCE_DIR}/tests/shared/fakes/
    ${CMAKE_SOURCE_DIR}/tests/shared/stubs/
)
