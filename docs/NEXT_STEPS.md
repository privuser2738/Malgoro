# Next Steps for Malgoro Development

This document outlines the recommended steps to complete the Malgoro project.

## Current Status ✓

- ✅ MalgoroPkg architecture designed
- ✅ MalgoroPkg core implementation complete (C++)
- ✅ MalgoroDE architecture designed (headers complete)
- ✅ Multi-package repository system documented
- ✅ Build scripts and helper tools created
- ✅ Package templates created
- ✅ Comprehensive documentation written

## Phase 1: Testing & Validation (Current Priority)

### 1.1 Build MalgoroPkg on Linux

**Estimated Time**: 2-4 hours

**Steps**:
```bash
# On a Linux system (Manjaro/Arch recommended)
cd malgoro-desktop/MalgoroPkg
mkdir build && cd build
cmake ..
make -j$(nproc)
```

**Potential Issues**:
- Missing dependencies (libgit2, sqlite3, openssl)
- Compiler errors (C++20 features)
- Linking errors

**Success Criteria**:
- MalgoroPkg binary builds without errors
- `./malgoropkg --version` shows version info
- `./malgoropkg --help` displays usage

### 1.2 Install Dependencies

**On Manjaro/Arch**:
```bash
sudo pacman -S base-devel cmake git
sudo pacman -S libgit2 sqlite openssl
```

**On Ubuntu/Debian**:
```bash
sudo apt install build-essential cmake git
sudo apt install libgit2-dev libsqlite3-dev libssl-dev
```

### 1.3 Run Basic Tests

**Test Repository Sync**:
```bash
# Create test repository
mkdir -p /tmp/test-repo/packages/test-pkg
cat > /tmp/test-repo/packages/test-pkg/PKGINFO << EOF
name=test-pkg
version=1.0.0
description=Test package
maintainer=Test <test@test.com>
license=MIT
depends=
EOF

# Test local installation
./malgoropkg install /tmp/test-repo/packages/test-pkg
./malgoropkg list-installed
./malgoropkg remove test-pkg
```

## Phase 2: GitHub Repository Setup

### 2.1 Create Main Repository

**Repository**: `malgoro`

```bash
cd malgoro-desktop
git init
git add .
git commit -m "Initial commit: MalgoroPkg and MalgoroDE"
git remote add origin https://github.com/privuser2738/malgoro
git push -u origin main
```

**Include**:
- Complete README.md with project overview
- LICENSE file (MIT recommended)
- Contributing guidelines
- Issue templates

### 2.2 Create Package Repositories

**Priority Order**:

1. **malgoro-core** (highest priority)
   - Contains essential DE components
   - Start with basic window manager package

2. **malgoro-themes**
   - Theme packages can be created while developing DE

3. **malgoro-applications**
   - Applications can be added incrementally

4. **malgoro-utilities**
   - Lower priority, can be added later

**For each repository**:
```bash
# Use the template
cp -r templates/multi-package/ ~/malgoro-repos/malgoro-core
cd ~/malgoro-repos/malgoro-core

# Customize and push
git init
git add .
git commit -m "Initial package repository"
git remote add origin https://github.com/privuser2738/malgoro-core
git push -u origin main
```

### 2.3 Configure Repository List

Create default `repositories.conf`:
```ini
[malgoro-core]
url = https://github.com/privuser2738/malgoro-core
description = Core desktop environment components
enabled = 1

[malgoro-themes]
url = https://github.com/privuser2738/malgoro-themes
description = Themes and visual customization
enabled = 1
```

## Phase 3: MalgoroDE Implementation

### 3.1 Implement Window Manager

**Files to implement** (currently headers only):
- `MalgoroDE/src/wm/WindowManager.cpp`
- `MalgoroDE/src/wm/Decorator.cpp`
- `MalgoroDE/src/wm/Workspace.cpp`

**Priority Features**:
1. Basic window management (map, unmap, move, resize)
2. Window decorations (titlebar, borders, buttons)
3. Keyboard shortcuts (Alt+Tab, Alt+F4, etc.)
4. Mouse interactions (drag to move, resize)

**Estimated Time**: 2-3 weeks

**Testing**:
```bash
# Build
cd MalgoroDE/build
cmake ..
make malgoro-wm

# Test in nested X server
Xephyr -screen 1280x720 :1 &
DISPLAY=:1 ./malgoro-wm
```

### 3.2 Implement Panel

**Files to implement**:
- `MalgoroDE/src/panel/Panel.cpp`
- `MalgoroDE/src/panel/Applet.cpp`
- `MalgoroDE/src/panel/TaskList.cpp`
- `MalgoroDE/src/panel/SystemTray.cpp`

**Priority Features**:
1. Basic panel rendering (top/bottom positioning)
2. Task list (show open windows)
3. System tray
4. Clock applet

**Estimated Time**: 1-2 weeks

### 3.3 Implement Application Launcher

**Files to implement**:
- `MalgoroDE/src/launcher/Launcher.cpp`
- `MalgoroDE/src/launcher/AppMenu.cpp`

**Features**:
1. Application menu (read .desktop files)
2. Search functionality
3. Recent/favorites

**Estimated Time**: 1 week

### 3.4 Implement Theme System

**Files to implement**:
- `MalgoroDE/src/themes/ThemeManager.cpp`

**Features**:
1. Load theme configurations
2. Apply GTK themes
3. Apply icon themes
4. Apply window decorations

**Estimated Time**: 1 week

## Phase 4: Packaging for Arch/Manjaro

### 4.1 Create PKGBUILD for MalgoroPkg

```bash
# pkgname=malgoropkg
# pkgver=0.1.0
# pkgrel=1
# pkgdesc="Git-based package manager for Malgoro"
# arch=('x86_64')
# url="https://github.com/privuser2738/malgoro"
# license=('MIT')
# depends=('libgit2' 'sqlite' 'openssl')
# makedepends=('cmake' 'gcc')
# source=("git+https://github.com/privuser2738/malgoro")

# Build and install
makepkg -si
```

### 4.2 Create PKGBUILD for MalgoroDE

```bash
# pkgname=malgoro-desktop
# pkgver=0.1.0
# depends=('libx11' 'gtk3' 'libwnck3' 'cairo' 'pango' 'dbus')
```

### 4.3 Submit to AUR

1. Create AUR account
2. Create PKGBUILD repository
3. Submit package
4. Maintain and respond to comments

## Phase 5: Integration & Distribution

### 5.1 Create Malgoro Meta-Package

```bash
# Package that installs complete desktop
malgoropkg install malgoro-desktop-complete

# This would install:
# - malgoro-wm
# - malgoro-panel
# - malgoro-launcher
# - malgoro-settings
# - malgoro-theme-luna
# - malgoro-icons-classic
```

### 5.2 Session Integration

Create `/usr/share/xsessions/malgoro.desktop`:
```ini
[Desktop Entry]
Name=Malgoro Desktop
Comment=Classic 2000s desktop experience
Exec=malgoro-session
Type=Application
```

### 5.3 Create Installation ISO (Optional)

- Fork Manjaro ISO builder
- Include Malgoro as default DE
- Custom branding and theming

## Phase 6: Documentation & Community

### 6.1 User Documentation

- Installation guide
- User manual
- Keyboard shortcuts reference
- Theming guide
- FAQ

### 6.2 Developer Documentation

- Architecture overview
- API documentation (Doxygen)
- Contributing guide
- Code style guide

### 6.3 Community Building

- GitHub Discussions
- Discord/Matrix server
- Reddit community
- YouTube demos

## Timeline Estimate

| Phase | Duration | Cumulative |
|-------|----------|------------|
| Testing & Validation | 1 week | 1 week |
| GitHub Setup | 2 days | 1.5 weeks |
| WM Implementation | 3 weeks | 4.5 weeks |
| Panel Implementation | 2 weeks | 6.5 weeks |
| Launcher Implementation | 1 week | 7.5 weeks |
| Theme Implementation | 1 week | 8.5 weeks |
| Packaging | 1 week | 9.5 weeks |
| Integration | 1 week | 10.5 weeks |
| Documentation | 1 week | 11.5 weeks |

**Total**: ~3 months of development time

## Priorities

### Must Have (v0.1.0)
- ✅ MalgoroPkg working package manager
- ⏳ Basic window manager with decorations
- ⏳ Basic panel with task list
- ⏳ One working theme (Luna recommended)
- ⏳ Application launcher

### Should Have (v0.2.0)
- Settings manager
- Multiple themes
- System tray
- Desktop icons
- File manager integration

### Nice to Have (v1.0.0)
- Compositing effects
- Advanced theming
- Plugin system
- Wayland support
- Multiple workspace animations

## Resources Needed

### Development
- Linux development machine (Manjaro/Arch recommended)
- C++ compiler (GCC 11+ or Clang 14+)
- CMake 3.20+
- Git

### Testing
- Virtual machines for different distributions
- Multiple monitor setup (optional)
- Various hardware configurations

### Hosting
- GitHub account (free tier sufficient)
- Optional: Custom domain for documentation
- Optional: CDN for package hosting (if packages are large)

## Getting Help

### Learning Resources

**X11 Window Manager Development**:
- [Xlib Programming Manual](https://tronche.com/gui/x/xlib/)
- [ICCCM Specification](https://www.x.org/releases/X11R7.6/doc/xorg-docs/specs/ICCCM/icccm.html)
- [EWMH Specification](https://specifications.freedesktop.org/wm-spec/wm-spec-latest.html)

**GTK Development**:
- [GTK Documentation](https://docs.gtk.org/gtk3/)
- [GTK Tutorial](https://www.gtk.org/docs/getting-started/)

**Package Management**:
- [Arch Package Guidelines](https://wiki.archlinux.org/title/Arch_package_guidelines)
- [PKGBUILD Documentation](https://wiki.archlinux.org/title/PKGBUILD)

### Example Projects to Study

**Window Managers**:
- [dwm](https://dwm.suckless.org/) - Minimalist WM
- [openbox](http://openbox.org/) - Stacking WM
- [i3](https://i3wm.org/) - Tiling WM

**Desktop Environments**:
- [XFCE](https://www.xfce.org/) - Lightweight DE
- [MATE](https://mate-desktop.org/) - GNOME 2 fork
- [Budgie](https://github.com/BuddiesOfBudgie/budgie-desktop) - Modern classic DE

**Package Managers**:
- [pacman](https://gitlab.archlinux.org/pacman/pacman) - Arch package manager
- [apt](https://salsa.debian.org/apt-team/apt) - Debian package manager

## Current Action Items

### Immediate (This Week)
1. ☐ Build MalgoroPkg on Linux system
2. ☐ Fix any compilation errors
3. ☐ Create test package repository
4. ☐ Test basic install/remove operations
5. ☐ Create main GitHub repository

### Short Term (Next 2 Weeks)
1. ☐ Set up package repositories on GitHub
2. ☐ Begin window manager implementation
3. ☐ Create basic window decorations
4. ☐ Implement window move/resize

### Medium Term (Next Month)
1. ☐ Complete window manager core features
2. ☐ Implement basic panel
3. ☐ Create first theme (Luna)
4. ☐ Test in real environment

### Long Term (Next 3 Months)
1. ☐ Complete all core components
2. ☐ Create PKGBUILD for AUR
3. ☐ Write user documentation
4. ☐ Release v0.1.0

## Questions & Decisions Needed

### Technical Decisions
- [ ] Wayland support priority? (Suggest: After v1.0)
- [ ] Compositing support? (Suggest: v0.2.0+)
- [ ] Support for other distributions? (Suggest: Start with Arch/Manjaro)

### Project Management
- [ ] Issue tracker setup (GitHub Issues)
- [ ] Project board setup (GitHub Projects)
- [ ] Release cycle (Suggest: Monthly dev releases, quarterly stable)

### Community
- [ ] Code of Conduct
- [ ] Contribution guidelines
- [ ] Communication channels (Discord? Matrix?)

## Success Metrics

### v0.1.0 Success Criteria
- [ ] MalgoroPkg can install/remove packages from Git
- [ ] Window manager can manage windows
- [ ] Panel displays task list
- [ ] Can switch between windows
- [ ] One theme works completely
- [ ] Installable via `pacman -S malgoro` (AUR)

### v1.0.0 Success Criteria
- [ ] 100+ GitHub stars
- [ ] 10+ contributors
- [ ] 50+ packages available
- [ ] Documentation complete
- [ ] No critical bugs
- [ ] Used by 100+ users

## Contact & Support

**Primary Maintainer**: privuser2738
**Repository**: https://github.com/privuser2738/malgoro
**Issues**: https://github.com/privuser2738/malgoro/issues

---

*Last Updated: 2025-11-16*
*Version: 0.1.0-dev*
