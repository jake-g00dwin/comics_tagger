add_library(MockRegEdit STATIC
    MockRegEdit.c
)

target_include_directories(MockRegEdit PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_SOURCE_DIR}/src/RegEdit/
)

target_link_libraries(MockRegEdit
    ${CPPUTEST_LIBRARIES}
)
