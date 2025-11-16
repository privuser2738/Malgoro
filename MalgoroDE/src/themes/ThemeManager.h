#ifndef MALGORO_THEME_MANAGER_H
#define MALGORO_THEME_MANAGER_H

#include <string>
#include <map>
#include <memory>
#include <gtk/gtk.h>

namespace MalgoroDE {

/**
 * @brief Manages desktop themes
 */
class ThemeManager {
public:
    static ThemeManager& instance();

    /**
     * @brief Initialize theme system
     */
    bool initialize();

    /**
     * @brief Set current theme
     */
    bool set_theme(const std::string& theme_name);

    /**
     * @brief Get current theme name
     */
    std::string get_current_theme() const { return current_theme_; }

    /**
     * @brief List available themes
     */
    std::vector<std::string> list_themes();

    /**
     * @brief Set GTK theme
     */
    void set_gtk_theme(const std::string& theme_name);

    /**
     * @brief Set icon theme
     */
    void set_icon_theme(const std::string& theme_name);

    /**
     * @brief Set cursor theme
     */
    void set_cursor_theme(const std::string& theme_name);

    /**
     * @brief Set font
     */
    void set_font(const std::string& font_name);

    /**
     * @brief Get color from current theme
     */
    bool get_color(const std::string& color_name, double& r, double& g, double& b);

    /**
     * @brief Apply theme to all components
     */
    void apply_theme();

    /**
     * @brief Load theme configuration
     */
    bool load_theme_config(const std::string& theme_name);

    /**
     * @brief Save current theme configuration
     */
    bool save_theme_config();

private:
    ThemeManager();
    ~ThemeManager();
    ThemeManager(const ThemeManager&) = delete;
    ThemeManager& operator=(const ThemeManager&) = delete;

    void scan_theme_directories();
    void load_gtk_settings();
    void apply_window_decorations();
    void notify_theme_changed();

    struct ThemeData {
        std::string name;
        std::string gtk_theme;
        std::string icon_theme;
        std::string cursor_theme;
        std::string font;

        std::map<std::string, std::string> colors;
        std::map<std::string, std::string> settings;
    };

    std::string current_theme_;
    std::map<std::string, ThemeData> themes_;
    ThemeData active_theme_;

    std::vector<std::string> theme_paths_;
    GtkSettings* gtk_settings_;
};

/**
 * @brief Classic theme definitions
 */
namespace ClassicThemes {

// Malgoro Classic (Default - Windows XP inspired)
const char* CLASSIC_THEME = R"(
[Theme]
name=Malgoro Classic
gtk_theme=Malgoro-Classic
icon_theme=Malgoro-Icons
cursor_theme=Malgoro-Cursors
font=Sans 10

[Colors]
primary=#0078D7
secondary=#005A9E
accent=#FFB900
text=#000000
bg_light=#F0F0F0
bg_dark=#E0E0E0
border=#ACACAC
window_active=#0078D7
window_inactive=#999999

[WindowDecorations]
titlebar_height=24
border_width=1
button_size=18
corner_radius=0
gradient=true
)";

// Malgoro Luna (Blue theme)
const char* LUNA_THEME = R"(
[Theme]
name=Malgoro Luna
gtk_theme=Malgoro-Luna
icon_theme=Malgoro-Icons
cursor_theme=Malgoro-Cursors
font=Sans 10

[Colors]
primary=#3A6EA5
secondary=#2E568C
accent=#FFB900
text=#000000
bg_light=#ECE9D8
bg_dark=#D4D0C8
border=#0054E3
window_active=#3A6EA5
window_inactive=#7A96DF

[WindowDecorations]
titlebar_height=24
border_width=1
button_size=18
corner_radius=0
gradient=true
)";

// Malgoro Royale (Deep blue theme)
const char* ROYALE_THEME = R"(
[Theme]
name=Malgoro Royale
gtk_theme=Malgoro-Royale
icon_theme=Malgoro-Icons
cursor_theme=Malgoro-Cursors
font=Sans 10

[Colors]
primary=#4A5D89
secondary=#354766
accent=#FFB900
text=#000000
bg_light=#F4F4F4
bg_dark=#E4E4E4
border=#5A6D99
window_active=#4A5D89
window_inactive=#8A9DC9

[WindowDecorations]
titlebar_height=24
border_width=1
button_size=18
corner_radius=0
gradient=true
)";

// Malgoro Olive (Green theme)
const char* OLIVE_THEME = R"(
[Theme]
name=Malgoro Olive
gtk_theme=Malgoro-Olive
icon_theme=Malgoro-Icons
cursor_theme=Malgoro-Cursors
font=Sans 10

[Colors]
primary=#748B4B
secondary=#5C6D3A
accent=#FFB900
text=#000000
bg_light=#EBE8D9
bg_dark=#D9D6C7
border=#7E9B5B
window_active=#748B4B
window_inactive=#A4BB8B

[WindowDecorations]
titlebar_height=24
border_width=1
button_size=18
corner_radius=0
gradient=true
)";

// Malgoro Silver (Gray minimal theme)
const char* SILVER_THEME = R"(
[Theme]
name=Malgoro Silver
gtk_theme=Malgoro-Silver
icon_theme=Malgoro-Icons
cursor_theme=Malgoro-Cursors
font=Sans 10

[Colors]
primary=#9B9B9B
secondary=#7B7B7B
accent=#FFB900
text=#000000
bg_light=#EFEFEF
bg_dark=#DFDFDF
border=#ABABAB
window_active=#9B9B9B
window_inactive=#CBCBCB

[WindowDecorations]
titlebar_height=24
border_width=1
button_size=18
corner_radius=0
gradient=false
)";

} // namespace ClassicThemes

} // namespace MalgoroDE

#endif // MALGORO_THEME_MANAGER_H
