add_executable(${PROJECT_NAME}
    main.cpp
)

# Link executable to the wxWidgets target
target_link_libraries(${PROJECT_NAME} PRIVATE
        ${wxWidgets_LIBRARIES}
    )


# This line was from the documentation but doesn't seem to work for me.
#target_link_libraries(${PROJECT_NAME} wxWidgets::wxWidgets)
