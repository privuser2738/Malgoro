# Utilities

set(UTILS_SOURCES
    Config.cpp
    Logger.cpp
    DBusHelper.cpp
)

add_library(malgoro-utils STATIC ${UTILS_SOURCES})

target_link_libraries(malgoro-utils
    ${GLIB_LIBRARIES}
    ${DBUS_LIBRARIES}
)
