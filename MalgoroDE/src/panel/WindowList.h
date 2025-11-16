#ifndef MALGORO_WINDOW_LIST_H
#define MALGORO_WINDOW_LIST_H

#include "Applet.h"
#include <libwnck/libwnck.h>
#include <vector>
#include <map>

namespace MalgoroDE {

/**
 * @brief Window list/taskbar applet
 */
class WindowList : public Applet {
public:
    WindowList();
    ~WindowList() override;

    bool initialize() override;
    GtkWidget* get_widget() override;
    void update() override;
    bool should_expand() const override { return true; }

    // Configuration
    void set_group_windows(bool group) { group_windows_ = group; }
    void set_show_all_workspaces(bool show_all) { show_all_workspaces_ = show_all; }
    void set_button_width(int width) { button_width_ = width; }

private:
    void create_ui();
    void refresh_window_list();
    void add_window_button(WnckWindow* window);
    void remove_window_button(WnckWindow* window);
    void update_window_button(WnckWindow* window);

    // Event handlers
    static void on_window_opened(WnckScreen* screen, WnckWindow* window, gpointer data);
    static void on_window_closed(WnckScreen* screen, WnckWindow* window, gpointer data);
    static void on_active_window_changed(WnckScreen* screen, WnckWindow* prev, gpointer data);
    static void on_window_state_changed(WnckWindow* window, WnckWindowState changed, WnckWindowState new_state, gpointer data);
    static void on_window_name_changed(WnckWindow* window, gpointer data);
    static void on_button_clicked(GtkWidget* button, gpointer data);
    static gboolean on_button_press(GtkWidget* button, GdkEventButton* event, gpointer data);

    // UI
    GtkWidget* scrolled_window_;
    GtkWidget* button_box_;

    // libwnck
    WnckScreen* screen_;

    // Window buttons
    std::map<WnckWindow*, GtkWidget*> window_buttons_;

    // Configuration
    bool group_windows_;
    bool show_all_workspaces_;
    int button_width_;
    int icon_size_;
};

} // namespace MalgoroDE

#endif // MALGORO_WINDOW_LIST_H
