# File: tests/module_name/CMakeLists.txt

add_subdirectory(mocks)
add_subdirectory(fakes)
add_subdirectory(stubs)

# TEST_RUNNER
add_library(test_module_name
    test_module_name.cpp    
)

target_link_libraries(test_module_name
    ${CPPUTEST_LIBRARIES}
    module_name
)

target_include_directories(test_module_name PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    #Next comes the shared and non-module specific test depencencies.
    ${CMAKE_SOURCE_DIR}/tests/shared/mocks/
    ${CMAKE_SOURCE_DIR}/tests/shared/fakes/
    ${CMAKE_SOURCE_DIR}/tests/shared/stubs/
)
