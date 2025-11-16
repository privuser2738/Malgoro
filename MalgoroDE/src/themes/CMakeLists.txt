# Theme Manager

set(THEMES_SOURCES
    ThemeManager.cpp
)

add_library(malgoro-themes STATIC ${THEMES_SOURCES})

target_link_libraries(malgoro-themes
    ${GTK3_LIBRARIES}
    ${GLIB_LIBRARIES}
)
