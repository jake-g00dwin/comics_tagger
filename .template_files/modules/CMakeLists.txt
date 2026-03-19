add_library(module_name STATIC
    module_name.c
)

target_include_directories(module_name PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
