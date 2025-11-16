# Recommended Repository Organization for Malgoro

Quick reference for organizing Malgoro package repositories.

## Official Malgoro Repositories

### 1. malgoro-core
**URL**: https://github.com/privuser2738/malgoro-core
**Purpose**: Core desktop environment components
**Package Count**: 5-7 packages

```
Packages:
- malgoro-wm          Window manager
- malgoro-panel       Desktop panel
- malgoro-menu        Application menu
- malgoro-settings    Settings manager
- malgoro-session     Session manager
```

**Size**: ~2-5MB total
**Type**: Multi-package repository

---

### 2. malgoro-themes
**URL**: https://github.com/privuser2738/malgoro-themes
**Purpose**: Visual themes for desktop
**Package Count**: 10-15 packages

```
Packages:
- malgoro-classic-theme    Default theme
- malgoro-luna-theme       Blue theme
- malgoro-royale-theme     Deep blue theme
- malgoro-olive-theme      Green theme
- malgoro-silver-theme     Gray minimal theme
- malgoro-icons            Icon theme
- malgoro-cursors          Cursor theme
- malgoro-wallpapers-*     Wallpaper packs
- malgoro-sounds           Sound theme
```

**Size**: ~5-10MB total
**Type**: Multi-package repository

---

### 3. malgoro-applications
**URL**: https://github.com/privuser2738/malgoro-applications
**Purpose**: Small to medium applications
**Package Count**: 15-25 packages

```
Packages:
- malgoro-terminal         Terminal emulator
- malgoro-editor           Text editor
- malgoro-files            File manager
- malgoro-calculator       Calculator
- malgoro-screenshot       Screenshot tool
- malgoro-imageviewer      Image viewer
- malgoro-archiver         Archive manager
- malgoro-notes            Note taking app
- malgoro-timer            Timer/stopwatch
- malgoro-colorpicker      Color picker
- malgoro-sysmonitor       System monitor
- malgoro-calendar         Calendar app
- ... (more small apps)
```

**Size**: ~10-20MB total
**Type**: Multi-package repository

---

### 4. malgoro-utilities
**URL**: https://github.com/privuser2738/malgoro-utilities
**Purpose**: System utilities and tools
**Package Count**: 10-15 packages

```
Packages:
- malgoro-backup           Backup utility
- malgoro-cleaner          Disk cleaner
- malgoro-network-tools    Network utilities
- malgoro-disk-manager     Disk management
- malgoro-process-manager  Process viewer
- malgoro-startup-manager  Autostart manager
- ... (system tools)
```

**Size**: ~5-10MB total
**Type**: Multi-package repository

---

### 5. malgoro-community
**URL**: https://github.com/privuser2738/malgoro-community
**Purpose**: Community contributed packages
**Package Count**: 50+ packages (growing)

```
Structure:
packages/
├── by-maintainer/
│   ├── user1-app1/
│   ├── user1-app2/
│   ├── user2-app1/
│   └── ...
```

**Size**: Variable
**Type**: Multi-package repository

---

## Large Application Repositories (Separate)

### firefox-malgoro
**URL**: https://github.com/privuser2738/firefox-malgoro
**Size**: ~100MB
**Type**: Single-package repository

### chromium-malgoro
**URL**: https://github.com/privuser2738/chromium-malgoro
**Size**: ~150MB
**Type**: Single-package repository

### libreoffice-malgoro
**URL**: https://github.com/privuser2738/libreoffice-malgoro
**Size**: ~200MB
**Type**: Single-package repository

---

## Repository Summary

| Repository | Packages | Size | Type |
|-----------|----------|------|------|
| malgoro-core | 5-7 | ~5MB | Multi |
| malgoro-themes | 10-15 | ~10MB | Multi |
| malgoro-applications | 15-25 | ~20MB | Multi |
| malgoro-utilities | 10-15 | ~10MB | Multi |
| malgoro-community | 50+ | Variable | Multi |
| firefox-malgoro | 1 | ~100MB | Single |
| chromium-malgoro | 1 | ~150MB | Single |
| libreoffice-malgoro | 1 | ~200MB | Single |

**Total Official Packages**: ~70-100 packages
**Total Repositories**: ~8-10 repositories

---

## Configuration

Add to `/etc/malgoro/repositories.conf` or `~/.config/malgoro/repositories.conf`:

```ini
[malgoro-core]
url = https://github.com/privuser2738/malgoro-core
branch = main
enabled = true
priority = 1
description = Core desktop environment components

[malgoro-themes]
url = https://github.com/privuser2738/malgoro-themes
branch = main
enabled = true
priority = 5
description = Visual themes and icons

[malgoro-applications]
url = https://github.com/privuser2738/malgoro-applications
branch = main
enabled = true
priority = 10
description = Desktop applications

[malgoro-utilities]
url = https://github.com/privuser2738/malgoro-utilities
branch = main
enabled = true
priority = 15
description = System utilities

[malgoro-community]
url = https://github.com/privuser2738/malgoro-community
branch = main
enabled = false
priority = 50
description = Community contributed packages

[firefox-malgoro]
url = https://github.com/privuser2738/firefox-malgoro
branch = main
enabled = true
priority = 20
description = Firefox web browser
```

---

## Size Guidelines

### Multi-Package Repository
- **Recommended**: 5-20 packages per repo
- **Max individual package**: 10MB
- **Max total repo**: 50MB
- **Categories**: Related packages

### Single-Package Repository
- **Min package size**: 50MB
- **Use for**: Major applications
- **Examples**: Browsers, Office suites, IDEs

---

## Benefits of This Organization

### Multi-Package Approach
✅ **Fewer repos to manage**: 4-5 official repos instead of 70+
✅ **Related packages together**: Easy to find and maintain
✅ **Shared resources**: Common build scripts, icons, etc.
✅ **Efficient Git**: Less repository overhead
✅ **Easy maintenance**: Update multiple related packages at once

### Mixed Approach (Multi + Single)
✅ **Flexibility**: Small packages grouped, large ones separate
✅ **Performance**: Large packages don't slow down main repos
✅ **Organization**: Clear categories
✅ **Scalability**: Easy to add new packages

---

## Creating Your Own Repository

### For Small Collection (5-20 packages)
Use **multi-package** structure:

```bash
mkdir my-malgoro-apps
cd my-malgoro-apps
git init

mkdir -p packages/{app1,app2,app3}

# Add PKGINFO and files for each
# Commit and push
```

### For Large Application
Use **single-package** structure:

```bash
mkdir my-big-app
cd my-big-app
git init

# Create PKGINFO, build.sh, files/
# Commit and push
```

---

## Package Naming Convention

### Official Packages
Format: `malgoro-{category}-{name}`

Examples:
- `malgoro-classic-theme`
- `malgoro-terminal`
- `malgoro-wm`

### Third-Party Integration
Format: `{app}-malgoro`

Examples:
- `firefox-malgoro`
- `vscode-malgoro`
- `gimp-malgoro`

### Community Packages
Format: `{maintainer}-{name}` or custom

Examples:
- `john-music-player`
- `awesome-app`
- `my-tool`

---

## Quick Start

### 1. Add Repositories

```bash
sudo malgoropkg sync
```

This syncs all configured repositories and discovers all packages!

### 2. List Available Packages

```bash
malgoropkg list --available
```

Shows all packages from all repositories.

### 3. Install Desktop Environment

```bash
# Install complete desktop (pulls in dependencies)
sudo malgoropkg install malgoro-session

# Or individual components
sudo malgoropkg install malgoro-wm
sudo malgoropkg install malgoro-panel
sudo malgoropkg install malgoro-classic-theme
```

### 4. Install Applications

```bash
sudo malgoropkg install malgoro-terminal
sudo malgoropkg install malgoro-editor
sudo malgoropkg install malgoro-files
```

---

## Maintenance

### Updating Packages

```bash
# Sync repositories (fetch latest package lists)
sudo malgoropkg sync

# Update all packages
sudo malgoropkg upgrade

# Update specific package
sudo malgoropkg update malgoro-wm
```

### Adding New Package to Multi-Package Repo

```bash
cd malgoro-applications
mkdir packages/my-new-app
echo "name=my-new-app" > packages/my-new-app/PKGINFO
# Add files...
git add packages/my-new-app
git commit -m "Add my-new-app"
git push
```

Users get it automatically after:
```bash
sudo malgoropkg sync
sudo malgoropkg install my-new-app
```

---

## Statistics

**Efficiency Comparison:**

**Without multi-package approach:**
- 70 packages = 70 Git repositories
- 70 separate clones/pulls
- Scattered maintenance

**With multi-package approach:**
- 70 packages = 8 Git repositories
- 8 clones/pulls (8x faster!)
- Organized maintenance

**Resource Savings:**
- ~90% fewer repositories
- ~90% less Git overhead
- ~50% less disk space (shared resources)
- Much easier to maintain

---

## Summary

**Recommended Organization:**

1. **Core components**: 1 multi-package repo (malgoro-core)
2. **Themes**: 1 multi-package repo (malgoro-themes)
3. **Applications**: 1 multi-package repo (malgoro-applications)
4. **Utilities**: 1 multi-package repo (malgoro-utilities)
5. **Large apps**: Individual repos (firefox, chromium, etc.)
6. **Community**: 1 multi-package repo (malgoro-community)

**Total**: ~8-10 repositories managing 70-100+ packages!

This is **efficient**, **scalable**, and **maintainable**! 🎯
