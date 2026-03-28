# File: src/cvectors/CMakeLists.txt
add_library(cvectors STATIC
    cvectors.c
)

# Current list dir: The directory where the cmake config file is.
# Source Dir: The dir where the root/main cmake config file is.

if(NOT UNIT_TESTING)
    target_include_directories(cvectors PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_SOURCE_DIR}/inc/
    )
    target_link_libraries(cvectors
        #Put linked libs here.
    )

else()
    target_include_directories(cvectors PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        #First we include any module specific test dependencies.
        ${CMAKE_SOURCE_DIR}/tests/cvectors/mocks/
        ${CMAKE_SOURCE_DIR}/tests/cvectors/fakes/
        ${CMAKE_SOURCE_DIR}/tests/cvectors/stubs/
        #Next comes the shared and non-module specific test depencencies.
        ${CMAKE_SOURCE_DIR}/tests/shared/mocks/
        ${CMAKE_SOURCE_DIR}/tests/shared/fakes/
        ${CMAKE_SOURCE_DIR}/tests/shared/stubs/
        #Finally we include the local stuff, which has likely been overridden.
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
    #Place Mocked/Regular dependencies here for unit testing.
    target_link_libraries(cvectors
        #Put linked libs here.
    )
endif()
