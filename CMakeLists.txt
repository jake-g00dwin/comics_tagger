cmake_minimum_required(VERSION 3.20)

# Use the fancy version substitution
project(comic_tagger
    VERSION 0.1.0
    DESCRIPTION "Comic Tagging program"
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

# For being able to use LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Request C  standard features
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic")

# SETUP THE CXX flags for .cpp
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wpedantic")



# #######################################
# TESTING STUFF 
# #######################################


if (UNIT_TESTING)
    #Allows usage of preprossor stuff in your files.
    add_compile_definitions(UNIT_TESTING=1)
    if(DEFINED ENV{CPPUTEST_HOME})
        message(STATUS "Using CppUTest home: $ENV{CPPUTEST_HOME}")
        set(CPPUTEST_INCLUDE_DIRS $ENV{CPPUTEST_HOME}/include)
        set(CPPUTEST_LIBRARY_DIRS $ENV{CPPUTEST_HOME}/lib)
        set(CPPUTEST_LIBRARIES CppUTest CppUTestExt) 
    else()
        find_package(PkgConfig REQUIRED)
        pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
        message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
    endif()
     
    # Diagnostic Messages for Multi-Platform testing.
    message(STATUS "CPPUTEST_LIBRARY_DIRS: ${CPPUTEST_LIBRARY_DIRS}")
    message(STATUS "CPPUTEST_INCLUDE_DIRS: ${CPPUTEST_INCLUDE_DIRS}" )
    message(STATUS "CPPUTEST_LIBRARIES: ${CPPUTEST_LIBRARIES}" )

    include_directories(${CPPUTEST_INCLUDE_DIRS})
    link_directories(${CPPUTEST_LIBRARY_DIRS})
    
    add_subdirectory(tests)
endif()

# #######################################
# PROJECT SPECIFIC 
# #######################################


include_directories(
    ./inc
)

add_subdirectory(src)
