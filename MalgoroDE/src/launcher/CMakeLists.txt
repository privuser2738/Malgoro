# Launcher

set(LAUNCHER_SOURCES
    Menu.cpp
    Application.cpp
    AppDatabase.cpp
)

add_executable(malgoro-menu
    ${LAUNCHER_SOURCES}
    main.cpp
)

target_link_libraries(malgoro-menu
    ${GTK3_LIBRARIES}
    ${GLIB_LIBRARIES}
)

install(TARGETS malgoro-menu RUNTIME DESTINATION bin)
