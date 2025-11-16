# Settings Manager

set(SETTINGS_SOURCES
    SettingsManager.cpp
    DisplaySettings.cpp
    ThemeSettings.cpp
)

add_executable(malgoro-settings
    ${SETTINGS_SOURCES}
    main.cpp
)

target_link_libraries(malgoro-settings
    ${GTK3_LIBRARIES}
    ${GLIB_LIBRARIES}
    ${XRANDR_LIBRARIES}
)

install(TARGETS malgoro-settings RUNTIME DESTINATION bin)
