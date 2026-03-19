# File: tests/shared/mocks/module_name/CMakeLists.txt

# TEST_RUNNER
add_library(module_name STATIC 
    module_name.cpp    
)

target_include_directories(module_name PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    #Next comes the shared and non-module specific test depencencies.
    #${CMAKE_SOURCE_DIR}/tests/shared/mocks/
    #${CMAKE_SOURCE_DIR}/tests/shared/fakes/
    #${CMAKE_SOURCE_DIR}/tests/shared/stubs/
)

target_link_libraries(module_name
    ${CPPUTEST_LIBRARIES}
)
