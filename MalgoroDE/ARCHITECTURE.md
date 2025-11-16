# MalgoroDE Architecture

**Enterprise-Grade Desktop Environment with Classic 2000s Aesthetic**

## Design Philosophy

MalgoroDE combines the elegance and simplicity of early 2000s desktop environments (like Windows XP, GNOME 2, KDE 3) with modern robustness and enterprise features. It's designed for traditional desktop computers with larger screens, emphasizing:

- **Classic Aesthetic**: Clean, functional, familiar design
- **Performance**: Lightweight and responsive
- **Stability**: Enterprise-grade reliability
- **Customization**: Flexible theming and configuration
- **Workflow**: Optimized for productivity

## Technology Stack

- **Display Server**: X11 (primary), Wayland (future)
- **Toolkit**: GTK3 (with GTK4 migration path)
- **Window Manager**: Custom lightweight WM based on libwnck
- **Compositor**: Built-in Xcompmgr/Picom integration
- **Language**: C++20 (core) + C (X11 bindings)
- **Configuration**: INI-based files
- **IPC**: D-Bus for inter-component communication

## Component Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                     MalgoroDE Session                       │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐    │
│  │    Window    │  │    Panel     │  │  Launcher    │    │
│  │   Manager    │  │   Service    │  │   Service    │    │
│  │  (MalgoroWM) │  │(MalgoroPanel)│  │(MalgoroMenu) │    │
│  └──────────────┘  └──────────────┘  └──────────────┘    │
│                                                             │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐    │
│  │   Settings   │  │    Theme     │  │   Widgets    │    │
│  │   Manager    │  │   Manager    │  │   Library    │    │
│  └──────────────┘  └──────────────┘  └──────────────┘    │
│                                                             │
├─────────────────────────────────────────────────────────────┤
│                      D-Bus Message Bus                      │
├─────────────────────────────────────────────────────────────┤
│                    X11 Display Server                       │
└─────────────────────────────────────────────────────────────┘
```

## Core Components

### 1. MalgoroWM - Window Manager

**Purpose**: Manages application windows, workspaces, and window decorations

**Features**:
- Window decorations with classic titlebar design
- Multi-workspace support (virtual desktops)
- Window snapping and tiling options
- Keyboard shortcuts
- Window rules and placement
- Focus management (click-to-focus, focus-follows-mouse)
- Window animations (subtle, classic)

**Key Files**:
- `src/wm/WindowManager.cpp/h` - Core WM logic
- `src/wm/Window.cpp/h` - Window abstraction
- `src/wm/Workspace.cpp/h` - Virtual desktop management
- `src/wm/Decorator.cpp/h` - Window decorations
- `src/wm/KeyBindings.cpp/h` - Keyboard shortcut handling

**Design**:
```
Window Decoration:
┌─────────────────────────────────────────────────┐
│ [Icon] Application Title            [_][□][X]  │ ← Titlebar
├─────────────────────────────────────────────────┤
│                                                 │
│                                                 │
│           Application Content Area              │
│                                                 │
│                                                 │
└─────────────────────────────────────────────────┘
```

### 2. MalgoroPanel - Desktop Panel/Taskbar

**Purpose**: Primary user interface for launching apps, switching windows, system status

**Features**:
- Application launcher button (start menu)
- Window list with grouping
- System tray (notification area)
- Clock and calendar
- Volume control
- Network indicator
- Battery indicator (laptops)
- Workspace switcher
- Quick launch area
- User menu (logout, shutdown, etc.)

**Layout** (Classic Bottom Panel):
```
┌──────────────────────────────────────────────────────────────────┐
│ [M] [App1] [App2] [App3]...  [Tray] [Vol] [Net] [12:34 PM] [▼] │
└──────────────────────────────────────────────────────────────────┘
 └┬┘ └────────┬────────────┘   └────────┬────────┘ └───┬───┘ └┬┘
  │          │                          │               │       │
Start    Window List            System Tray          Clock   User
Menu                                                           Menu
```

**Key Files**:
- `src/panel/Panel.cpp/h` - Main panel container
- `src/panel/AppletManager.cpp/h` - Manages panel applets
- `src/panel/WindowList.cpp/h` - Window list widget
- `src/panel/SystemTray.cpp/h` - System tray implementation
- `src/panel/Clock.cpp/h` - Clock widget
- `src/panel/VolumeControl.cpp/h` - Volume widget
- `src/panel/NetworkMonitor.cpp/h` - Network widget

### 3. MalgoroMenu - Application Launcher

**Purpose**: Categorized application menu with search

**Features**:
- Hierarchical application categories
- Search/filter functionality
- Recently used applications
- Favorites/pinned applications
- "All Applications" view
- Run command dialog
- Classic cascading menu option

**Design** (Windows XP / GNOME 2 inspired):
```
┌────────────────────────────────────┐
│  Search: [____________]        [x] │
├────────────────────────────────────┤
│ ★ Favorites                        │
│   Firefox                          │
│   Terminal                         │
│   Files                            │
├────────────────────────────────────┤
│ ▸ Accessories                      │
│ ▸ Graphics                         │
│ ▸ Internet                         │
│ ▸ Office                           │
│ ▸ Sound & Video                    │
│ ▸ System Tools                     │
├────────────────────────────────────┤
│ All Applications            ▸      │
├────────────────────────────────────┤
│ Settings      │ Power      │ Help  │
└────────────────────────────────────┘
```

**Key Files**:
- `src/launcher/Menu.cpp/h` - Main menu window
- `src/launcher/AppDatabase.cpp/h` - Application discovery
- `src/launcher/CategoryView.cpp/h` - Category navigation
- `src/launcher/SearchEngine.cpp/h` - Search functionality

### 4. MalgoroSettings - Settings Manager

**Purpose**: System configuration and preferences

**Settings Categories**:
- **Appearance**: Themes, fonts, colors, icons
- **Desktop**: Wallpaper, screen saver, effects
- **Windows**: Window behavior, shortcuts, workspaces
- **Panel**: Panel configuration, applets
- **Display**: Resolution, orientation, multiple monitors
- **Keyboard**: Layouts, shortcuts, typing
- **Mouse**: Pointer speed, buttons, scrolling
- **Sound**: Volume, devices, effects
- **Power**: Sleep, brightness, battery
- **Network**: WiFi, Ethernet, VPN
- **Peripherals**: Printers, Bluetooth, USB

**Key Files**:
- `src/settings/SettingsManager.cpp/h` - Main settings backend
- `src/settings/SettingsUI.cpp/h` - Settings GUI
- `src/settings/DisplaySettings.cpp/h` - Display configuration
- `src/settings/ThemeSettings.cpp/h` - Theme management

### 5. MalgoroTheme - Theme System

**Purpose**: Unified theming across desktop components

**Theme Components**:
- **GTK Theme**: Widget styling (buttons, menus, etc.)
- **Window Decorations**: Titlebar, borders, buttons
- **Icon Theme**: Application and system icons
- **Cursor Theme**: Mouse pointer
- **Color Scheme**: System-wide colors
- **Sounds**: System sound effects
- **Fonts**: System fonts and sizes

**Classic Themes Included**:
- **Malgoro Classic** - Default Windows XP inspired
- **Malgoro Luna** - Blue, clean, professional
- **Malgoro Royale** - Deep blue, elegant
- **Malgoro Olive** - Green, calm
- **Malgoro Silver** - Gray, minimal

**Key Files**:
- `src/themes/ThemeManager.cpp/h` - Theme loading and switching
- `src/themes/GTKTheme.cpp/h` - GTK theme integration
- `src/themes/IconTheme.cpp/h` - Icon theme handling
- `data/themes/` - Theme data files

### 6. MalgoroWidgets - Custom Widget Library

**Purpose**: Reusable UI components with classic styling

**Widgets**:
- **ClassicButton** - Raised 3D button
- **ClassicWindow** - Window with classic frame
- **ClassicMenu** - Traditional cascading menu
- **ClassicToolbar** - Toolbar with classic buttons
- **ClassicScrollbar** - Classic scrollbar style
- **ClassicProgressBar** - Classic progress indicator
- **ClassicDialog** - System dialog boxes
- **ClassicListView** - File manager style list
- **ClassicTreeView** - Hierarchical tree view

**Key Files**:
- `src/widgets/ClassicButton.cpp/h`
- `src/widgets/ClassicWindow.cpp/h`
- `src/widgets/ClassicMenu.cpp/h`
- etc.

## Session Management

### MalgoroSession

**Purpose**: Manages desktop session lifecycle

**Responsibilities**:
- Start/stop desktop components
- Session saving/restoration
- Autostart applications
- Session lockdown
- Logout/shutdown handling

**Startup Sequence**:
1. X11 server initialization
2. D-Bus session bus start
3. Settings daemon start
4. Theme manager initialization
5. Window manager launch
6. Panel launch
7. Compositor start
8. Autostart applications
9. Session ready signal

**Key Files**:
- `src/session/SessionManager.cpp/h`
- `src/session/Autostart.cpp/h`

## Configuration System

### Configuration Files

**Location**: `~/.config/malgoro/`

```
~/.config/malgoro/
├── desktop.conf          # Desktop settings
├── panel.conf            # Panel configuration
├── wm.conf              # Window manager settings
├── theme.conf           # Theme settings
├── keybindings.conf     # Keyboard shortcuts
├── autostart/           # Autostart applications
│   ├── app1.desktop
│   └── app2.desktop
└── session/             # Session data
    └── session.conf
```

### Configuration Format (INI-style)

```ini
[Desktop]
wallpaper = /usr/share/backgrounds/malgoro/default.jpg
show_desktop_icons = true
icon_size = 48

[Panel]
position = bottom
height = 32
autohide = false

[WindowManager]
theme = Malgoro Classic
focus_mode = click
num_workspaces = 4
enable_animations = true

[Theme]
gtk_theme = Malgoro-Classic
icon_theme = Malgoro-Icons
cursor_theme = Malgoro-Cursors
font_name = Sans 10
```

## D-Bus Interfaces

### org.malgoro.WindowManager

```xml
<interface name="org.malgoro.WindowManager">
    <method name="ShowDesktop"/>
    <method name="MinimizeAll"/>
    <method name="SwitchWorkspace">
        <arg type="i" direction="in" name="workspace"/>
    </method>
    <signal name="WindowOpened">
        <arg type="s" name="window_id"/>
    </signal>
</interface>
```

### org.malgoro.Panel

```xml
<interface name="org.malgoro.Panel">
    <method name="ShowMenu"/>
    <method name="ToggleHide"/>
    <property name="Height" type="i" access="readwrite"/>
</interface>
```

### org.malgoro.ThemeManager

```xml
<interface name="org.malgoro.ThemeManager">
    <method name="SetTheme">
        <arg type="s" direction="in" name="theme_name"/>
    </method>
    <signal name="ThemeChanged">
        <arg type="s" name="theme_name"/>
    </signal>
</interface>
```

## File Manager (Future Component)

**MalgoroFiles** - Classic file manager

Features:
- Dual-pane option
- Tree view sidebar
- Icon, list, and details views
- Thumbnail generation
- File operations (copy, move, delete)
- Archive support
- Network locations
- Search functionality

## System Integration

### Display Manager Integration

MalgoroDE provides a session file for display managers:

```desktop
[Desktop Entry]
Name=Malgoro Desktop
Comment=Classic desktop environment
Exec=malgoro-session
Type=Application
```

### XDG Compliance

- Follows XDG Base Directory Specification
- Desktop Entry support
- Icon theme specification
- Menu specification

## Performance Targets

- **Memory**: < 200MB base system
- **CPU**: < 5% idle
- **Startup**: < 3 seconds to usable desktop
- **Window Draw**: < 16ms (60 FPS)
- **Panel Response**: < 50ms

## Accessibility Features

- High contrast themes
- Keyboard navigation
- Screen reader support (AT-SPI)
- Large fonts option
- Configurable DPI

## Visual Design Guidelines

### Color Palette (Malgoro Classic)

```
Primary:   #0078D7 (Blue)
Secondary: #005A9E (Dark Blue)
Accent:    #FFB900 (Gold)
Text:      #000000 (Black)
BG Light:  #F0F0F0 (Light Gray)
BG Dark:   #E0E0E0 (Gray)
Border:    #ACACAC (Medium Gray)
```

### Typography

- **System Font**: Sans (DejaVu Sans)
- **Monospace**: Monospace (DejaVu Sans Mono)
- **Title**: Bold 11pt
- **Body**: Regular 10pt
- **Small**: Regular 9pt

### Window Decorations

```
Titlebar Height: 24px
Border Width: 1px
Button Size: 18x18px
Corner Radius: 0px (sharp corners for classic look)

Button Colors:
- Close: #E81123 (Red)
- Maximize: #FFB900 (Yellow)
- Minimize: #00CC6A (Green)
```

### Spacing

- **Padding**: 4px (tight), 8px (normal), 12px (loose)
- **Margins**: 8px (elements), 16px (sections)
- **Grid**: 8px base unit

## Build System

### CMake Structure

```cmake
MalgoroDE/
├── CMakeLists.txt          # Main build file
├── src/
│   ├── wm/CMakeLists.txt
│   ├── panel/CMakeLists.txt
│   ├── launcher/CMakeLists.txt
│   ├── settings/CMakeLists.txt
│   └── themes/CMakeLists.txt
└── data/CMakeLists.txt
```

### Build Targets

- `malgoro-wm` - Window manager
- `malgoro-panel` - Panel
- `malgoro-menu` - Application menu
- `malgoro-settings` - Settings manager
- `malgoro-session` - Session manager
- `libmalgoro-widgets` - Widget library

## Testing Strategy

- **Unit Tests**: Core functionality
- **Integration Tests**: Component interaction
- **UI Tests**: User interface
- **Performance Tests**: Resource usage
- **Stress Tests**: Stability under load

## Extensibility

### Plugin System (Future)

- Panel applets
- Window manager effects
- Settings panels
- Theme engines
- File manager extensions

### API

- C++ API for extensions
- D-Bus API for external apps
- Theme API for custom themes

## Internationalization

- gettext for translations
- RTL language support
- Locale-aware formatting
- Translatable UI strings

## Documentation

- User manual
- Administrator guide
- Developer API docs
- Theme creation guide
- Keyboard shortcuts reference

## Comparison with Other DEs

| Feature | MalgoroDE | GNOME 2 | XFCE | MATE | Budgie |
|---------|-----------|---------|------|------|--------|
| Memory | ~200MB | ~180MB | ~150MB | ~200MB | ~350MB |
| Classic Look | ✓ | ✓ | ✓ | ✓ | ~ |
| Modern Code | ✓ | ✗ | ~ | ~ | ✓ |
| Wayland | Future | ✗ | Future | ✗ | ✓ |
| Customizable | ✓✓ | ✓ | ✓✓ | ✓ | ~ |

## Roadmap

**Phase 1 (Months 1-2)**: Core Components
- Window manager
- Basic panel
- Simple launcher

**Phase 2 (Months 2-3)**: Refinement
- Theme system
- Settings manager
- Polish UI

**Phase 3 (Months 3-4)**: Features
- File manager
- Advanced widgets
- Animations

**Phase 4 (Months 4-6)**: Release
- Documentation
- Testing
- Package creation
- Beta release

## References

- X11 Protocol: https://www.x.org/
- GTK Documentation: https://docs.gtk.org/
- Freedesktop Standards: https://www.freedesktop.org/
- Window Manager Specification: ICCCM, EWMH
