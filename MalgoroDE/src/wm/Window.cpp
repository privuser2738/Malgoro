#include "Window.h"
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <cstring>
#include <iostream>

namespace MalgoroDE {

Window::Window(::Window xwindow, Display* display)
    : display_(display)
    , xwindow_(xwindow)
    , frame_(0)
    , x_(0), y_(0)
    , width_(0), height_(0)
    , old_x_(0), old_y_(0)
    , old_width_(0), old_height_(0)
    , mapped_(false)
    , minimized_(false)
    , maximized_(false)
    , fullscreen_(false)
    , shaded_(false)
    , sticky_(false)
    , above_(false)
    , below_(false)
    , modal_(false)
    , focused_(false)
    , skip_taskbar_(false)
    , skip_pager_(false)
    , type_(Type::NORMAL)
    , workspace_(0)
    , supports_delete_(false)
    , supports_focus_(false)
    , min_width_(1), min_height_(1)
    , max_width_(INT_MAX), max_height_(INT_MAX)
    , base_width_(0), base_height_(0)
    , width_inc_(1), height_inc_(1)
    , min_aspect_(0.0f), max_aspect_(0.0f)
    , border_width_(1)
    , titlebar_height_(24)
{
    // Get initial window geometry
    XWindowAttributes attrs;
    if (XGetWindowAttributes(display_, xwindow_, &attrs)) {
        x_ = attrs.x;
        y_ = attrs.y;
        width_ = attrs.width;
        height_ = attrs.height;
    }

    // Update window properties
    update_title();
    update_class();
    update_hints();
    update_size_hints();
    update_protocols();
    update_type();
}

Window::~Window() {
    destroy_frame();
}

void Window::set_geometry(int x, int y, int width, int height) {
    // Apply size hints
    apply_size_hints(width, height);

    x_ = x;
    y_ = y;
    width_ = width;
    height_ = height;

    // Move and resize the client window
    XMoveResizeWindow(display_, xwindow_, 0, titlebar_height_, width_, height_);

    // Update frame if it exists
    if (frame_) {
        XMoveResizeWindow(display_, frame_, x_, y_,
            width_ + 2 * border_width_,
            height_ + titlebar_height_ + border_width_);
    }

    send_configure_notify();
}

void Window::get_frame_geometry(int& x, int& y, int& width, int& height) const {
    x = x_;
    y = y_;
    width = width_ + 2 * border_width_;
    height = height_ + titlebar_height_ + border_width_;
}

void Window::set_mapped(bool mapped) {
    mapped_ = mapped;
    if (mapped) {
        XMapWindow(display_, xwindow_);
        if (frame_) {
            XMapWindow(display_, frame_);
        }
    } else {
        XUnmapWindow(display_, xwindow_);
        if (frame_) {
            XUnmapWindow(display_, frame_);
        }
    }
}

void Window::set_minimized(bool minimized) {
    minimized_ = minimized;
    if (minimized) {
        XUnmapWindow(display_, xwindow_);
        if (frame_) {
            XUnmapWindow(display_, frame_);
        }
    } else {
        XMapWindow(display_, xwindow_);
        if (frame_) {
            XMapWindow(display_, frame_);
        }
    }
}

void Window::set_maximized(bool maximized) {
    if (maximized == maximized_) {
        return;
    }

    if (maximized) {
        // Save current geometry
        old_x_ = x_;
        old_y_ = y_;
        old_width_ = width_;
        old_height_ = height_;

        // Get screen size
        Screen* screen = DefaultScreenOfDisplay(display_);
        int screen_width = WidthOfScreen(screen);
        int screen_height = HeightOfScreen(screen);

        // Maximize (accounting for titlebar and borders)
        set_geometry(0, 0, screen_width, screen_height - titlebar_height_);
    } else {
        // Restore previous geometry
        set_geometry(old_x_, old_y_, old_width_, old_height_);
    }

    maximized_ = maximized;
}

void Window::set_fullscreen(bool fullscreen) {
    fullscreen_ = fullscreen;
    // TODO: Implement fullscreen mode
}

void Window::set_shaded(bool shaded) {
    shaded_ = shaded;
    // TODO: Implement shading (roll up window to titlebar only)
}

void Window::set_sticky(bool sticky) {
    sticky_ = sticky;
}

void Window::set_above(bool above) {
    above_ = above;
    if (above) {
        XRaiseWindow(display_, frame_ ? frame_ : xwindow_);
    }
}

void Window::set_below(bool below) {
    below_ = below;
    if (below) {
        XLowerWindow(display_, frame_ ? frame_ : xwindow_);
    }
}

void Window::set_focused(bool focused) {
    focused_ = focused;
}

void Window::take_focus() {
    if (supports_focus_) {
        // Send WM_TAKE_FOCUS message
        Atom wm_protocols = XInternAtom(display_, "WM_PROTOCOLS", False);
        Atom wm_take_focus = XInternAtom(display_, "WM_TAKE_FOCUS", False);

        XEvent event;
        memset(&event, 0, sizeof(event));
        event.type = ClientMessage;
        event.xclient.window = xwindow_;
        event.xclient.message_type = wm_protocols;
        event.xclient.format = 32;
        event.xclient.data.l[0] = wm_take_focus;
        event.xclient.data.l[1] = CurrentTime;

        XSendEvent(display_, xwindow_, False, NoEventMask, &event);
    }
    XSetInputFocus(display_, xwindow_, RevertToPointerRoot, CurrentTime);
}

void Window::create_frame() {
    if (frame_) {
        return;  // Frame already exists
    }

    // Create frame window
    XSetWindowAttributes attrs;
    attrs.background_pixel = WhitePixel(display_, DefaultScreen(display_));
    attrs.border_pixel = BlackPixel(display_, DefaultScreen(display_));
    attrs.event_mask = SubstructureRedirectMask | SubstructureNotifyMask |
                      ButtonPressMask | ButtonReleaseMask |
                      PointerMotionMask | ExposureMask;

    frame_ = XCreateWindow(display_,
        RootWindow(display_, DefaultScreen(display_)),
        x_, y_,
        width_ + 2 * border_width_,
        height_ + titlebar_height_ + border_width_,
        0,
        CopyFromParent,
        InputOutput,
        CopyFromParent,
        CWBackPixel | CWBorderPixel | CWEventMask,
        &attrs);

    // Reparent client window to frame
    XReparentWindow(display_, xwindow_, frame_, 0, titlebar_height_);

    // Map frame
    XMapWindow(display_, frame_);

    std::cout << "Created frame for window " << xwindow_ << std::endl;
}

void Window::destroy_frame() {
    if (!frame_) {
        return;
    }

    // Reparent client window back to root
    ::Window root = RootWindow(display_, DefaultScreen(display_));
    XReparentWindow(display_, xwindow_, root, x_, y_);

    // Destroy frame
    XDestroyWindow(display_, frame_);
    frame_ = 0;

    std::cout << "Destroyed frame for window " << xwindow_ << std::endl;
}

void Window::update_frame() {
    if (frame_) {
        XMoveResizeWindow(display_, frame_, x_, y_,
            width_ + 2 * border_width_,
            height_ + titlebar_height_ + border_width_);
    }
}

void Window::redraw_frame() {
    if (!frame_) {
        return;
    }

    // TODO: Trigger frame redraw (handled by Decorator)
    XClearWindow(display_, frame_);
}

void Window::map() {
    XMapWindow(display_, xwindow_);
    if (frame_) {
        XMapWindow(display_, frame_);
    }
    mapped_ = true;
}

void Window::unmap() {
    XUnmapWindow(display_, xwindow_);
    if (frame_) {
        XUnmapWindow(display_, frame_);
    }
    mapped_ = false;
}

void Window::raise() {
    XRaiseWindow(display_, frame_ ? frame_ : xwindow_);
}

void Window::lower() {
    XLowerWindow(display_, frame_ ? frame_ : xwindow_);
}

void Window::close() {
    if (supports_delete_) {
        // Send WM_DELETE_WINDOW message
        Atom wm_protocols = XInternAtom(display_, "WM_PROTOCOLS", False);
        Atom wm_delete = XInternAtom(display_, "WM_DELETE_WINDOW", False);

        XEvent event;
        memset(&event, 0, sizeof(event));
        event.type = ClientMessage;
        event.xclient.window = xwindow_;
        event.xclient.message_type = wm_protocols;
        event.xclient.format = 32;
        event.xclient.data.l[0] = wm_delete;
        event.xclient.data.l[1] = CurrentTime;

        XSendEvent(display_, xwindow_, False, NoEventMask, &event);
        XFlush(display_);
    } else {
        // Force kill
        kill();
    }
}

void Window::kill() {
    XKillClient(display_, xwindow_);
}

void Window::update_title() {
    // Try _NET_WM_NAME first (UTF-8)
    Atom net_wm_name = XInternAtom(display_, "_NET_WM_NAME", False);
    Atom utf8_string = XInternAtom(display_, "UTF8_STRING", False);

    Atom actual_type;
    int actual_format;
    unsigned long nitems, bytes_after;
    unsigned char* prop = nullptr;

    if (XGetWindowProperty(display_, xwindow_, net_wm_name,
            0, 1024, False, utf8_string,
            &actual_type, &actual_format,
            &nitems, &bytes_after, &prop) == Success && prop) {
        title_ = std::string((char*)prop);
        XFree(prop);
        return;
    }

    // Fall back to WM_NAME
    XTextProperty text_prop;
    if (XGetWMName(display_, xwindow_, &text_prop)) {
        if (text_prop.value) {
            title_ = std::string((char*)text_prop.value);
            XFree(text_prop.value);
        }
    } else {
        title_ = "Untitled";
    }
}

void Window::update_class() {
    XClassHint class_hint;
    if (XGetClassHint(display_, xwindow_, &class_hint)) {
        if (class_hint.res_class) {
            class_name_ = std::string(class_hint.res_class);
            XFree(class_hint.res_class);
        }
        if (class_hint.res_name) {
            instance_ = std::string(class_hint.res_name);
            XFree(class_hint.res_name);
        }
    }
}

void Window::update_hints() {
    XWMHints* hints = XGetWMHints(display_, xwindow_);
    if (hints) {
        // Process hints
        XFree(hints);
    }
}

void Window::update_size_hints() {
    XSizeHints hints;
    long supplied;

    if (XGetWMNormalHints(display_, xwindow_, &hints, &supplied)) {
        if (hints.flags & PMinSize) {
            min_width_ = hints.min_width;
            min_height_ = hints.min_height;
        }
        if (hints.flags & PMaxSize) {
            max_width_ = hints.max_width;
            max_height_ = hints.max_height;
        }
        if (hints.flags & PBaseSize) {
            base_width_ = hints.base_width;
            base_height_ = hints.base_height;
        }
        if (hints.flags & PResizeInc) {
            width_inc_ = hints.width_inc;
            height_inc_ = hints.height_inc;
        }
        if (hints.flags & PAspect) {
            min_aspect_ = (float)hints.min_aspect.x / hints.min_aspect.y;
            max_aspect_ = (float)hints.max_aspect.x / hints.max_aspect.y;
        }
    }
}

void Window::update_protocols() {
    Atom* protocols = nullptr;
    int count = 0;

    Atom wm_protocols = XInternAtom(display_, "WM_PROTOCOLS", False);

    if (XGetWMProtocols(display_, xwindow_, &protocols, &count)) {
        Atom wm_delete = XInternAtom(display_, "WM_DELETE_WINDOW", False);
        Atom wm_take_focus = XInternAtom(display_, "WM_TAKE_FOCUS", False);

        for (int i = 0; i < count; ++i) {
            if (protocols[i] == wm_delete) {
                supports_delete_ = true;
            }
            if (protocols[i] == wm_take_focus) {
                supports_focus_ = true;
            }
        }

        XFree(protocols);
    }
}

void Window::update_state() {
    // TODO: Read _NET_WM_STATE property
}

void Window::update_type() {
    Atom net_wm_window_type = XInternAtom(display_, "_NET_WM_WINDOW_TYPE", False);

    Atom actual_type;
    int actual_format;
    unsigned long nitems, bytes_after;
    unsigned char* prop = nullptr;

    if (XGetWindowProperty(display_, xwindow_, net_wm_window_type,
            0, 1, False, XA_ATOM,
            &actual_type, &actual_format,
            &nitems, &bytes_after, &prop) == Success && prop) {

        Atom window_type = *(Atom*)prop;

        Atom type_desktop = XInternAtom(display_, "_NET_WM_WINDOW_TYPE_DESKTOP", False);
        Atom type_dock = XInternAtom(display_, "_NET_WM_WINDOW_TYPE_DOCK", False);
        Atom type_toolbar = XInternAtom(display_, "_NET_WM_WINDOW_TYPE_TOOLBAR", False);
        Atom type_menu = XInternAtom(display_, "_NET_WM_WINDOW_TYPE_MENU", False);
        Atom type_utility = XInternAtom(display_, "_NET_WM_WINDOW_TYPE_UTILITY", False);
        Atom type_splash = XInternAtom(display_, "_NET_WM_WINDOW_TYPE_SPLASH", False);
        Atom type_dialog = XInternAtom(display_, "_NET_WM_WINDOW_TYPE_DIALOG", False);

        if (window_type == type_desktop) {
            type_ = Type::DESKTOP;
        } else if (window_type == type_dock) {
            type_ = Type::DOCK;
        } else if (window_type == type_toolbar) {
            type_ = Type::TOOLBAR;
        } else if (window_type == type_menu) {
            type_ = Type::MENU;
        } else if (window_type == type_utility) {
            type_ = Type::UTILITY;
        } else if (window_type == type_splash) {
            type_ = Type::SPLASH;
        } else if (window_type == type_dialog) {
            type_ = Type::DIALOG;
        }

        XFree(prop);
    }
}

void Window::apply_size_hints(int& width, int& height) {
    // Apply minimum size
    if (width < min_width_) {
        width = min_width_;
    }
    if (height < min_height_) {
        height = min_height_;
    }

    // Apply maximum size
    if (width > max_width_) {
        width = max_width_;
    }
    if (height > max_height_) {
        height = max_height_;
    }

    // Apply size increments
    if (width_inc_ > 1) {
        width = base_width_ + ((width - base_width_) / width_inc_) * width_inc_;
    }
    if (height_inc_ > 1) {
        height = base_height_ + ((height - base_height_) / height_inc_) * height_inc_;
    }
}

void Window::send_configure_notify() {
    XConfigureEvent ce;
    ce.type = ConfigureNotify;
    ce.display = display_;
    ce.event = xwindow_;
    ce.window = xwindow_;
    ce.x = x_;
    ce.y = y_;
    ce.width = width_;
    ce.height = height_;
    ce.border_width = 0;
    ce.above = None;
    ce.override_redirect = False;

    XSendEvent(display_, xwindow_, False, StructureNotifyMask, (XEvent*)&ce);
}

} // namespace MalgoroDE
