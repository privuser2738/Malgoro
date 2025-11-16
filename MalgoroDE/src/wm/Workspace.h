#ifndef MALGORO_WORKSPACE_H
#define MALGORO_WORKSPACE_H

#include <string>
#include <vector>
#include <memory>

namespace MalgoroDE {

class Window;

/**
 * @brief Represents a virtual desktop/workspace
 */
class Workspace {
public:
    Workspace(int index, const std::string& name = "");
    ~Workspace();

    // Properties
    int get_index() const { return index_; }
    std::string get_name() const { return name_; }
    void set_name(const std::string& name) { name_ = name; }

    // Window management
    void add_window(std::shared_ptr<Window> window);
    void remove_window(std::shared_ptr<Window> window);
    bool has_window(std::shared_ptr<Window> window) const;
    std::vector<std::shared_ptr<Window>> get_windows() const { return windows_; }
    int get_window_count() const { return windows_.size(); }

    // Visibility
    void show();
    void hide();
    bool is_active() const { return active_; }
    void set_active(bool active) { active_ = active; }

    // Layout
    void tile_horizontally();
    void tile_vertically();
    void cascade();

private:
    int index_;
    std::string name_;
    std::vector<std::shared_ptr<Window>> windows_;
    bool active_;
};

} // namespace MalgoroDE

#endif // MALGORO_WORKSPACE_H
