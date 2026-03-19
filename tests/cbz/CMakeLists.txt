# File: tests/cbz/CMakeLists.txt

add_subdirectory(mocks)
add_subdirectory(fakes)
add_subdirectory(stubs)

# TEST_RUNNER
add_library(test_cbz
    test_cbz.cpp    
)

target_link_libraries(test_cbz
    ${CPPUTEST_LIBRARIES}
    cbz
)

target_include_directories(test_cbz PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    #Next comes the shared and non-module specific test depencencies.
    ${CMAKE_SOURCE_DIR}/tests/shared/mocks/
    ${CMAKE_SOURCE_DIR}/tests/shared/fakes/
    ${CMAKE_SOURCE_DIR}/tests/shared/stubs/
)
