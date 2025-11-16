# Window Manager

set(WM_SOURCES
    WindowManager.cpp
    Window.cpp
    Workspace.cpp
    Decorator.cpp
    KeyBindings.cpp
)

add_executable(malgoro-wm
    ${WM_SOURCES}
    main.cpp
)

target_link_libraries(malgoro-wm
    ${X11_LIBRARIES}
    ${XCOMPOSITE_LIBRARIES}
    ${XDAMAGE_LIBRARIES}
    ${XRENDER_LIBRARIES}
    ${XRANDR_LIBRARIES}
    ${XINERAMA_LIBRARIES}
    ${CAIRO_LIBRARIES}
    ${PANGO_LIBRARIES}
    ${GLIB_LIBRARIES}
)

install(TARGETS malgoro-wm RUNTIME DESTINATION bin)
