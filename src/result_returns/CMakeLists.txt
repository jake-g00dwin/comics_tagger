# File: src/result_returns/CMakeLists.txt
add_library(result_returns STATIC
    result_returns.c
)

# Current list dir: The directory where the cmake config file is.
# Source Dir: The dir where the root/main cmake config file is.

if(NOT UNIT_TESTING)
    target_include_directories(result_returns PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_SOURCE_DIR}/inc/
    )
    target_link_libraries(result_returns
        #Put linked libs here.
    )

else()
    target_include_directories(result_returns PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        #First we include any module specific test dependencies.
        ${CMAKE_SOURCE_DIR}/tests/result_returns/mocks/
        ${CMAKE_SOURCE_DIR}/tests/result_returns/fakes/
        ${CMAKE_SOURCE_DIR}/tests/result_returns/stubs/
        #Next comes the shared and non-module specific test depencencies.
        ${CMAKE_SOURCE_DIR}/tests/shared/mocks/
        ${CMAKE_SOURCE_DIR}/tests/shared/fakes/
        ${CMAKE_SOURCE_DIR}/tests/shared/stubs/
        #Finally we include the local stuff, which has likely been overridden.
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
    #Place Mocked/Regular dependencies here for unit testing.
    target_link_libraries(result_returns
        #Put linked libs here.
    )
endif()
