#ifndef MALGORO_WINDOW_H
#define MALGORO_WINDOW_H

#include <string>
#include <X11/Xlib.h>
#include <memory>

namespace MalgoroDE {

/**
 * @brief Represents a managed window
 */
class Window {
public:
    Window(::Window xwindow, Display* display);
    ~Window();

    // Window properties
    ::Window get_xwindow() const { return xwindow_; }
    ::Window get_frame() const { return frame_; }
    std::string get_title() const { return title_; }
    std::string get_class() const { return class_name_; }
    std::string get_instance() const { return instance_; }

    // Geometry
    int get_x() const { return x_; }
    int get_y() const { return y_; }
    int get_width() const { return width_; }
    int get_height() const { return height_; }
    void set_geometry(int x, int y, int width, int height);
    void get_frame_geometry(int& x, int& y, int& width, int& height) const;

    // State
    bool is_mapped() const { return mapped_; }
    bool is_minimized() const { return minimized_; }
    bool is_maximized() const { return maximized_; }
    bool is_fullscreen() const { return fullscreen_; }
    bool is_shaded() const { return shaded_; }
    bool is_sticky() const { return sticky_; }
    bool is_above() const { return above_; }
    bool is_below() const { return below_; }
    bool is_modal() const { return modal_; }
    bool is_skip_taskbar() const { return skip_taskbar_; }
    bool is_skip_pager() const { return skip_pager_; }

    void set_mapped(bool mapped);
    void set_minimized(bool minimized);
    void set_maximized(bool maximized);
    void set_fullscreen(bool fullscreen);
    void set_shaded(bool shaded);
    void set_sticky(bool sticky);
    void set_above(bool above);
    void set_below(bool below);

    // Focus
    bool is_focused() const { return focused_; }
    void set_focused(bool focused);
    void take_focus();

    // Window type
    enum class Type {
        NORMAL,
        DESKTOP,
        DOCK,
        TOOLBAR,
        MENU,
        UTILITY,
        SPLASH,
        DIALOG
    };
    Type get_type() const { return type_; }
    void set_type(Type type) { type_ = type; }

    // Workspace
    int get_workspace() const { return workspace_; }
    void set_workspace(int workspace) { workspace_ = workspace; }

    // Frame management
    void create_frame();
    void destroy_frame();
    void update_frame();
    void redraw_frame();

    // Window operations
    void map();
    void unmap();
    void raise();
    void lower();
    void close();
    void kill();

    // Properties
    void update_title();
    void update_class();
    void update_hints();
    void update_size_hints();
    void update_protocols();
    void update_state();
    void update_type();

    // Protocols
    bool supports_delete_window() const { return supports_delete_; }
    bool supports_take_focus() const { return supports_focus_; }

    // Size constraints
    int get_min_width() const { return min_width_; }
    int get_min_height() const { return min_height_; }
    int get_max_width() const { return max_width_; }
    int get_max_height() const { return max_height_; }
    int get_base_width() const { return base_width_; }
    int get_base_height() const { return base_height_; }
    int get_width_inc() const { return width_inc_; }
    int get_height_inc() const { return height_inc_; }

    // Frame extents
    int get_border_width() const { return border_width_; }
    int get_titlebar_height() const { return titlebar_height_; }

private:
    void apply_size_hints(int& width, int& height);
    void send_configure_notify();

    Display* display_;
    ::Window xwindow_;      // Client window
    ::Window frame_;        // Frame window (decoration)

    // Geometry
    int x_, y_;
    int width_, height_;
    int old_x_, old_y_;     // Pre-maximize geometry
    int old_width_, old_height_;

    // State flags
    bool mapped_;
    bool minimized_;
    bool maximized_;
    bool fullscreen_;
    bool shaded_;
    bool sticky_;
    bool above_;
    bool below_;
    bool modal_;
    bool focused_;
    bool skip_taskbar_;
    bool skip_pager_;

    // Properties
    std::string title_;
    std::string class_name_;
    std::string instance_;
    Type type_;
    int workspace_;

    // Protocols
    bool supports_delete_;
    bool supports_focus_;

    // Size hints
    int min_width_, min_height_;
    int max_width_, max_height_;
    int base_width_, base_height_;
    int width_inc_, height_inc_;
    float min_aspect_, max_aspect_;

    // Frame decoration
    int border_width_;
    int titlebar_height_;
};

} // namespace MalgoroDE

#endif // MALGORO_WINDOW_H
