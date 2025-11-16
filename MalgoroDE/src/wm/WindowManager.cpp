#include "WindowManager.h"
#include "Window.h"
#include "Workspace.h"
#include "Decorator.h"
#include <iostream>
#include <cstring>
#include <algorithm>

namespace MalgoroDE {

// Static error handler flag
static bool wm_detected = false;

WindowManager::WindowManager()
    : display_(nullptr)
    , root_(0)
    , screen_(0)
    , current_workspace_(0)
    , current_theme_("luna")
    , enable_compositor_(false)
    , enable_animations_(true)
    , num_workspaces_(4)
    , focus_mode_(FocusMode::CLICK_TO_FOCUS)
    , placement_mode_(PlacementMode::SMART)
    , running_(false)
    , show_desktop_mode_(false)
{
}

WindowManager::~WindowManager() {
    shutdown();
}

bool WindowManager::initialize() {
    std::cout << "Malgoro Window Manager - Initializing..." << std::endl;

    // Connect to X11
    if (!connect_to_x11()) {
        std::cerr << "Failed to connect to X11 display" << std::endl;
        return false;
    }

    // Become the window manager
    if (!become_window_manager()) {
        std::cerr << "Another window manager is already running" << std::endl;
        return false;
    }

    // Initialize X11 atoms
    init_atoms();

    // Setup EWMH and ICCCM
    setup_ewmh();
    setup_icccm();

    // Initialize decorator
    decorator_ = std::make_unique<Decorator>(this);

    // Initialize workspaces
    for (int i = 0; i < num_workspaces_; ++i) {
        auto workspace = std::make_shared<Workspace>(i, "Workspace " + std::to_string(i + 1));
        workspaces_.push_back(workspace);
    }

    // Grab keyboard shortcuts
    grab_keys();

    // Grab mouse buttons for window management
    grab_buttons();

    // Scan for existing windows
    scan_existing_windows();

    running_ = true;
    std::cout << "Window manager initialized successfully" << std::endl;

    return true;
}

int WindowManager::run() {
    if (!running_) {
        std::cerr << "Window manager not initialized" << std::endl;
        return 1;
    }

    std::cout << "Starting event loop..." << std::endl;

    // Main event loop
    while (running_) {
        XEvent event;
        XNextEvent(display_, &event);
        handle_event(event);
    }

    std::cout << "Event loop terminated" << std::endl;
    return 0;
}

void WindowManager::shutdown() {
    if (!display_) {
        return;
    }

    std::cout << "Shutting down window manager..." << std::endl;

    running_ = false;

    // Unmanage all windows
    auto windows_copy = windows_;
    for (auto& [xwin, window] : windows_copy) {
        unmanage_window(xwin);
    }

    windows_.clear();
    workspaces_.clear();
    focused_window_.reset();
    decorator_.reset();

    if (display_) {
        XCloseDisplay(display_);
        display_ = nullptr;
    }

    std::cout << "Shutdown complete" << std::endl;
}

bool WindowManager::connect_to_x11() {
    display_ = XOpenDisplay(nullptr);
    if (!display_) {
        return false;
    }

    screen_ = DefaultScreen(display_);
    root_ = RootWindow(display_, screen_);

    return true;
}

bool WindowManager::become_window_manager() {
    // Set error handler to detect if another WM is running
    wm_detected = false;
    XSetErrorHandler(&WindowManager::on_wm_detected);

    // Try to select SubstructureRedirect on root window
    // This will fail if another WM is already running
    XSelectInput(display_, root_,
        SubstructureRedirectMask | SubstructureNotifyMask |
        StructureNotifyMask | PropertyChangeMask |
        ButtonPressMask | ButtonReleaseMask |
        KeyPressMask | KeyReleaseMask |
        FocusChangeMask | EnterWindowMask | LeaveWindowMask);

    XSync(display_, False);

    if (wm_detected) {
        return false;
    }

    // Set normal error handler
    XSetErrorHandler(&WindowManager::on_x_error);

    return true;
}

void WindowManager::init_atoms() {
    // WM protocols
    atoms_.wm_protocols = XInternAtom(display_, "WM_PROTOCOLS", False);
    atoms_.wm_delete_window = XInternAtom(display_, "WM_DELETE_WINDOW", False);
    atoms_.wm_state = XInternAtom(display_, "WM_STATE", False);
    atoms_.wm_change_state = XInternAtom(display_, "WM_CHANGE_STATE", False);
    atoms_.wm_take_focus = XInternAtom(display_, "WM_TAKE_FOCUS", False);

    // EWMH atoms
    atoms_.net_supported = XInternAtom(display_, "_NET_SUPPORTED", False);
    atoms_.net_client_list = XInternAtom(display_, "_NET_CLIENT_LIST", False);
    atoms_.net_client_list_stacking = XInternAtom(display_, "_NET_CLIENT_LIST_STACKING", False);
    atoms_.net_number_of_desktops = XInternAtom(display_, "_NET_NUMBER_OF_DESKTOPS", False);
    atoms_.net_desktop_geometry = XInternAtom(display_, "_NET_DESKTOP_GEOMETRY", False);
    atoms_.net_desktop_viewport = XInternAtom(display_, "_NET_DESKTOP_VIEWPORT", False);
    atoms_.net_current_desktop = XInternAtom(display_, "_NET_CURRENT_DESKTOP", False);
    atoms_.net_desktop_names = XInternAtom(display_, "_NET_DESKTOP_NAMES", False);
    atoms_.net_active_window = XInternAtom(display_, "_NET_ACTIVE_WINDOW", False);
    atoms_.net_workarea = XInternAtom(display_, "_NET_WORKAREA", False);
    atoms_.net_supporting_wm_check = XInternAtom(display_, "_NET_SUPPORTING_WM_CHECK", False);
    atoms_.net_wm_name = XInternAtom(display_, "_NET_WM_NAME", False);
    atoms_.net_wm_state = XInternAtom(display_, "_NET_WM_STATE", False);
    atoms_.net_wm_state_modal = XInternAtom(display_, "_NET_WM_STATE_MODAL", False);
    atoms_.net_wm_state_sticky = XInternAtom(display_, "_NET_WM_STATE_STICKY", False);
    atoms_.net_wm_state_maximized_vert = XInternAtom(display_, "_NET_WM_STATE_MAXIMIZED_VERT", False);
    atoms_.net_wm_state_maximized_horz = XInternAtom(display_, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
    atoms_.net_wm_state_shaded = XInternAtom(display_, "_NET_WM_STATE_SHADED", False);
    atoms_.net_wm_state_skip_taskbar = XInternAtom(display_, "_NET_WM_STATE_SKIP_TASKBAR", False);
    atoms_.net_wm_state_skip_pager = XInternAtom(display_, "_NET_WM_STATE_SKIP_PAGER", False);
    atoms_.net_wm_state_hidden = XInternAtom(display_, "_NET_WM_STATE_HIDDEN", False);
    atoms_.net_wm_state_fullscreen = XInternAtom(display_, "_NET_WM_STATE_FULLSCREEN", False);
    atoms_.net_wm_state_above = XInternAtom(display_, "_NET_WM_STATE_ABOVE", False);
    atoms_.net_wm_state_below = XInternAtom(display_, "_NET_WM_STATE_BELOW", False);
    atoms_.net_wm_window_type = XInternAtom(display_, "_NET_WM_WINDOW_TYPE", False);
    atoms_.net_wm_window_type_desktop = XInternAtom(display_, "_NET_WM_WINDOW_TYPE_DESKTOP", False);
    atoms_.net_wm_window_type_dock = XInternAtom(display_, "_NET_WM_WINDOW_TYPE_DOCK", False);
    atoms_.net_wm_window_type_toolbar = XInternAtom(display_, "_NET_WM_WINDOW_TYPE_TOOLBAR", False);
    atoms_.net_wm_window_type_menu = XInternAtom(display_, "_NET_WM_WINDOW_TYPE_MENU", False);
    atoms_.net_wm_window_type_utility = XInternAtom(display_, "_NET_WM_WINDOW_TYPE_UTILITY", False);
    atoms_.net_wm_window_type_splash = XInternAtom(display_, "_NET_WM_WINDOW_TYPE_SPLASH", False);
    atoms_.net_wm_window_type_dialog = XInternAtom(display_, "_NET_WM_WINDOW_TYPE_DIALOG", False);
    atoms_.net_wm_window_type_normal = XInternAtom(display_, "_NET_WM_WINDOW_TYPE_NORMAL", False);
    atoms_.net_close_window = XInternAtom(display_, "_NET_CLOSE_WINDOW", False);
    atoms_.net_moveresize_window = XInternAtom(display_, "_NET_MOVERESIZE_WINDOW", False);
    atoms_.net_wm_moveresize = XInternAtom(display_, "_NET_WM_MOVERESIZE", False);
}

void WindowManager::setup_ewmh() {
    // Advertise EWMH support
    Atom supported[] = {
        atoms_.net_supported,
        atoms_.net_client_list,
        atoms_.net_client_list_stacking,
        atoms_.net_number_of_desktops,
        atoms_.net_desktop_geometry,
        atoms_.net_desktop_viewport,
        atoms_.net_current_desktop,
        atoms_.net_desktop_names,
        atoms_.net_active_window,
        atoms_.net_workarea,
        atoms_.net_supporting_wm_check,
        atoms_.net_wm_name,
        atoms_.net_wm_state,
        atoms_.net_wm_state_modal,
        atoms_.net_wm_state_sticky,
        atoms_.net_wm_state_maximized_vert,
        atoms_.net_wm_state_maximized_horz,
        atoms_.net_wm_state_shaded,
        atoms_.net_wm_state_skip_taskbar,
        atoms_.net_wm_state_skip_pager,
        atoms_.net_wm_state_hidden,
        atoms_.net_wm_state_fullscreen,
        atoms_.net_wm_state_above,
        atoms_.net_wm_state_below,
        atoms_.net_wm_window_type,
        atoms_.net_wm_window_type_desktop,
        atoms_.net_wm_window_type_dock,
        atoms_.net_wm_window_type_toolbar,
        atoms_.net_wm_window_type_menu,
        atoms_.net_wm_window_type_utility,
        atoms_.net_wm_window_type_splash,
        atoms_.net_wm_window_type_dialog,
        atoms_.net_wm_window_type_normal,
        atoms_.net_close_window,
        atoms_.net_moveresize_window,
        atoms_.net_wm_moveresize
    };

    XChangeProperty(display_, root_, atoms_.net_supported,
        XA_ATOM, 32, PropModeReplace,
        (unsigned char*)supported, sizeof(supported) / sizeof(Atom));

    // Set number of desktops
    unsigned long num_desktops = num_workspaces_;
    XChangeProperty(display_, root_, atoms_.net_number_of_desktops,
        XA_CARDINAL, 32, PropModeReplace,
        (unsigned char*)&num_desktops, 1);

    // Set current desktop
    unsigned long current = current_workspace_;
    XChangeProperty(display_, root_, atoms_.net_current_desktop,
        XA_CARDINAL, 32, PropModeReplace,
        (unsigned char*)&current, 1);

    // Set WM name
    const char* wm_name = "Malgoro";
    XChangeProperty(display_, root_, atoms_.net_wm_name,
        XInternAtom(display_, "UTF8_STRING", False), 8, PropModeReplace,
        (unsigned char*)wm_name, strlen(wm_name));
}

void WindowManager::setup_icccm() {
    // Set WM_CLASS for the window manager
    XClassHint class_hint;
    class_hint.res_name = (char*)"malgoro-wm";
    class_hint.res_class = (char*)"MalgoroWM";
    XSetClassHint(display_, root_, &class_hint);
}

void WindowManager::grab_keys() {
    // Grab common window manager shortcuts

    // Ungrab all first
    XUngrabKey(display_, AnyKey, AnyModifier, root_);

    unsigned int modifiers[] = {
        0,
        LockMask,
        Mod2Mask,
        LockMask | Mod2Mask
    };

    // Alt+Tab (window switching)
    KeyCode tab_key = XKeysymToKeycode(display_, XK_Tab);
    for (auto mod : modifiers) {
        XGrabKey(display_, tab_key, Mod1Mask | mod, root_,
            True, GrabModeAsync, GrabModeAsync);
        XGrabKey(display_, tab_key, Mod1Mask | ShiftMask | mod, root_,
            True, GrabModeAsync, GrabModeAsync);
    }

    // Alt+F4 (close window)
    KeyCode f4_key = XKeysymToKeycode(display_, XK_F4);
    for (auto mod : modifiers) {
        XGrabKey(display_, f4_key, Mod1Mask | mod, root_,
            True, GrabModeAsync, GrabModeAsync);
    }

    // Alt+F10 (maximize)
    KeyCode f10_key = XKeysymToKeycode(display_, XK_F10);
    for (auto mod : modifiers) {
        XGrabKey(display_, f10_key, Mod1Mask | mod, root_,
            True, GrabModeAsync, GrabModeAsync);
    }

    // Ctrl+Alt+Left/Right (workspace switching)
    KeyCode left_key = XKeysymToKeycode(display_, XK_Left);
    KeyCode right_key = XKeysymToKeycode(display_, XK_Right);
    for (auto mod : modifiers) {
        XGrabKey(display_, left_key, ControlMask | Mod1Mask | mod, root_,
            True, GrabModeAsync, GrabModeAsync);
        XGrabKey(display_, right_key, ControlMask | Mod1Mask | mod, root_,
            True, GrabModeAsync, GrabModeAsync);
    }
}

void WindowManager::grab_buttons() {
    // Grab mouse buttons on client windows for click-to-focus and window movement

    // Ungrab all first
    XUngrabButton(display_, AnyButton, AnyModifier, root_);

    // Grab Alt+Button1 (move window)
    XGrabButton(display_, Button1, Mod1Mask, root_, True,
        ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
        GrabModeAsync, GrabModeAsync, None, None);

    // Grab Alt+Button3 (resize window)
    XGrabButton(display_, Button3, Mod1Mask, root_, True,
        ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
        GrabModeAsync, GrabModeAsync, None, None);
}

void WindowManager::scan_existing_windows() {
    XGrabServer(display_);

    ::Window returned_root, returned_parent;
    ::Window* top_level_windows;
    unsigned int num_top_level_windows;

    XQueryTree(display_, root_,
        &returned_root, &returned_parent,
        &top_level_windows, &num_top_level_windows);

    for (unsigned int i = 0; i < num_top_level_windows; ++i) {
        XWindowAttributes attrs;
        if (XGetWindowAttributes(display_, top_level_windows[i], &attrs)) {
            // Only manage visible windows that are not override-redirect
            if (!attrs.override_redirect && attrs.map_state == IsViewable) {
                manage_window(top_level_windows[i]);
            }
        }
    }

    XFree(top_level_windows);
    XUngrabServer(display_);
}

bool WindowManager::manage_window(::Window xwindow) {
    // Check if already managed
    if (windows_.find(xwindow) != windows_.end()) {
        return false;
    }

    // Get window attributes
    XWindowAttributes attrs;
    if (!XGetWindowAttributes(display_, xwindow, &attrs)) {
        return false;
    }

    // Don't manage override-redirect windows
    if (attrs.override_redirect) {
        return false;
    }

    std::cout << "Managing window: " << xwindow << std::endl;

    // Create Window object
    auto window = std::make_shared<Window>(xwindow, display_);
    windows_[xwindow] = window;

    // Select events we want from this window
    XSelectInput(display_, xwindow,
        EnterWindowMask | LeaveWindowMask | FocusChangeMask |
        PropertyChangeMask | StructureNotifyMask);

    // Add to current workspace
    if (current_workspace_ < workspaces_.size()) {
        workspaces_[current_workspace_]->add_window(window);
    }

    // Create frame/decoration
    if (decorator_) {
        decorator_->decorate_window(window);
    }

    // Map the window
    XMapWindow(display_, xwindow);

    // Update client list
    update_client_list();

    return true;
}

bool WindowManager::unmanage_window(::Window xwindow) {
    auto it = windows_.find(xwindow);
    if (it == windows_.end()) {
        return false;
    }

    std::cout << "Unmanaging window: " << xwindow << std::endl;

    auto window = it->second;

    // Remove from focused window if needed
    if (focused_window_ == window) {
        focused_window_.reset();
    }

    // Remove from all workspaces
    for (auto& workspace : workspaces_) {
        workspace->remove_window(window);
    }

    // Remove decoration
    if (decorator_) {
        decorator_->undecorate_window(window);
    }

    // Remove from map
    windows_.erase(it);

    // Update client list
    update_client_list();

    return true;
}

std::shared_ptr<Window> WindowManager::find_window(::Window xwindow) {
    auto it = windows_.find(xwindow);
    if (it != windows_.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<std::shared_ptr<Window>> WindowManager::get_all_windows() {
    std::vector<std::shared_ptr<Window>> result;
    result.reserve(windows_.size());
    for (auto& [xwin, window] : windows_) {
        result.push_back(window);
    }
    return result;
}

void WindowManager::focus_window(std::shared_ptr<Window> window) {
    if (!window) {
        return;
    }

    // Unfocus previous window
    if (focused_window_ && focused_window_ != window) {
        if (decorator_) {
            decorator_->set_window_active(focused_window_, false);
        }
    }

    // Focus new window
    focused_window_ = window;
    XSetInputFocus(display_, window->get_xwindow(), RevertToPointerRoot, CurrentTime);
    XRaiseWindow(display_, window->get_xwindow());

    // Update decoration
    if (decorator_) {
        decorator_->set_window_active(window, true);
    }

    // Update EWMH active window
    update_active_window();
}

std::shared_ptr<Window> WindowManager::get_focused_window() {
    return focused_window_;
}

void WindowManager::cycle_focus(bool reverse) {
    if (windows_.empty()) {
        return;
    }

    auto windows = get_all_windows();
    if (windows.empty()) {
        return;
    }

    // Find current focused window index
    int current_index = -1;
    for (size_t i = 0; i < windows.size(); ++i) {
        if (windows[i] == focused_window_) {
            current_index = i;
            break;
        }
    }

    // Calculate next index
    int next_index;
    if (current_index == -1) {
        next_index = 0;
    } else if (reverse) {
        next_index = (current_index - 1 + windows.size()) % windows.size();
    } else {
        next_index = (current_index + 1) % windows.size();
    }

    // Focus next window
    focus_window(windows[next_index]);
}

void WindowManager::close_window(std::shared_ptr<Window> window) {
    if (!window) {
        return;
    }

    // Try to close gracefully using WM_DELETE_WINDOW
    XEvent event;
    memset(&event, 0, sizeof(event));
    event.type = ClientMessage;
    event.xclient.window = window->get_xwindow();
    event.xclient.message_type = atoms_.wm_protocols;
    event.xclient.format = 32;
    event.xclient.data.l[0] = atoms_.wm_delete_window;
    event.xclient.data.l[1] = CurrentTime;

    XSendEvent(display_, window->get_xwindow(), False, NoEventMask, &event);
    XFlush(display_);
}

void WindowManager::maximize_window(std::shared_ptr<Window> window) {
    if (!window) {
        return;
    }

    // TODO: Implement maximize
    std::cout << "Maximize window: " << window->get_xwindow() << std::endl;
}

void WindowManager::update_client_list() {
    std::vector<::Window> client_list;
    client_list.reserve(windows_.size());

    for (auto& [xwin, window] : windows_) {
        client_list.push_back(xwin);
    }

    if (!client_list.empty()) {
        XChangeProperty(display_, root_, atoms_.net_client_list,
            XA_WINDOW, 32, PropModeReplace,
            (unsigned char*)client_list.data(), client_list.size());
    } else {
        XDeleteProperty(display_, root_, atoms_.net_client_list);
    }
}

void WindowManager::update_active_window() {
    if (focused_window_) {
        ::Window xwin = focused_window_->get_xwindow();
        XChangeProperty(display_, root_, atoms_.net_active_window,
            XA_WINDOW, 32, PropModeReplace,
            (unsigned char*)&xwin, 1);
    } else {
        XDeleteProperty(display_, root_, atoms_.net_active_window);
    }
}

// Event handlers

void WindowManager::handle_event(XEvent& event) {
    switch (event.type) {
        case MapRequest:
            handle_map_request(event.xmaprequest);
            break;
        case UnmapNotify:
            handle_unmap_notify(event.xunmap);
            break;
        case DestroyNotify:
            handle_destroy_notify(event.xdestroywindow);
            break;
        case ConfigureRequest:
            handle_configure_request(event.xconfigurerequest);
            break;
        case ConfigureNotify:
            handle_configure_notify(event.xconfigure);
            break;
        case PropertyNotify:
            handle_property_notify(event.xproperty);
            break;
        case ClientMessage:
            handle_client_message(event.xclient);
            break;
        case ButtonPress:
            handle_button_press(event.xbutton);
            break;
        case ButtonRelease:
            handle_button_release(event.xbutton);
            break;
        case MotionNotify:
            handle_motion_notify(event.xmotion);
            break;
        case KeyPress:
            handle_key_press(event.xkey);
            break;
        case EnterNotify:
            handle_enter_notify(event.xcrossing);
            break;
        case LeaveNotify:
            handle_leave_notify(event.xcrossing);
            break;
        case FocusIn:
            handle_focus_in(event.xfocus);
            break;
        case FocusOut:
            handle_focus_out(event.xfocus);
            break;
    }
}

void WindowManager::handle_map_request(XMapRequestEvent& event) {
    manage_window(event.window);
}

void WindowManager::handle_unmap_notify(XUnmapEvent& event) {
    unmanage_window(event.window);
}

void WindowManager::handle_destroy_notify(XDestroyWindowEvent& event) {
    unmanage_window(event.window);
}

void WindowManager::handle_configure_request(XConfigureRequestEvent& event) {
    XWindowChanges changes;
    changes.x = event.x;
    changes.y = event.y;
    changes.width = event.width;
    changes.height = event.height;
    changes.border_width = event.border_width;
    changes.sibling = event.above;
    changes.stack_mode = event.detail;

    XConfigureWindow(display_, event.window, event.value_mask, &changes);
}

void WindowManager::handle_configure_notify(XConfigureEvent& event) {
    // Handle configuration changes
}

void WindowManager::handle_property_notify(XPropertyEvent& event) {
    // Handle property changes
}

void WindowManager::handle_client_message(XClientMessageEvent& event) {
    handle_ewmh_message(event);
}

void WindowManager::handle_button_press(XButtonEvent& event) {
    auto window = find_window(event.window);
    if (window) {
        focus_window(window);
    }
}

void WindowManager::handle_button_release(XButtonEvent& event) {
    // Handle button release
}

void WindowManager::handle_motion_notify(XMotionEvent& event) {
    // Handle mouse motion
}

void WindowManager::handle_key_press(XKeyEvent& event) {
    KeySym keysym = XLookupKeysym(&event, 0);
    unsigned int modifiers = event.state & (ShiftMask | ControlMask | Mod1Mask | Mod4Mask);

    // Alt+Tab - Switch windows
    if (keysym == XK_Tab && (modifiers & Mod1Mask)) {
        bool reverse = (modifiers & ShiftMask);
        cycle_focus(reverse);
    }
    // Alt+F4 - Close window
    else if (keysym == XK_F4 && (modifiers & Mod1Mask)) {
        if (focused_window_) {
            close_window(focused_window_);
        }
    }
    // Alt+F10 - Maximize
    else if (keysym == XK_F10 && (modifiers & Mod1Mask)) {
        if (focused_window_) {
            toggle_maximize(focused_window_);
        }
    }
}

void WindowManager::handle_enter_notify(XCrossingEvent& event) {
    if (focus_mode_ == FocusMode::FOCUS_FOLLOWS_MOUSE ||
        focus_mode_ == FocusMode::SLOPPY_FOCUS) {
        auto window = find_window(event.window);
        if (window) {
            focus_window(window);
        }
    }
}

void WindowManager::handle_leave_notify(XCrossingEvent& event) {
    // Handle leave notify
}

void WindowManager::handle_focus_in(XFocusChangeEvent& event) {
    // Handle focus in
}

void WindowManager::handle_focus_out(XFocusChangeEvent& event) {
    // Handle focus out
}

void WindowManager::handle_ewmh_message(XClientMessageEvent& event) {
    // Handle EWMH client messages
    if (event.message_type == atoms_.net_active_window) {
        auto window = find_window(event.window);
        if (window) {
            focus_window(window);
        }
    }
    else if (event.message_type == atoms_.net_close_window) {
        auto window = find_window(event.window);
        if (window) {
            close_window(window);
        }
    }
}

// Static error handlers

int WindowManager::on_x_error(Display* display, XErrorEvent* event) {
    char error_text[1024];
    XGetErrorText(display, event->error_code, error_text, sizeof(error_text));
    std::cerr << "X11 Error: " << error_text << std::endl;
    std::cerr << "  Request code: " << (int)event->request_code << std::endl;
    std::cerr << "  Minor code: " << (int)event->minor_code << std::endl;
    std::cerr << "  Resource ID: " << event->resourceid << std::endl;
    return 0;
}

int WindowManager::on_wm_detected(Display* display, XErrorEvent* event) {
    wm_detected = true;
    return 0;
}

// Stubs for remaining functions

void WindowManager::toggle_maximize(std::shared_ptr<Window> window) {
    // TODO: Implement
}

void WindowManager::switch_workspace(int workspace_index) {
    // TODO: Implement
}

int WindowManager::get_current_workspace() {
    return current_workspace_;
}

int WindowManager::get_workspace_count() {
    return num_workspaces_;
}

void WindowManager::move_window_to_workspace(std::shared_ptr<Window> window, int workspace) {
    // TODO: Implement
}

void WindowManager::minimize_window(std::shared_ptr<Window> window) {
    // TODO: Implement
}

void WindowManager::unmaximize_window(std::shared_ptr<Window> window) {
    // TODO: Implement
}

void WindowManager::shade_window(std::shared_ptr<Window> window) {
    // TODO: Implement
}

void WindowManager::fullscreen_window(std::shared_ptr<Window> window) {
    // TODO: Implement
}

void WindowManager::show_desktop() {
    // TODO: Implement
}

void WindowManager::tile_windows_horizontally() {
    // TODO: Implement
}

void WindowManager::tile_windows_vertically() {
    // TODO: Implement
}

void WindowManager::cascade_windows() {
    // TODO: Implement
}

void WindowManager::load_config() {
    // TODO: Implement
}

void WindowManager::save_config() {
    // TODO: Implement
}

void WindowManager::reload_config() {
    // TODO: Implement
}

void WindowManager::set_theme(const std::string& theme_name) {
    current_theme_ = theme_name;
    // TODO: Apply theme
}

void WindowManager::update_window_list() {
    // TODO: Implement
}

void WindowManager::update_desktop_names() {
    // TODO: Implement
}

} // namespace MalgoroDE
