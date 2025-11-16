cmake_minimum_required(VERSION 3.20)
project(MalgoroDE VERSION 0.1.0 LANGUAGES CXX C)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set C standard for X11 bindings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# Find required packages
find_package(PkgConfig REQUIRED)

# GTK3 for UI
pkg_check_modules(GTK3 REQUIRED gtk+-3.0>=3.24)

# X11 libraries
pkg_check_modules(X11 REQUIRED x11)
pkg_check_modules(XCOMPOSITE REQUIRED xcomposite)
pkg_check_modules(XDAMAGE REQUIRED xdamage)
pkg_check_modules(XRENDER REQUIRED xrender)
pkg_check_modules(XRANDR REQUIRED xrandr)
pkg_check_modules(XINERAMA REQUIRED xinerama)

# libwnck for window management utilities
pkg_check_modules(WNCK REQUIRED libwnck-3.0)

# D-Bus for IPC
pkg_check_modules(DBUS REQUIRED dbus-1)
pkg_check_modules(DBUS_GLIB REQUIRED dbus-glib-1)

# GLib/GObject
pkg_check_modules(GLIB REQUIRED glib-2.0 gobject-2.0 gio-2.0)

# Cairo for drawing
pkg_check_modules(CAIRO REQUIRED cairo)

# Pango for text rendering
pkg_check_modules(PANGO REQUIRED pango pangocairo)

# PulseAudio for volume control
pkg_check_modules(PULSE REQUIRED libpulse libpulse-mainloop-glib)

# Optional: Wayland support (future)
pkg_check_modules(WAYLAND wayland-client)
if(WAYLAND_FOUND)
    add_definitions(-DHAVE_WAYLAND)
endif()

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${GTK3_INCLUDE_DIRS}
    ${X11_INCLUDE_DIRS}
    ${XCOMPOSITE_INCLUDE_DIRS}
    ${XDAMAGE_INCLUDE_DIRS}
    ${XRENDER_INCLUDE_DIRS}
    ${XRANDR_INCLUDE_DIRS}
    ${XINERAMA_INCLUDE_DIRS}
    ${WNCK_INCLUDE_DIRS}
    ${DBUS_INCLUDE_DIRS}
    ${DBUS_GLIB_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
    ${CAIRO_INCLUDE_DIRS}
    ${PANGO_INCLUDE_DIRS}
    ${PULSE_INCLUDE_DIRS}
)

# Link directories
link_directories(
    ${GTK3_LIBRARY_DIRS}
    ${X11_LIBRARY_DIRS}
    ${XCOMPOSITE_LIBRARY_DIRS}
    ${XDAMAGE_LIBRARY_DIRS}
    ${XRENDER_LIBRARY_DIRS}
    ${XRANDR_LIBRARY_DIRS}
    ${XINERAMA_LIBRARY_DIRS}
    ${WNCK_LIBRARY_DIRS}
    ${DBUS_LIBRARY_DIRS}
    ${DBUS_GLIB_LIBRARY_DIRS}
    ${GLIB_LIBRARY_DIRS}
    ${CAIRO_LIBRARY_DIRS}
    ${PANGO_LIBRARY_DIRS}
    ${PULSE_LIBRARY_DIRS}
)

# Add subdirectories
add_subdirectory(src/utils)
add_subdirectory(src/widgets)
add_subdirectory(src/wm)
add_subdirectory(src/panel)
add_subdirectory(src/launcher)
add_subdirectory(src/settings)
add_subdirectory(src/themes)

# Installation
install(DIRECTORY data/themes DESTINATION share/malgoro)
install(DIRECTORY data/icons DESTINATION share/malgoro)
install(FILES data/malgoro.desktop DESTINATION share/xsessions)

# Print configuration summary
message(STATUS "")
message(STATUS "MalgoroDE Configuration Summary:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Install Prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "")
message(STATUS "Dependencies:")
message(STATUS "  GTK3: ${GTK3_VERSION}")
message(STATUS "  libwnck: ${WNCK_VERSION}")
message(STATUS "  D-Bus: ${DBUS_VERSION}")
message(STATUS "  PulseAudio: ${PULSE_VERSION}")
if(WAYLAND_FOUND)
message(STATUS "  Wayland: ${WAYLAND_VERSION} (enabled)")
else()
message(STATUS "  Wayland: not found (disabled)")
endif()
message(STATUS "")
