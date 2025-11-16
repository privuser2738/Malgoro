# Panel

set(PANEL_SOURCES
    Panel.cpp
    Applet.cpp
    WindowList.cpp
    SystemTray.cpp
    Clock.cpp
    VolumeControl.cpp
    NetworkMonitor.cpp
)

add_executable(malgoro-panel
    ${PANEL_SOURCES}
    main.cpp
)

target_link_libraries(malgoro-panel
    ${GTK3_LIBRARIES}
    ${WNCK_LIBRARIES}
    ${DBUS_LIBRARIES}
    ${DBUS_GLIB_LIBRARIES}
    ${PULSE_LIBRARIES}
    ${GLIB_LIBRARIES}
)

install(TARGETS malgoro-panel RUNTIME DESTINATION bin)
