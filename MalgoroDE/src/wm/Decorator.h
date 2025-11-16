#ifndef MALGORO_DECORATOR_H
#define MALGORO_DECORATOR_H

#include <string>
#include <memory>
#include <X11/Xlib.h>
#include <cairo/cairo.h>

namespace MalgoroDE {

class Window;

/**
 * @brief Window decoration renderer (titlebars, borders, buttons)
 */
class Decorator {
public:
    Decorator(Display* display);
    ~Decorator();

    /**
     * @brief Draw window decorations
     */
    void draw(std::shared_ptr<Window> window, bool focused);

    /**
     * @brief Handle button click on decoration
     * @return true if click was on decoration button
     */
    bool handle_button_press(std::shared_ptr<Window> window, int x, int y, unsigned int button);

    /**
     * @brief Load theme
     */
    void load_theme(const std::string& theme_name);

    /**
     * @brief Get titlebar height for theme
     */
    int get_titlebar_height() const { return titlebar_height_; }

    /**
     * @brief Get border width for theme
     */
    int get_border_width() const { return border_width_; }

    /**
     * @brief Check if position is in titlebar
     */
    bool is_in_titlebar(std::shared_ptr<Window> window, int x, int y) const;

    /**
     * @brief Check if position is on resize border
     */
    bool is_on_border(std::shared_ptr<Window> window, int x, int y, int& border_mask) const;

    // Border masks
    enum BorderMask {
        BORDER_NONE = 0,
        BORDER_TOP = 1,
        BORDER_BOTTOM = 2,
        BORDER_LEFT = 4,
        BORDER_RIGHT = 8,
        BORDER_TOP_LEFT = BORDER_TOP | BORDER_LEFT,
        BORDER_TOP_RIGHT = BORDER_TOP | BORDER_RIGHT,
        BORDER_BOTTOM_LEFT = BORDER_BOTTOM | BORDER_LEFT,
        BORDER_BOTTOM_RIGHT = BORDER_BOTTOM | BORDER_RIGHT
    };

private:
    void draw_titlebar(cairo_t* cr, std::shared_ptr<Window> window, bool focused);
    void draw_border(cairo_t* cr, std::shared_ptr<Window> window, bool focused);
    void draw_buttons(cairo_t* cr, std::shared_ptr<Window> window, bool focused);
    void draw_title_text(cairo_t* cr, std::shared_ptr<Window> window, bool focused);
    void draw_icon(cairo_t* cr, std::shared_ptr<Window> window);

    // Button detection
    enum class Button {
        NONE,
        CLOSE,
        MAXIMIZE,
        MINIMIZE,
        MENU,
        SHADE
    };

    Button get_button_at(std::shared_ptr<Window> window, int x, int y) const;
    void get_button_rect(std::shared_ptr<Window> window, Button button, int& x, int& y, int& w, int& h) const;

    // Theme data
    struct Theme {
        // Colors
        struct {
            double r, g, b;
        } titlebar_active, titlebar_inactive;

        struct {
            double r, g, b;
        } border_active, border_inactive;

        struct {
            double r, g, b;
        } text_active, text_inactive;

        struct {
            double r, g, b;
        } button_close, button_maximize, button_minimize;

        // Dimensions
        int titlebar_height;
        int border_width;
        int button_size;
        int button_spacing;
        int icon_size;

        // Font
        std::string font_family;
        int font_size;
        bool font_bold;

        // Style
        bool gradient_titlebar;
        bool rounded_corners;
        int corner_radius;
    };

    Display* display_;
    Theme theme_;
    int titlebar_height_;
    int border_width_;

    // Button layout
    enum class ButtonPosition {
        LEFT,
        RIGHT
    };

    struct ButtonLayout {
        Button button;
        ButtonPosition position;
    };

    std::vector<ButtonLayout> button_layout_;
};

} // namespace MalgoroDE

#endif // MALGORO_DECORATOR_H
