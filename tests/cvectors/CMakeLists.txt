# File: tests/cvectors/CMakeLists.txt

add_subdirectory(mocks)
add_subdirectory(fakes)
add_subdirectory(stubs)

# TEST_RUNNER
add_library(test_cvectors
    test_cvectors.cpp    
)

target_link_libraries(test_cvectors
    ${CPPUTEST_LIBRARIES}
    cvectors
)

target_include_directories(test_cvectors PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    #Next comes the shared and non-module specific test depencencies.
    ${CMAKE_SOURCE_DIR}/tests/shared/mocks/
    ${CMAKE_SOURCE_DIR}/tests/shared/fakes/
    ${CMAKE_SOURCE_DIR}/tests/shared/stubs/
)
