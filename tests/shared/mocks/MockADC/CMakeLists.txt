add_library(MockADC STATIC
    MockADC.c
)

target_include_directories(MockADC PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(MockADC
    ${CPPUTEST_LIBRARIES}
)
