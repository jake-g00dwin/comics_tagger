cmake_minimum_required(VERSION 3.20)

# Use the fancy version substitution
project(main
    VERSION 1.0
    DESCRIPTION "template for cmake + cpputest"
    LANGUAGES   C CXX
)
enable_testing()

set(TARGET_GROUP production CACHE STRING "Group to build")

if(MSVC OR MSYS OR MINGW)
    message("### SETUP FOR WINDOWS ###")
    add_definitions(-DWINDOWS)
else()
    message("### SETUP FOR UNIX ###")
    add_definitions(-DUNIX)
endif()

# For being able to used LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Request C 17 standard features
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic")

# SETUP THE CXX flags for .cpp
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wpedantic")



# #######################################
# Libraries to include 
# #######################################

# Request the required wxWidgets libs
find_package(wxWidgets COMPONENTS core base REQUIRED)

#find_package(wxWidgets 3.3 COMPONENTS core base REQUIRED CONFIG)
include(${wxWidgets_USE_FILE})



# #######################################
# TESTING STUFF 
# #######################################


if (UNIT_TESTING)

    if(DEFINED ENV{CPPUTEST_HOME})
        message(STATUS "Using CppUTest home: $ENV{CPPUTEST_HOME}")
        set(CPPUTEST_INCLUDE_DIRS $ENV{CPPUTEST_HOME}/include)
        set(CPPUTEST_LIBRARIES $ENV{CPPUTEST_HOME}/lib)
        set(CPPUTEST_LDFLAGS CppUTest CppUTestExt)
    else()
        find_package(PkgConfig REQUIRED)
        pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
        message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
    endif()
    
    include_directories(
        ${CPPUTEST_INCLUDE_DIRS}
        /usr/include/c++/11/
        ./inc
        ./mocks
        )
    link_directories(${CPPUTEST_LIBRARIES})
    
    add_subdirectory(mocks)
    add_subdirectory(tests)

endif()

# #######################################
# PROJECT SPECIFIC 
# #######################################


include_directories(
    ./inc
)

add_subdirectory(src)
