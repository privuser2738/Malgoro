#ifndef MALGORO_WINDOW_MANAGER_H
#define MALGORO_WINDOW_MANAGER_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace MalgoroDE {

// Forward declarations
class Window;
class Workspace;
class Decorator;
class KeyBindings;

/**
 * @brief Main window manager class
 *
 * Manages windows, workspaces, and window decorations on X11
 */
class WindowManager {
public:
    WindowManager();
    ~WindowManager();

    /**
     * @brief Initialize the window manager
     * @return true if successful, false otherwise
     */
    bool initialize();

    /**
     * @brief Run the main event loop
     * @return Exit code
     */
    int run();

    /**
     * @brief Gracefully shutdown the window manager
     */
    void shutdown();

    // Window management
    bool manage_window(::Window xwindow);
    bool unmanage_window(::Window xwindow);
    std::shared_ptr<Window> find_window(::Window xwindow);
    std::vector<std::shared_ptr<Window>> get_all_windows();

    // Focus management
    void focus_window(std::shared_ptr<Window> window);
    std::shared_ptr<Window> get_focused_window();
    void cycle_focus(bool reverse = false);

    // Workspace management
    void switch_workspace(int workspace_index);
    int get_current_workspace();
    int get_workspace_count();
    void move_window_to_workspace(std::shared_ptr<Window> window, int workspace);

    // Window operations
    void close_window(std::shared_ptr<Window> window);
    void minimize_window(std::shared_ptr<Window> window);
    void maximize_window(std::shared_ptr<Window> window);
    void unmaximize_window(std::shared_ptr<Window> window);
    void toggle_maximize(std::shared_ptr<Window> window);
    void shade_window(std::shared_ptr<Window> window);
    void fullscreen_window(std::shared_ptr<Window> window);

    // Desktop operations
    void show_desktop();
    void tile_windows_horizontally();
    void tile_windows_vertically();
    void cascade_windows();

    // Configuration
    void load_config();
    void save_config();
    void reload_config();

    // X11 access
    Display* get_display() { return display_; }
    ::Window get_root_window() { return root_; }

    // Theme
    void set_theme(const std::string& theme_name);
    std::string get_theme() const { return current_theme_; }

private:
    // X11 event handling
    void handle_event(XEvent& event);
    void handle_map_request(XMapRequestEvent& event);
    void handle_unmap_notify(XUnmapEvent& event);
    void handle_destroy_notify(XDestroyWindowEvent& event);
    void handle_configure_request(XConfigureRequestEvent& event);
    void handle_configure_notify(XConfigureEvent& event);
    void handle_property_notify(XPropertyEvent& event);
    void handle_client_message(XClientMessageEvent& event);
    void handle_button_press(XButtonEvent& event);
    void handle_button_release(XButtonEvent& event);
    void handle_motion_notify(XMotionEvent& event);
    void handle_key_press(XKeyEvent& event);
    void handle_key_release(XKeyEvent& event);
    void handle_enter_notify(XCrossingEvent& event);
    void handle_leave_notify(XCrossingEvent& event);
    void handle_focus_in(XFocusChangeEvent& event);
    void handle_focus_out(XFocusChangeEvent& event);

    // Window state management
    void update_window_list();
    void update_client_list();
    void update_active_window();
    void update_desktop_names();

    // EWMH (Extended Window Manager Hints) support
    void setup_ewmh();
    void handle_ewmh_message(XClientMessageEvent& event);
    void set_ewmh_property(const char* name, unsigned long* data, int count);

    // ICCCM (Inter-Client Communication Conventions Manual) support
    void setup_icccm();

    // X11 error handling
    static int on_x_error(Display* display, XErrorEvent* event);
    static int on_wm_detected(Display* display, XErrorEvent* event);

    // Initialization helpers
    bool connect_to_x11();
    bool become_window_manager();
    void grab_keys();
    void grab_buttons();
    void scan_existing_windows();

    // Data members
    Display* display_;
    ::Window root_;
    int screen_;

    std::map<::Window, std::shared_ptr<Window>> windows_;
    std::vector<std::shared_ptr<Workspace>> workspaces_;
    int current_workspace_;

    std::shared_ptr<Window> focused_window_;
    std::unique_ptr<Decorator> decorator_;
    std::unique_ptr<KeyBindings> key_bindings_;

    // Configuration
    std::string config_file_;
    std::string current_theme_;
    bool enable_compositor_;
    bool enable_animations_;
    int num_workspaces_;

    // Focus mode
    enum class FocusMode {
        CLICK_TO_FOCUS,
        FOCUS_FOLLOWS_MOUSE,
        SLOPPY_FOCUS
    };
    FocusMode focus_mode_;

    // Window placement
    enum class PlacementMode {
        SMART,
        CASCADE,
        CENTER,
        RANDOM
    };
    PlacementMode placement_mode_;

    // State
    bool running_;
    bool show_desktop_mode_;

    // Atoms (X11 properties)
    struct Atoms {
        Atom wm_protocols;
        Atom wm_delete_window;
        Atom wm_state;
        Atom wm_change_state;
        Atom wm_take_focus;

        // EWMH atoms
        Atom net_supported;
        Atom net_client_list;
        Atom net_client_list_stacking;
        Atom net_number_of_desktops;
        Atom net_desktop_geometry;
        Atom net_desktop_viewport;
        Atom net_current_desktop;
        Atom net_desktop_names;
        Atom net_active_window;
        Atom net_workarea;
        Atom net_supporting_wm_check;
        Atom net_wm_name;
        Atom net_wm_state;
        Atom net_wm_state_modal;
        Atom net_wm_state_sticky;
        Atom net_wm_state_maximized_vert;
        Atom net_wm_state_maximized_horz;
        Atom net_wm_state_shaded;
        Atom net_wm_state_skip_taskbar;
        Atom net_wm_state_skip_pager;
        Atom net_wm_state_hidden;
        Atom net_wm_state_fullscreen;
        Atom net_wm_state_above;
        Atom net_wm_state_below;
        Atom net_wm_window_type;
        Atom net_wm_window_type_desktop;
        Atom net_wm_window_type_dock;
        Atom net_wm_window_type_toolbar;
        Atom net_wm_window_type_menu;
        Atom net_wm_window_type_utility;
        Atom net_wm_window_type_splash;
        Atom net_wm_window_type_dialog;
        Atom net_wm_window_type_normal;
        Atom net_close_window;
        Atom net_moveresize_window;
        Atom net_wm_moveresize;
    };
    Atoms atoms_;

    void init_atoms();
};

} // namespace MalgoroDE

#endif // MALGORO_WINDOW_MANAGER_H
