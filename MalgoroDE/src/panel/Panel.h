#ifndef MALGORO_PANEL_H
#define MALGORO_PANEL_H

#include <gtk/gtk.h>
#include <string>
#include <vector>
#include <memory>

namespace MalgoroDE {

class Applet;
class WindowList;
class SystemTray;
class Clock;
class Launcher;

/**
 * @brief Main panel/taskbar
 */
class Panel {
public:
    Panel();
    ~Panel();

    /**
     * @brief Initialize and show panel
     */
    bool initialize();

    /**
     * @brief Run the panel (GTK main loop)
     */
    void run();

    /**
     * @brief Shutdown panel
     */
    void shutdown();

    // Panel properties
    enum class Position {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT
    };

    Position get_position() const { return position_; }
    void set_position(Position position);

    int get_height() const { return height_; }
    void set_height(int height);

    bool is_autohide() const { return autohide_; }
    void set_autohide(bool autohide);

    // Applet management
    void add_applet(std::shared_ptr<Applet> applet, bool expand = false);
    void remove_applet(std::shared_ptr<Applet> applet);
    std::vector<std::shared_ptr<Applet>> get_applets() const { return applets_; }

    // Configuration
    void load_config();
    void save_config();

    // GTK widgets
    GtkWidget* get_window() { return window_; }

private:
    void create_ui();
    void create_default_layout();
    void setup_struts();
    void update_geometry();

    // Event handlers
    static gboolean on_button_press(GtkWidget* widget, GdkEventButton* event, gpointer data);
    static gboolean on_enter_notify(GtkWidget* widget, GdkEventCrossing* event, gpointer data);
    static gboolean on_leave_notify(GtkWidget* widget, GdkEventCrossing* event, gpointer data);
    static gboolean on_configure(GtkWidget* widget, GdkEventConfigure* event, gpointer data);

    // Autohide
    void show_panel();
    void hide_panel();
    static gboolean autohide_timeout(gpointer data);

    // GTK widgets
    GtkWidget* window_;
    GtkWidget* container_;
    GtkWidget* left_box_;
    GtkWidget* center_box_;
    GtkWidget* right_box_;

    // Panel configuration
    Position position_;
    int height_;
    int width_;
    bool autohide_;
    int autohide_delay_;
    int screen_;

    // Applets
    std::vector<std::shared_ptr<Applet>> applets_;

    // Built-in components
    std::shared_ptr<Launcher> launcher_;
    std::shared_ptr<WindowList> window_list_;
    std::shared_ptr<SystemTray> system_tray_;
    std::shared_ptr<Clock> clock_;

    // State
    bool hidden_;
    guint autohide_timer_;
    std::string config_file_;
};

} // namespace MalgoroDE

#endif // MALGORO_PANEL_H
