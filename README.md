# Malgoro Desktop Environment

> A classic 2000s-inspired desktop environment for Linux with enterprise-grade quality

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: Linux](https://img.shields.io/badge/Platform-Linux-blue.svg)](https://www.linux.org/)
[![Status: Development](https://img.shields.io/badge/Status-Development-orange.svg)](https://github.com/privuser2738/malgoro)

## Overview

Malgoro is a modern desktop environment that combines the elegant aesthetics of classic 2000s desktops (Windows XP, Luna theme era) with robust, enterprise-grade features. It consists of two main components:

### MalgoroPkg - Git-Based Package Manager
A revolutionary package management system that uses Git repositories as package sources, enabling efficient multi-package distribution and seamless updates.

**Key Features**:
- 📦 Git-native package distribution
- 🔄 Multi-package repositories (90% reduction in repo count)
- 🔒 SHA-256 verification and dependency resolution
- 🗃️ SQLite-backed package database
- ⚡ Fast, efficient C++20 implementation

### MalgoroDE - Desktop Environment
A beautiful, functional desktop environment inspired by Budgie but designed for traditional desktop workflows with a nostalgic 2000s aesthetic.

**Key Features**:
- 🪟 Classic window decorations (24px titlebars, 1px borders)
- 🎨 Five elegant themes (Classic, Luna, Royale, Olive, Silver)
- 📊 Traditional panel with taskbar and system tray
- 🚀 Application launcher with search
- ⚙️ Comprehensive settings manager
- 🖥️ X11-based (Wayland support planned)

## Screenshots

*Coming soon - Development in progress*

## Installation

### From AUR (Recommended for Arch/Manjaro)

```bash
# Install MalgoroPkg
yay -S malgoropkg

# Install Malgoro Desktop Environment
malgoropkg install malgoro-desktop-complete
```

### From Source

```bash
# Clone repository
git clone https://github.com/privuser2738/malgoro
cd malgoro

# Build MalgoroPkg
cd MalgoroPkg
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install

# Build MalgoroDE (coming soon)
cd ../../MalgoroDE
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install
```

**Dependencies**:

*MalgoroPkg*:
- libgit2 >= 1.5
- sqlite >= 3.35
- openssl >= 3.0
- CMake >= 3.20
- GCC >= 11 or Clang >= 14 (C++20 support)

*MalgoroDE*:
- libx11
- gtk3 or gtk4
- libwnck-3
- cairo
- pango
- dbus

## Quick Start

### Using MalgoroPkg

```bash
# Add repositories
malgoropkg repo-add malgoro-core https://github.com/privuser2738/malgoro-core
malgoropkg repo-add malgoro-themes https://github.com/privuser2738/malgoro-themes

# Sync repositories
malgoropkg sync

# Install packages
malgoropkg install malgoro-wm malgoro-panel malgoro-launcher

# Install a theme
malgoropkg install malgoro-theme-luna malgoro-icons-classic

# List installed packages
malgoropkg list-installed

# Update all packages
malgoropkg update

# Remove package
malgoropkg remove package-name
```

### Starting Malgoro Desktop

```bash
# From display manager - select "Malgoro Desktop" at login

# Or start manually
startx malgoro-session

# Or in nested X server (testing)
Xephyr -screen 1280x720 :1 &
DISPLAY=:1 malgoro-session
```

## Project Structure

```
malgoro/
├── MalgoroPkg/              # Git-based package manager
│   ├── src/
│   │   ├── core/            # Core package management
│   │   ├── git/             # Git operations
│   │   ├── database/        # SQLite database
│   │   └── utils/           # Utilities
│   ├── include/             # Public headers
│   ├── tests/               # Unit tests
│   └── CMakeLists.txt
│
├── MalgoroDE/               # Desktop environment
│   ├── src/
│   │   ├── wm/              # Window manager
│   │   ├── panel/           # Desktop panel
│   │   ├── launcher/        # Application launcher
│   │   ├── settings/        # Settings manager
│   │   └── themes/          # Theme system
│   ├── include/             # Public headers
│   └── CMakeLists.txt
│
├── config/                  # Configuration files
│   └── repositories.conf    # Default repositories
│
├── scripts/                 # Helper scripts
│   ├── build/               # Build scripts
│   ├── install/             # Installation scripts
│   ├── package/             # Package creation tools
│   └── test/                # Test scripts
│
├── templates/               # Package templates
│   ├── multi-package/       # Multi-package repository template
│   └── single-package/      # Single-package repository template
│
└── docs/                    # Documentation
    ├── ARCHITECTURE.md
    ├── REPOSITORY_STRUCTURE.md
    ├── MULTI_PACKAGE_QUICKSTART.md
    ├── GITHUB_SETUP.md
    └── NEXT_STEPS.md
```

## Package Repositories

Malgoro uses a multi-package repository architecture for efficient package distribution:

### Official Repositories

| Repository | Packages | Description |
|------------|----------|-------------|
| [malgoro-core](https://github.com/privuser2738/malgoro-core) | 5 | Core desktop components |
| [malgoro-themes](https://github.com/privuser2738/malgoro-themes) | 10 | Themes, icons, cursors, wallpapers |
| [malgoro-applications](https://github.com/privuser2738/malgoro-applications) | 8-12 | Desktop applications |
| [malgoro-utilities](https://github.com/privuser2738/malgoro-utilities) | 5-8 | System utilities and tools |

### Repository Efficiency

Traditional approach: **70 repositories** for 70 packages
Malgoro approach: **8 repositories** for 70 packages (90% reduction!)

See [REPOSITORY_STRUCTURE.md](docs/REPOSITORY_STRUCTURE.md) for details.

## Creating Packages

### Quick Package Creation

```bash
# Use the package creation wizard
./scripts/package/create-package.sh

# Or manually using templates
cp -r templates/multi-package/ my-packages
cd my-packages

# Edit PKGINFO files
vim packages/my-app/PKGINFO

# Test locally
malgoropkg install packages/my-app

# Publish to GitHub
git init
git add .
git commit -m "Initial packages"
git remote add origin https://github.com/yourusername/my-packages
git push -u origin main
```

See [MULTI_PACKAGE_QUICKSTART.md](docs/MULTI_PACKAGE_QUICKSTART.md) for details.

## Architecture

### MalgoroPkg Architecture

```
┌─────────────────────────────────────────┐
│         MalgoroPkg CLI                  │
├─────────────────────────────────────────┤
│  PackageManager  │  RepositoryManager   │
├──────────────────┼─────────────────────┤
│   GitHandler     │  Database (SQLite)  │
├──────────────────┼─────────────────────┤
│  FileSystem Utils │  Security/Verify   │
└─────────────────────────────────────────┘
```

### MalgoroDE Architecture

```
┌─────────────────────────────────────────┐
│         X11 Display Server              │
├─────────────────────────────────────────┤
│  WindowManager │  Panel  │  Launcher    │
├────────────────┼─────────┼──────────────┤
│  Decorator │ Workspace │ Settings │    │
├────────────────┼─────────┼──────────────┤
│  ThemeManager  │  GTK3/4 │  D-Bus       │
└─────────────────────────────────────────┘
```

See [ARCHITECTURE.md](docs/ARCHITECTURE.md) for details.

## Themes

Malgoro includes five classic themes:

| Theme | Colors | Style | Inspired By |
|-------|--------|-------|-------------|
| Classic | Gray/Blue | Traditional | Windows 2000 |
| Luna | Blue/Green | Modern classic | Windows XP |
| Royale | Deep Blue | Professional | Windows XP Media Center |
| Olive | Olive/Green | Natural | Windows XP Olive |
| Silver | Gray/Silver | Elegant | Windows XP Silver |

All themes feature:
- 24px titlebars with gradient or solid colors
- Classic 1px borders
- 16x16px titlebar buttons (minimize, maximize, close)
- Matching GTK themes and icon sets

## Development Status

### Completed ✅
- MalgoroPkg core implementation (C++)
- Multi-package repository architecture
- Package discovery and installation system
- MalgoroDE architecture and headers
- Build system and helper scripts
- Comprehensive documentation
- Package templates

### In Progress 🔨
- MalgoroDE component implementation
- Window manager core features
- Panel and taskbar
- Application launcher

### Planned 📋
- Settings manager
- File manager integration
- Compositing effects
- Wayland support
- Plugin system

See [NEXT_STEPS.md](docs/NEXT_STEPS.md) for the development roadmap.

## Contributing

We welcome contributions! Here's how you can help:

### Code Contributions
- 🐛 **Bug fixes** - Found a bug? Submit a PR!
- ✨ **Features** - Implement planned features from our roadmap
- 🎨 **Themes** - Create new theme variants
- 📱 **Applications** - Build applications for Malgoro

### Non-Code Contributions
- 📝 **Documentation** - Improve docs, write tutorials
- 🌍 **Translations** - Translate to other languages
- 🎨 **Design** - Create icons, wallpapers, themes
- 🧪 **Testing** - Test on different systems, report issues

### Getting Started

```bash
# Fork the repository
# Clone your fork
git clone https://github.com/yourusername/malgoro

# Create a branch
git checkout -b feature/my-feature

# Make changes and commit
git commit -m "Add my feature"

# Push and create PR
git push origin feature/my-feature
```

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## Documentation

- [Architecture Overview](docs/ARCHITECTURE.md)
- [Repository Structure](docs/REPOSITORY_STRUCTURE.md)
- [Multi-Package Quick Start](docs/MULTI_PACKAGE_QUICKSTART.md)
- [Package Creation Guide](docs/PACKAGE_CREATION.md)
- [Repository Examples](docs/REPOSITORY_EXAMPLES.md)
- [GitHub Setup Guide](docs/GITHUB_SETUP.md)
- [Next Steps](docs/NEXT_STEPS.md)

## Community

- **GitHub Issues**: [Report bugs](https://github.com/privuser2738/malgoro/issues)
- **GitHub Discussions**: [Ask questions, share ideas](https://github.com/privuser2738/malgoro/discussions)
- **Discord**: Coming soon
- **Reddit**: r/MalgoroDE (coming soon)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Inspired by **Budgie Desktop** - Modern, elegant desktop design
- Inspired by **Windows XP Luna** - Classic 2000s aesthetic
- Built with **GTK**, **X11**, **libwnck**, and **Cairo**
- Package management concepts from **pacman**, **apt**, and **Nix**

## FAQ

### Why create another desktop environment?

Malgoro fills a specific niche: users who want a modern, functional desktop with the elegant aesthetics of classic 2000s interfaces. While many modern DEs focus on minimalism or flat design, Malgoro embraces the polished, dimensional look of that era while providing robust, enterprise-grade functionality.

### Why Git-based package management?

Git is ubiquitous, reliable, and efficient. By leveraging Git:
- **Multi-package repositories** reduce infrastructure overhead
- **Version control** is built-in
- **Distribution is free** (GitHub, GitLab, etc.)
- **Updates are fast** (delta compression)
- **Anyone can host** packages

### Is Malgoro production-ready?

Not yet. Malgoro is currently in active development (v0.1.0-dev). MalgoroPkg is functional, but MalgoroDE components are still being implemented. Expected v0.1.0 release: Q2 2025.

### What distributions are supported?

Primary target: **Arch Linux** and **Manjaro**
Future support: Ubuntu, Fedora, Debian

### Can I use MalgoroPkg with other DEs?

Yes! MalgoroPkg is a standalone package manager that works with any desktop environment or window manager.

### How does Malgoro compare to XFCE/MATE?

| Feature | Malgoro | XFCE | MATE |
|---------|---------|------|------|
| Base | X11/GTK3-4 | X11/GTK3 | X11/GTK3 |
| Aesthetic | 2000s classic | Modern simple | GNOME 2 classic |
| Package Manager | MalgoroPkg (Git) | System PM | System PM |
| Resource Usage | Light-Medium | Light | Light |
| Customization | High | High | High |

## Roadmap

### v0.1.0 (Q2 2025)
- [x] MalgoroPkg package manager
- [ ] Basic window manager
- [ ] Basic panel
- [ ] Application launcher
- [ ] One theme (Luna)

### v0.2.0 (Q3 2025)
- [ ] Settings manager
- [ ] All five themes
- [ ] System tray
- [ ] Desktop icons
- [ ] File manager integration

### v1.0.0 (Q4 2025)
- [ ] Compositing support
- [ ] Advanced theming
- [ ] Plugin system
- [ ] Complete documentation
- [ ] AUR stable release

### v2.0.0 (2026)
- [ ] Wayland support
- [ ] Mobile/tablet support
- [ ] Cloud integration
- [ ] AI-powered features

## Support the Project

Malgoro is free and open-source software. If you find it useful, consider:

- ⭐ **Star** the repository
- 🐛 **Report** bugs and issues
- 💻 **Contribute** code or documentation
- 💬 **Spread** the word
- ☕ **Sponsor** development (coming soon)

---

**Made with ❤️ by the Malgoro team**

*Bringing back the elegance of classic desktop computing*
