# Widgets

set(WIDGETS_SOURCES
    ClassicButton.cpp
    ClassicWindow.cpp
    ClassicMenu.cpp
)

add_library(malgoro-widgets STATIC ${WIDGETS_SOURCES})

target_link_libraries(malgoro-widgets
    ${GTK3_LIBRARIES}
    ${CAIRO_LIBRARIES}
)
