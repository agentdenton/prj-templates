set(SOURCES
    main.cpp
)

add_executable(app ${SOURCES})
target_link_libraries(app PRIVATE spdlog)
target_link_libraries(app PRIVATE fmt)
target_link_libraries(app PRIVATE magic_enum)
