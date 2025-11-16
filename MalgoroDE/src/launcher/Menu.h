#ifndef MALGORO_MENU_H
#define MALGORO_MENU_H

#include <gtk/gtk.h>
#include <string>
#include <vector>
#include <memory>
#include <map>

namespace MalgoroDE {

class Application;
class Category;

/**
 * @brief Application launcher menu (Start Menu)
 */
class Menu {
public:
    Menu();
    ~Menu();

    /**
     * @brief Initialize menu
     */
    bool initialize();

    /**
     * @brief Show menu at position
     */
    void show(int x, int y);

    /**
     * @brief Hide menu
     */
    void hide();

    /**
     * @brief Toggle menu visibility
     */
    void toggle();

    /**
     * @brief Refresh application list
     */
    void refresh();

    /**
     * @brief Get menu button for panel
     */
    GtkWidget* get_button();

private:
    void create_ui();
    void load_applications();
    void build_category_tree();
    void populate_menu();
    void create_favorites_section();
    void create_categories_section();
    void create_footer();

    // Search
    void filter_applications(const std::string& query);
    void show_search_results();

    // Event handlers
    static void on_button_clicked(GtkWidget* button, gpointer data);
    static void on_search_changed(GtkEditable* editable, gpointer data);
    static void on_app_activated(GtkWidget* widget, gpointer data);
    static void on_category_clicked(GtkWidget* widget, gpointer data);
    static void on_all_apps_clicked(GtkWidget* widget, gpointer data);
    static gboolean on_window_focus_out(GtkWidget* widget, GdkEvent* event, gpointer data);

    // Application launch
    void launch_application(std::shared_ptr<Application> app);

    // Favorites
    void add_to_favorites(std::shared_ptr<Application> app);
    void remove_from_favorites(std::shared_ptr<Application> app);
    bool is_favorite(std::shared_ptr<Application> app);
    void load_favorites();
    void save_favorites();

    // Recent apps
    void add_to_recent(std::shared_ptr<Application> app);
    std::vector<std::shared_ptr<Application>> get_recent_apps();

    // UI Widgets
    GtkWidget* menu_button_;          // Button for panel
    GtkWidget* menu_window_;          // Menu popup window
    GtkWidget* search_entry_;         // Search box
    GtkWidget* content_box_;          // Main content area
    GtkWidget* favorites_box_;        // Favorites section
    GtkWidget* categories_box_;       // Categories section
    GtkWidget* apps_box_;             // Application list
    GtkWidget* footer_box_;           // Footer buttons

    // Data
    std::vector<std::shared_ptr<Application>> applications_;
    std::vector<std::shared_ptr<Application>> favorites_;
    std::vector<std::shared_ptr<Application>> recent_;
    std::map<std::string, std::shared_ptr<Category>> categories_;

    // State
    bool visible_;
    std::string current_category_;
    std::string search_query_;

    // Configuration
    int width_;
    int height_;
    int icon_size_;
    bool show_descriptions_;
};

/**
 * @brief Represents a desktop application
 */
class Application {
public:
    Application(const std::string& desktop_file);
    ~Application();

    std::string get_name() const { return name_; }
    std::string get_description() const { return description_; }
    std::string get_exec() const { return exec_; }
    std::string get_icon() const { return icon_; }
    std::string get_category() const { return category_; }
    std::string get_desktop_file() const { return desktop_file_; }

    bool is_valid() const { return valid_; }
    bool should_show() const { return !no_display_ && !hidden_; }

    void launch();

private:
    void parse_desktop_file();

    std::string desktop_file_;
    std::string name_;
    std::string description_;
    std::string exec_;
    std::string icon_;
    std::string category_;
    std::string path_;
    bool terminal_;
    bool no_display_;
    bool hidden_;
    bool valid_;
};

/**
 * @brief Application category
 */
class Category {
public:
    Category(const std::string& name, const std::string& icon = "");

    std::string get_name() const { return name_; }
    std::string get_icon() const { return icon_; }

    void add_application(std::shared_ptr<Application> app);
    std::vector<std::shared_ptr<Application>> get_applications() const { return applications_; }
    int get_count() const { return applications_.size(); }

private:
    std::string name_;
    std::string icon_;
    std::vector<std::shared_ptr<Application>> applications_;
};

} // namespace MalgoroDE

#endif // MALGORO_MENU_H
