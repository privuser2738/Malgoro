# GitHub Repository Setup Guide

This guide explains how to set up the Malgoro project repositories on GitHub.

## Repository Structure

The Malgoro project consists of multiple repositories:

### 1. Main Source Repository

**Repository**: `malgoro`
**URL**: `https://github.com/privuser2738/malgoro`
**Purpose**: Source code for MalgoroPkg and MalgoroDE

**Contents**:
- MalgoroPkg source code (C++ package manager)
- MalgoroDE source code (C++ desktop environment)
- Build scripts and documentation
- Templates for package creation

**Type**: Source code repository (not a package repository)

### 2. Package Repositories

These repositories contain installable packages:

#### malgoro-core
**URL**: `https://github.com/privuser2738/malgoro-core`
**Type**: Multi-package repository
**Description**: Core desktop environment components

**Packages** (5 total):
```
packages/
├── malgoro-wm/           # Window manager
├── malgoro-panel/        # Desktop panel
├── malgoro-launcher/     # Application launcher
├── malgoro-settings/     # Settings manager
└── malgoro-session/      # Session manager
```

#### malgoro-themes
**URL**: `https://github.com/privuser2738/malgoro-themes`
**Type**: Multi-package repository
**Description**: Themes, icons, cursors, and wallpapers

**Packages** (10 total):
```
packages/
├── malgoro-theme-classic/    # Classic theme
├── malgoro-theme-luna/       # Luna (blue) theme
├── malgoro-theme-royale/     # Royale theme
├── malgoro-theme-olive/      # Olive (green) theme
├── malgoro-theme-silver/     # Silver theme
├── malgoro-icons-classic/    # Classic icon set
├── malgoro-icons-modern/     # Modern icon set
├── malgoro-cursors/          # Cursor themes
├── malgoro-wallpapers/       # Wallpaper collection
└── malgoro-sounds/           # System sounds
```

#### malgoro-applications
**URL**: `https://github.com/privuser2738/malgoro-applications`
**Type**: Multi-package repository
**Description**: Desktop applications

**Packages** (8-12 total):
```
packages/
├── malgoro-terminal/         # Terminal emulator
├── malgoro-files/            # File manager
├── malgoro-editor/           # Text editor
├── malgoro-calc/             # Calculator
├── malgoro-viewer/           # Image viewer
├── malgoro-music/            # Music player
├── malgoro-monitor/          # System monitor
└── malgoro-archiver/         # Archive manager
```

#### malgoro-utilities
**URL**: `https://github.com/privuser2738/malgoro-utilities`
**Type**: Multi-package repository
**Description**: System utilities and tools

**Packages** (5-8 total):
```
packages/
├── malgoro-screenshot/       # Screenshot tool
├── malgoro-backup/           # Backup utility
├── malgoro-cleaner/          # Disk cleaner
├── malgoro-tweaks/           # System tweaks
└── malgoro-info/             # System information
```

## Setup Steps

### Step 1: Create Main Repository

```bash
# Navigate to project directory
cd /path/to/malgoro-desktop

# Initialize git (if not already done)
git init

# Create .gitignore
cat > .gitignore << 'EOF'
# Build artifacts
build/
MalgoroPkg/build/
MalgoroDE/build/
*.o
*.so
*.a

# CMake
CMakeFiles/
CMakeCache.txt
cmake_install.cmake

# IDE
.vscode/
.idea/

# Temporary
*~
*.swp

# Logs
*.log
EOF

# Add files
git add .
git commit -m "Initial commit: MalgoroPkg and MalgoroDE

- MalgoroPkg: Git-based package manager for Malgoro
- MalgoroDE: Desktop environment with classic 2000s aesthetic
- Complete C++ implementation with build system
- Documentation and templates included

🤖 Generated with [Claude Code](https://claude.com/claude-code)

Co-Authored-By: Claude <noreply@anthropic.com>"

# Add remote and push
git remote add origin https://github.com/privuser2738/malgoro
git branch -M main
git push -u origin main
```

### Step 2: Create Package Repositories

For each package repository:

```bash
# Example: Creating malgoro-core repository

# 1. Create new directory
mkdir -p ~/malgoro-repos/malgoro-core
cd ~/malgoro-repos/malgoro-core

# 2. Copy multi-package template
cp -r /path/to/malgoro-desktop/templates/multi-package/* .

# 3. Customize README.md
# Edit README.md with repository-specific information

# 4. Create package directories
mkdir -p packages/{malgoro-wm,malgoro-panel,malgoro-launcher,malgoro-settings,malgoro-session}

# 5. For each package, create PKGINFO
# Example for malgoro-wm:
cat > packages/malgoro-wm/PKGINFO << EOF
name=malgoro-wm
version=0.1.0
description=Malgoro window manager - Classic 2000s desktop experience
maintainer=privuser2738 <your.email@example.com>
license=MIT
depends=libx11,libxft,libwnck-3,cairo,pango
EOF

# 6. Create package structure
mkdir -p packages/malgoro-wm/files/usr/bin
mkdir -p packages/malgoro-wm/README.md

# 7. Initialize git
git init
git add .
git commit -m "Initial malgoro-core packages

🤖 Generated with [Claude Code](https://claude.com/claude-code)

Co-Authored-By: Claude <noreply@anthropic.com>"

# 8. Push to GitHub
git remote add origin https://github.com/privuser2738/malgoro-core
git branch -M main
git push -u origin main
```

### Step 3: Configure MalgoroPkg Repositories

Create the default repositories configuration:

**File**: `/etc/malgoro/repositories.conf` (or `~/.config/malgoro/repositories.conf`)

```ini
# Malgoro Package Repositories
# Each repository can contain MULTIPLE packages

[malgoro-core]
url = https://github.com/privuser2738/malgoro-core
description = Core desktop environment components
priority = 10
enabled = 1

[malgoro-themes]
url = https://github.com/privuser2738/malgoro-themes
description = Themes, icons, cursors, and wallpapers
priority = 20
enabled = 1

[malgoro-applications]
url = https://github.com/privuser2738/malgoro-applications
description = Desktop applications
priority = 30
enabled = 1

[malgoro-utilities]
url = https://github.com/privuser2738/malgoro-utilities
description = System utilities and tools
priority = 40
enabled = 1
```

### Step 4: Sync and Install

```bash
# Add repositories
malgoropkg repo-add malgoro-core https://github.com/privuser2738/malgoro-core
malgoropkg repo-add malgoro-themes https://github.com/privuser2738/malgoro-themes
malgoropkg repo-add malgoro-applications https://github.com/privuser2738/malgoro-applications
malgoropkg repo-add malgoro-utilities https://github.com/privuser2738/malgoro-utilities

# Sync repositories
malgoropkg sync

# Install core desktop
malgoropkg install malgoro-wm malgoro-panel malgoro-launcher

# Install a theme
malgoropkg install malgoro-theme-luna malgoro-icons-classic
```

## Repository Organization

### Package Naming Convention

All Malgoro packages should follow this naming:

- **Prefix**: `malgoro-`
- **Category**: component type (wm, panel, theme, etc.)
- **Variant**: optional variant name (luna, classic, etc.)

Examples:
- ✅ `malgoro-wm` (window manager)
- ✅ `malgoro-theme-luna` (Luna theme)
- ✅ `malgoro-terminal` (terminal application)
- ❌ `malgoroWM` (incorrect capitalization)
- ❌ `wm-malgoro` (incorrect order)

### Version Numbering

Use semantic versioning: `MAJOR.MINOR.PATCH`

- **MAJOR**: Incompatible API changes
- **MINOR**: New functionality (backwards compatible)
- **PATCH**: Bug fixes

Examples:
- `0.1.0` - Initial development
- `1.0.0` - First stable release
- `1.1.0` - New features added
- `1.1.1` - Bug fixes

### Dependency Management

List all runtime dependencies in PKGINFO:

```ini
# Single dependency
depends=gtk3

# Multiple dependencies (comma-separated, no spaces)
depends=gtk3,libx11,cairo,pango

# No dependencies
depends=
```

Common dependencies for Malgoro packages:
- `libx11` - X11 client library
- `gtk3` or `gtk4` - GTK toolkit
- `cairo` - 2D graphics
- `pango` - Text rendering
- `libwnck-3` - Window navigator
- `dbus` - Message bus system

## Building from Source

After repositories are created and packages are added:

### Build MalgoroPkg

```bash
cd malgoro/MalgoroPkg
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install
```

### Build MalgoroDE Components

After implementing the C++ source:

```bash
cd malgoro/MalgoroDE
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install
```

### Create Packages from Build

```bash
# After building, create package structure
cd malgoro

# Copy binaries to package files/
mkdir -p ~/malgoro-repos/malgoro-core/packages/malgoro-wm/files/usr/bin
cp MalgoroDE/build/malgoro-wm ~/malgoro-repos/malgoro-core/packages/malgoro-wm/files/usr/bin/

# Commit and push
cd ~/malgoro-repos/malgoro-core
git add .
git commit -m "Add malgoro-wm binary"
git push
```

## Testing

### Local Testing

```bash
# Install from local directory
malgoropkg install ~/malgoro-repos/malgoro-core/packages/malgoro-wm

# Verify installation
malgoro-wm --version
malgoropkg list-installed | grep malgoro
```

### Remote Testing

```bash
# Sync from GitHub
malgoropkg sync

# Install from remote
malgoropkg install malgoro-wm

# Check for updates
malgoropkg update
```

## Maintenance

### Updating Packages

```bash
# 1. Update version in PKGINFO
vim packages/malgoro-wm/PKGINFO  # Change version to 0.2.0

# 2. Update files
cp new-build/malgoro-wm packages/malgoro-wm/files/usr/bin/

# 3. Commit and push
git add .
git commit -m "Update malgoro-wm to 0.2.0"
git push

# 4. Users update
malgoropkg sync
malgoropkg update malgoro-wm
```

### Adding New Packages

```bash
# 1. Create package directory
mkdir -p packages/new-package/files/usr/bin

# 2. Create PKGINFO
cat > packages/new-package/PKGINFO << EOF
name=new-package
version=1.0.0
description=Description here
maintainer=privuser2738 <email@example.com>
license=MIT
depends=
EOF

# 3. Add files and commit
git add .
git commit -m "Add new-package"
git push
```

## Documentation Links

- [Repository Structure](REPOSITORY_STRUCTURE.md)
- [Multi-Package Quick Start](MULTI_PACKAGE_QUICKSTART.md)
- [Package Creation Guide](PACKAGE_CREATION.md)

## Support

- Main Repository: https://github.com/privuser2738/malgoro
- Issues: https://github.com/privuser2738/malgoro/issues
- Discussions: https://github.com/privuser2738/malgoro/discussions
