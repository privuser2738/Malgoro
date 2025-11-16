#ifndef MALGORO_APPLET_H
#define MALGORO_APPLET_H

#include <gtk/gtk.h>
#include <string>

namespace MalgoroDE {

/**
 * @brief Base class for panel applets
 */
class Applet {
public:
    Applet(const std::string& name);
    virtual ~Applet();

    /**
     * @brief Initialize the applet
     */
    virtual bool initialize() = 0;

    /**
     * @brief Get the applet widget
     */
    virtual GtkWidget* get_widget() = 0;

    /**
     * @brief Update applet content
     */
    virtual void update() = 0;

    /**
     * @brief Get applet name
     */
    std::string get_name() const { return name_; }

    /**
     * @brief Should applet expand to fill space
     */
    virtual bool should_expand() const { return false; }

    /**
     * @brief Get preferred size
     */
    virtual int get_preferred_size() const { return -1; }

    /**
     * @brief Handle configuration
     */
    virtual void configure() {}

    /**
     * @brief Load settings
     */
    virtual void load_settings() {}

    /**
     * @brief Save settings
     */
    virtual void save_settings() {}

protected:
    std::string name_;
    GtkWidget* container_;
};

} // namespace MalgoroDE

#endif // MALGORO_APPLET_H
