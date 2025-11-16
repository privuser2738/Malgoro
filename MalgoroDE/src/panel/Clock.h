#ifndef MALGORO_CLOCK_H
#define MALGORO_CLOCK_H

#include "Applet.h"
#include <string>

namespace MalgoroDE {

/**
 * @brief Clock and calendar applet
 */
class Clock : public Applet {
public:
    Clock();
    ~Clock() override;

    bool initialize() override;
    GtkWidget* get_widget() override;
    void update() override;

    // Format
    void set_format(const std::string& format) { time_format_ = format; }
    void set_show_seconds(bool show) { show_seconds_ = show; }
    void set_show_date(bool show) { show_date_ = show; }
    void set_24hour(bool use_24) { use_24hour_ = use_24; }

private:
    void create_ui();
    void update_time();
    void show_calendar();

    static gboolean on_timeout(gpointer data);
    static gboolean on_button_press(GtkWidget* widget, GdkEventButton* event, gpointer data);

    GtkWidget* button_;
    GtkWidget* label_;
    GtkWidget* calendar_window_;
    GtkWidget* calendar_;

    std::string time_format_;
    bool show_seconds_;
    bool show_date_;
    bool use_24hour_;

    guint timeout_id_;
};

} // namespace MalgoroDE

#endif // MALGORO_CLOCK_H
