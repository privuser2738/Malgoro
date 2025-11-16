# MalgoroPkg Repository Examples

Complete examples of repository structures for different use cases.

## Example 1: malgoro-core (Desktop Components)

**Repository**: https://github.com/privuser2738/malgoro-core
**Contains**: 5 desktop environment packages

```
malgoro-core/
├── README.md
├── LICENSE (GPL-3.0)
├── .gitignore
├── CMakeLists.txt              # Optional: shared build system
├── common/                     # Shared resources
│   ├── include/
│   │   └── malgoro-common.h
│   └── data/
│       └── malgoro-logo.svg
└── packages/
    ├── malgoro-wm/
    │   ├── PKGINFO
    │   ├── README.md
    │   ├── build.sh
    │   ├── src/
    │   │   ├── main.cpp
    │   │   ├── WindowManager.cpp
    │   │   └── Window.cpp
    │   └── files/
    │       └── usr/
    │           ├── bin/
    │           │   └── malgoro-wm
    │           └── share/
    │               └── man/
    │                   └── man1/
    │                       └── malgoro-wm.1
    ├── malgoro-panel/
    │   ├── PKGINFO
    │   ├── build.sh
    │   └── src/
    ├── malgoro-menu/
    │   ├── PKGINFO
    │   ├── build.sh
    │   └── src/
    ├── malgoro-settings/
    │   ├── PKGINFO
    │   ├── build.sh
    │   └── src/
    └── malgoro-session/
        ├── PKGINFO
        └── files/
            ├── usr/
            │   └── bin/
            │       └── malgoro-session
            └── usr/share/
                └── xsessions/
                    └── malgoro.desktop
```

### PKGINFO Files

**malgoro-wm/PKGINFO:**
```ini
name=malgoro-wm
version=0.1.0
description=Malgoro window manager with classic look
maintainer=Malgoro Team <team@malgoro.org>
license=GPL-3.0
depends=libx11,libxcomposite,libxdamage,cairo
```

**malgoro-panel/PKGINFO:**
```ini
name=malgoro-panel
version=0.1.0
description=Desktop panel for Malgoro
maintainer=Malgoro Team <team@malgoro.org>
license=GPL-3.0
depends=malgoro-wm,gtk3,libwnck
```

**malgoro-session/PKGINFO:**
```ini
name=malgoro-session
version=0.1.0
description=Session manager for Malgoro Desktop
maintainer=Malgoro Team <team@malgoro.org>
license=GPL-3.0
depends=malgoro-wm,malgoro-panel,malgoro-menu
```

### README.md

```markdown
# Malgoro Core

Core desktop environment components for Malgoro.

## Packages

This repository contains:

- **malgoro-wm** - Window manager (v0.1.0)
- **malgoro-panel** - Desktop panel (v0.1.0)
- **malgoro-menu** - Application menu (v0.1.0)
- **malgoro-settings** - Settings manager (v0.1.0)
- **malgoro-session** - Session manager (v0.1.0)

## Installation

```bash
# Install complete desktop
malgoropkg install malgoro-session

# Or install individual components
malgoropkg install malgoro-wm
malgoropkg install malgoro-panel
```

## Building from Source

```bash
git clone https://github.com/privuser2738/malgoro-core.git
cd malgoro-core
mkdir build && cd build
cmake ..
make
```
```

---

## Example 2: malgoro-themes (Theme Packages)

**Repository**: https://github.com/privuser2738/malgoro-themes
**Contains**: 10 theme packages (GTK, icons, cursors, wallpapers)

```
malgoro-themes/
├── README.md
├── LICENSE
├── .gitignore
├── preview/                    # Theme screenshots
│   ├── classic.png
│   ├── luna.png
│   └── royale.png
└── packages/
    ├── malgoro-classic-theme/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/share/themes/Malgoro-Classic/
    │           ├── index.theme
    │           ├── gtk-3.0/
    │           │   ├── gtk.css
    │           │   └── gtk-dark.css
    │           └── gtk-4.0/
    │               └── gtk.css
    ├── malgoro-luna-theme/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/share/themes/Malgoro-Luna/
    ├── malgoro-royale-theme/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/share/themes/Malgoro-Royale/
    ├── malgoro-olive-theme/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/share/themes/Malgoro-Olive/
    ├── malgoro-silver-theme/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/share/themes/Malgoro-Silver/
    ├── malgoro-icons/
    │   ├── PKGINFO
    │   ├── build.sh           # Generates icons from SVG
    │   ├── src/
    │   │   └── *.svg
    │   └── files/
    │       └── usr/share/icons/Malgoro/
    │           ├── index.theme
    │           ├── 16x16/
    │           ├── 22x22/
    │           ├── 24x24/
    │           ├── 32x32/
    │           ├── 48x48/
    │           └── scalable/
    ├── malgoro-cursors/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/share/icons/Malgoro-Cursors/
    ├── malgoro-wallpapers-classic/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/share/backgrounds/malgoro/
    │           ├── classic-bliss.jpg
    │           ├── classic-hills.jpg
    │           └── classic-sunset.jpg
    ├── malgoro-wallpapers-nature/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/share/backgrounds/malgoro/
    └── malgoro-sounds/
        ├── PKGINFO
        └── files/
            └── usr/share/sounds/malgoro/
                ├── startup.ogg
                ├── shutdown.ogg
                └── notify.ogg
```

### Sample PKGINFO

**malgoro-classic-theme/PKGINFO:**
```ini
name=malgoro-classic-theme
version=1.0.0
description=Classic Windows XP inspired theme for Malgoro
maintainer=Malgoro Team <team@malgoro.org>
license=GPL-3.0
depends=gtk3
provides=malgoro-theme
```

**malgoro-icons/PKGINFO:**
```ini
name=malgoro-icons
version=1.0.0
description=Classic icon theme for Malgoro
maintainer=Malgoro Team <team@malgoro.org>
license=GPL-3.0
depends=hicolor-icon-theme
```

---

## Example 3: malgoro-applications (Small Utilities)

**Repository**: https://github.com/privuser2738/malgoro-applications
**Contains**: 20+ small to medium applications

```
malgoro-applications/
├── README.md
├── LICENSE
└── packages/
    ├── malgoro-terminal/
    │   ├── PKGINFO
    │   ├── build.sh
    │   ├── src/
    │   │   └── main.cpp
    │   └── files/
    │       └── usr/
    │           ├── bin/malgoro-terminal
    │           └── share/applications/malgoro-terminal.desktop
    ├── malgoro-editor/
    │   ├── PKGINFO
    │   ├── build.sh
    │   └── src/
    ├── malgoro-files/
    │   ├── PKGINFO
    │   ├── build.sh
    │   └── src/
    ├── malgoro-calculator/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/
    │           ├── bin/malgoro-calculator
    │           └── share/applications/malgoro-calculator.desktop
    ├── malgoro-screenshot/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/bin/malgoro-screenshot
    ├── malgoro-imageviewer/
    │   ├── PKGINFO
    │   ├── build.sh
    │   └── src/
    ├── malgoro-archiver/
    │   ├── PKGINFO
    │   └── files/
    ├── malgoro-notes/
    │   ├── PKGINFO
    │   └── files/
    ├── malgoro-timer/
    │   ├── PKGINFO
    │   └── files/
    └── malgoro-colorpicker/
        ├── PKGINFO
        └── files/
```

**Note**: This shows a mix of:
- Apps requiring compilation (build.sh + src/)
- Pre-built scripts (just files/)
- Different complexity levels

---

## Example 4: Community Repository

**Repository**: https://github.com/username/my-malgoro-apps
**Contains**: Personal collection of packages

```
my-malgoro-apps/
├── README.md
├── LICENSE
└── packages/
    ├── my-music-player/
    │   ├── PKGINFO
    │   ├── README.md
    │   ├── build.sh
    │   └── src/
    ├── my-game-launcher/
    │   ├── PKGINFO
    │   └── files/
    └── my-backup-tool/
        ├── PKGINFO
        ├── build.sh
        └── src/
```

**PKGINFO Example:**
```ini
name=my-music-player
version=2.3.1
description=Lightweight music player for Malgoro
maintainer=John Doe <john@example.com>
license=MIT
depends=gtk3,gstreamer
```

---

## Example 5: Large Single Package

**Repository**: https://github.com/privuser2738/firefox-malgoro
**Contains**: 1 large package

```
firefox-malgoro/
├── README.md
├── LICENSE
├── PKGINFO
├── build.sh
├── patches/
│   ├── malgoro-integration.patch
│   └── theme-support.patch
├── src/
│   └── (extracted Firefox source)
└── files/
    └── usr/
        ├── bin/firefox-malgoro
        ├── lib/firefox-malgoro/
        └── share/
            ├── applications/firefox-malgoro.desktop
            └── icons/
```

**PKGINFO:**
```ini
name=firefox-malgoro
version=120.0
description=Firefox web browser integrated with Malgoro
maintainer=Malgoro Team <team@malgoro.org>
license=MPL-2.0
depends=gtk3,dbus-glib,nss
conflicts=firefox
provides=web-browser
```

---

## Example 6: Development Tools Collection

**Repository**: https://github.com/devtools/malgoro-dev
**Contains**: Development tools and libraries

```
malgoro-dev/
├── README.md
└── packages/
    ├── malgoro-dev-base/
    │   ├── PKGINFO
    │   └── files/
    │       └── (base development tools)
    ├── malgoro-debugger/
    │   ├── PKGINFO
    │   ├── build.sh
    │   └── src/
    ├── malgoro-profiler/
    │   ├── PKGINFO
    │   └── src/
    ├── libmalgoro-dev/
    │   ├── PKGINFO
    │   ├── build.sh
    │   └── src/
    │       ├── include/
    │       └── lib/
    └── malgoro-sdk/
        ├── PKGINFO
        └── files/
            └── usr/
                ├── include/malgoro/
                ├── lib/pkgconfig/
                └── share/doc/malgoro-sdk/
```

---

## Shared Build Scripts

Many packages in a repository can share build scripts:

**scripts/common.sh:**
```bash
#!/bin/bash
# Common build functions

build_with_cmake() {
    mkdir -p build
    cd build
    cmake .. -DCMAKE_INSTALL_PREFIX=/usr
    make -j$(nproc)
    cd ..
}

build_with_meson() {
    meson setup build --prefix=/usr
    ninja -C build
}

install_files() {
    cp -r files/* "$DESTDIR/"
}
```

**Package build.sh:**
```bash
#!/bin/bash
source ../scripts/common.sh

build_with_cmake
install_files
```

---

## Best Practices Summary

### Multi-Package Repositories Should:

✅ Group 5-20 related packages
✅ Keep individual packages < 10MB
✅ Share common resources in root
✅ Document all packages in README
✅ Use consistent PKGINFO format

### File Organization:

```
repo/
├── README.md           # List all packages
├── LICENSE            # Shared license
├── .gitignore         # Common ignores
├── scripts/           # Shared build scripts
│   └── common.sh
├── common/            # Shared resources
│   ├── include/
│   └── data/
└── packages/          # Individual packages
    ├── pkg1/
    │   ├── PKGINFO    # Required
    │   ├── build.sh   # If needs building
    │   ├── src/       # Source code
    │   └── files/     # Installed files
    └── pkg2/
```

### Repository Sizes:

- **Tiny** (< 1MB): 20-50 packages per repo
- **Small** (1-10MB): 10-20 packages per repo
- **Medium** (10-50MB): 3-5 packages per repo
- **Large** (> 50MB): 1 package per repo

---

## Adding Packages to Multi-Package Repository

### Quick Steps:

```bash
# 1. Clone repository
git clone https://github.com/user/repo.git
cd repo

# 2. Create new package directory
mkdir -p packages/my-new-app

# 3. Create PKGINFO
cat > packages/my-new-app/PKGINFO << EOF
name=my-new-app
version=1.0.0
description=My new application
maintainer=Me <me@example.com>
license=MIT
EOF

# 4. Add files
mkdir -p packages/my-new-app/files/usr/bin
echo "#!/bin/bash" > packages/my-new-app/files/usr/bin/my-app
chmod +x packages/my-new-app/files/usr/bin/my-app

# 5. Commit and push
git add packages/my-new-app
git commit -m "Add my-new-app package"
git push
```

Users will automatically see the new package after `malgoropkg sync`!

---

## Summary

**Key Points:**

1. **One repository = Many packages** (for small/related packages)
2. **Automatic discovery** by MalgoroPkg
3. **Shared resources** reduce duplication
4. **Easy maintenance** - related packages together
5. **Flexible structure** - adapt to your needs

**Recommended Approach:**

- Official repos: 10-20 packages each (by category)
- Community repos: 5-10 packages (by maintainer)
- Large apps: Individual repositories

This approach balances **efficiency**, **maintainability**, and **discoverability**!
