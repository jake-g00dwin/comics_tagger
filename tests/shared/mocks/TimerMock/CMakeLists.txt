add_library(TimerMock STATIC
    TimerMock.c
)

target_include_directories(TimerMock PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(TimerMock
    ${CPPUTEST_LIBRARIES}
)
