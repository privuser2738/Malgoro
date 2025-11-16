# MalgoroPkg Repository Structure Guide

## Overview

MalgoroPkg repositories are **Git repositories that can contain one or multiple packages**. This flexible approach allows you to:

- Group related packages together
- Reduce the number of repositories to manage
- Share common build scripts and resources
- Organize packages by category or maintainer
- Scale from small single-package repos to large multi-package collections

## Repository Models

### Model 1: Single Package Repository

**Best for:**
- Large, complex packages
- Packages with many files
- Packages requiring extensive build processes
- Flagship applications

**Structure:**
```
my-app/
├── README.md
├── LICENSE
├── PKGINFO
├── build.sh
├── install.sh
└── files/
    └── usr/
        └── bin/
            └── my-app
```

**Example:**
```
firefox-malgoro/
├── README.md
├── PKGINFO
├── build.sh
└── files/
    └── usr/
        └── bin/
            └── firefox
```

### Model 2: Multi-Package Repository (Recommended)

**Best for:**
- Related packages (e.g., all GTK themes)
- Small to medium packages
- Packages by the same maintainer
- Category-based collections (e.g., all development tools)
- Resource efficiency

**Structure:**
```
malgoro-themes/
├── README.md
├── LICENSE
└── packages/
    ├── malgoro-classic-theme/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/share/themes/
    ├── malgoro-luna-theme/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/share/themes/
    ├── malgoro-royale-theme/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/share/themes/
    ├── malgoro-icons/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/share/icons/
    └── malgoro-cursors/
        ├── PKGINFO
        └── files/
            └── usr/share/icons/
```

**MalgoroPkg automatically detects** all packages in the `packages/` directory!

## Recommended Repository Organization

### By Category (Recommended for Official Repos)

#### malgoro-core
```
malgoro-core/
├── README.md
└── packages/
    ├── malgoro-wm/          # Window manager
    ├── malgoro-panel/       # Desktop panel
    ├── malgoro-menu/        # Application menu
    ├── malgoro-settings/    # Settings manager
    └── malgoro-session/     # Session manager
```

#### malgoro-themes
```
malgoro-themes/
└── packages/
    ├── malgoro-classic-theme/
    ├── malgoro-luna-theme/
    ├── malgoro-royale-theme/
    ├── malgoro-olive-theme/
    ├── malgoro-silver-theme/
    ├── malgoro-icons/
    └── malgoro-cursors/
```

#### malgoro-applications
```
malgoro-applications/
└── packages/
    ├── malgoro-terminal/
    ├── malgoro-editor/
    ├── malgoro-files/
    ├── malgoro-calculator/
    └── malgoro-imageviewer/
```

#### malgoro-utilities
```
malgoro-utilities/
└── packages/
    ├── malgoro-screenshot/
    ├── malgoro-archiver/
    ├── malgoro-sysmonitor/
    └── malgoro-backup/
```

### By Maintainer (Good for Community Repos)

```
john-packages/
├── README.md
└── packages/
    ├── johns-app1/
    ├── johns-app2/
    ├── johns-app3/
    └── johns-lib/
```

### By Size/Complexity

**Small Packages Repository:**
```
malgoro-small-apps/
└── packages/
    ├── hello-world/
    ├── color-picker/
    ├── timer/
    └── notes/
```

**Large Packages (Individual Repos):**
```
firefox-malgoro/       (separate repo)
libreoffice-malgoro/   (separate repo)
blender-malgoro/       (separate repo)
```

## Package Discovery

### How MalgoroPkg Finds Packages

When you run `malgoropkg sync`, MalgoroPkg:

1. Clones/pulls the repository
2. Looks for packages in two places:
   - `packages/*/PKGINFO` (multi-package)
   - `PKGINFO` (single-package)
3. Parses each PKGINFO file
4. Adds packages to the database

**Example scan:**
```
Repository: malgoro-themes
  Found: malgoro-classic-theme (1.0.0)
  Found: malgoro-luna-theme (1.0.0)
  Found: malgoro-royale-theme (1.0.0)
  Found: malgoro-icons (1.0.0)
  Found: malgoro-cursors (1.0.0)
Total: 5 packages from 1 repository
```

## Detailed Structure Examples

### Example 1: Themes Repository (Multi-Package)

```
malgoro-themes/
├── README.md
├── LICENSE
├── .gitignore
├── scripts/
│   ├── build-all.sh
│   └── test-themes.sh
└── packages/
    ├── malgoro-classic-theme/
    │   ├── PKGINFO
    │   ├── README.md
    │   └── files/
    │       └── usr/share/themes/Malgoro-Classic/
    │           ├── gtk-3.0/
    │           │   └── gtk.css
    │           └── index.theme
    ├── malgoro-luna-theme/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/share/themes/Malgoro-Luna/
    ├── malgoro-icons/
    │   ├── PKGINFO
    │   ├── build.sh
    │   ├── src/
    │   │   └── (SVG source files)
    │   └── files/
    │       └── usr/share/icons/Malgoro/
    └── common/
        └── shared-resources/
```

### Example 2: Desktop Components (Multi-Package)

```
malgoro-core/
├── README.md
├── CMakeLists.txt          # Optional: shared build
├── common/
│   ├── include/            # Shared headers
│   └── libs/               # Shared libraries
└── packages/
    ├── malgoro-wm/
    │   ├── PKGINFO
    │   ├── build.sh
    │   ├── src/
    │   │   └── (C++ sources)
    │   └── files/
    │       └── usr/
    │           └── bin/
    │               └── malgoro-wm
    ├── malgoro-panel/
    │   ├── PKGINFO
    │   ├── build.sh
    │   └── src/
    └── malgoro-session/
        ├── PKGINFO
        └── files/
            ├── usr/bin/malgoro-session
            └── usr/share/xsessions/malgoro.desktop
```

### Example 3: Simple Utilities (Multi-Package)

```
malgoro-utilities/
└── packages/
    ├── malgoro-screenshot/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/
    │           ├── bin/malgoro-screenshot
    │           └── share/applications/malgoro-screenshot.desktop
    ├── malgoro-colorpicker/
    │   ├── PKGINFO
    │   └── files/
    │       └── usr/bin/malgoro-colorpicker
    └── malgoro-notes/
        ├── PKGINFO
        └── files/
            └── usr/bin/malgoro-notes
```

## PKGINFO File Examples

### For Package in Multi-Package Repo

```ini
# packages/malgoro-classic-theme/PKGINFO
name=malgoro-classic-theme
version=1.0.0
description=Classic Windows XP inspired theme for Malgoro
maintainer=Malgoro Team <team@malgoro.org>
license=GPL-3.0
depends=gtk3
provides=malgoro-theme
```

### With Dependencies Between Packages in Same Repo

```ini
# packages/malgoro-panel/PKGINFO
name=malgoro-panel
version=1.0.0
description=Desktop panel for Malgoro
maintainer=Malgoro Team <team@malgoro.org>
license=GPL-3.0
depends=malgoro-wm,gtk3,libwnck
```

## Best Practices

### ✅ DO:

1. **Group Related Packages**
   ```
   malgoro-themes/packages/
   ├── theme1/
   ├── theme2/
   └── theme3/
   ```

2. **Use Descriptive Names**
   ```
   gnome-apps/          # Good
   my-stuff/            # Bad
   ```

3. **Keep Similar Sizes Together**
   ```
   small-utilities/     # All small apps
   large-apps/         # Each big app separate
   ```

4. **Document Repository Contents**
   ```
   README.md should list all packages
   ```

5. **Version Control Everything**
   ```
   Use Git tags for releases
   ```

### ❌ DON'T:

1. **Mix Unrelated Packages**
   ```
   random-stuff/packages/
   ├── browser/         # Bad: unrelated
   ├── game/
   └── driver/
   ```

2. **Create Too Many Small Repos**
   ```
   cursor-theme-1/      # Bad: each cursor theme
   cursor-theme-2/      # separate repo
   cursor-theme-3/

   Instead use:
   cursor-themes/packages/
   ├── theme1/
   ├── theme2/
   └── theme3/
   ```

3. **Put Huge Packages in Multi-Package Repos**
   ```
   apps/packages/
   ├── small-app/       # OK
   └── chromium/        # Bad: too large
   ```

## Size Guidelines

### Single Package Repository
- Package size > 50MB
- Complex build process
- Many dependencies
- Flagship application

### Multi-Package Repository
- Individual packages < 10MB each
- Related functionality
- Simple build process
- 5-20 packages per repo recommended

### Optimal Organization
```
Small packages (< 1MB):   10-50 per repo
Medium packages (1-10MB): 5-20 per repo
Large packages (10-50MB): 2-5 per repo
Huge packages (> 50MB):   1 per repo
```

## Creating a Multi-Package Repository

### Step 1: Create Repository

```bash
mkdir malgoro-themes
cd malgoro-themes
git init
```

### Step 2: Create Structure

```bash
mkdir -p packages/{theme1,theme2,theme3}
```

### Step 3: Add Packages

```bash
# For each package
cd packages/theme1

cat > PKGINFO << EOF
name=malgoro-classic-theme
version=1.0.0
description=Classic theme
maintainer=You <you@example.com>
license=GPL-3.0
EOF

mkdir -p files/usr/share/themes/Malgoro-Classic
# Add theme files...
```

### Step 4: Document

```bash
cat > README.md << EOF
# Malgoro Themes

This repository contains multiple theme packages:

- malgoro-classic-theme - Classic Windows XP style
- malgoro-luna-theme - Blue theme
- malgoro-royale-theme - Deep blue theme

## Installation

\`\`\`bash
malgoropkg install malgoro-classic-theme
\`\`\`
EOF
```

### Step 5: Commit and Push

```bash
git add .
git commit -m "Initial themes"
git push origin main
```

## Using Multi-Package Repositories

### Add Repository

```bash
sudo malgoropkg repo-add malgoro-themes https://github.com/privuser2738/malgoro-themes
```

### Sync Repository

```bash
sudo malgoropkg sync
```

This will discover **all packages** in the repository automatically!

### Install Specific Package

```bash
sudo malgoropkg install malgoro-classic-theme
```

### List All Packages from Repository

```bash
malgoropkg list --available | grep malgoro-themes
```

## Advanced: Shared Resources

### Shared Build Scripts

```
malgoro-apps/
├── scripts/
│   ├── common-build.sh     # Shared by all packages
│   └── common-install.sh
└── packages/
    ├── app1/
    │   └── build.sh        # Calls ../scripts/common-build.sh
    ├── app2/
    │   └── build.sh
    └── app3/
        └── build.sh
```

### Shared Libraries

```
malgoro-libs/
├── common/
│   ├── include/
│   │   └── malgoro-common.h
│   └── lib/
│       └── libmalgoro-common.so
└── packages/
    ├── app1/
    │   └── build.sh        # Links against ../common/lib/
    └── app2/
        └── build.sh
```

## Repository Examples

### Official Malgoro Repositories

**malgoro-core** (5-10 packages)
- Desktop environment components
- Core system tools
- Essential libraries

**malgoro-themes** (10-15 packages)
- GTK themes
- Icon themes
- Cursor themes
- Wallpapers

**malgoro-applications** (20-30 packages)
- Text editors
- File managers
- Utilities
- Media players

**malgoro-community** (50+ packages)
- User-submitted packages
- Experimental software
- Niche tools

### Community Repository Examples

**user123-apps** (3-5 packages)
- Personal projects
- Maintained by single developer

**gaming-apps** (10-20 packages)
- Game launchers
- Gaming utilities
- Emulators

**development-tools** (15-25 packages)
- IDEs
- Compilers
- Debuggers
- Version control tools

## Migration Strategy

### From Single-Package to Multi-Package

**Before:**
```
app1-repo/
app2-repo/
app3-repo/
```

**After:**
```
my-apps/
└── packages/
    ├── app1/
    ├── app2/
    └── app3/
```

**Migration Steps:**
1. Create new multi-package repo
2. Copy each app into `packages/`
3. Update repository configuration
4. Test package discovery
5. Archive old repos

## Performance Considerations

### Git Repository Size

**Small Repo (< 10MB):**
- Fast cloning
- Quick updates
- Good for multi-package

**Medium Repo (10-100MB):**
- Acceptable for multi-package
- Consider Git LFS for binary files

**Large Repo (> 100MB):**
- Slower cloning/updates
- Consider splitting
- Use shallow clones

### Optimization Tips

1. **Use .gitignore**
   ```gitignore
   *.o
   *.so
   build/
   .cache/
   ```

2. **Git LFS for Binary Files**
   ```bash
   git lfs track "*.png"
   git lfs track "*.ttf"
   ```

3. **Shallow Clones**
   MalgoroPkg can use shallow clones for large repos
   ```bash
   git clone --depth 1 <url>
   ```

## Summary

### Key Takeaways

✅ **One Git repo can contain many packages**
✅ **Group related packages together**
✅ **Reduces number of repos to manage**
✅ **More efficient resource usage**
✅ **MalgoroPkg automatically discovers all packages**
✅ **Flexible organization options**

### Recommended Structure

```
malgoro-category/
├── README.md              # Document all packages
├── LICENSE                # Shared license
├── .gitignore            # Ignore build artifacts
├── scripts/              # Shared scripts (optional)
│   └── common-build.sh
└── packages/             # Individual packages
    ├── package1/
    │   ├── PKGINFO       # Required
    │   ├── build.sh      # Optional
    │   └── files/        # Package files
    ├── package2/
    └── package3/
```

This structure is:
- **Scalable** - Add packages easily
- **Maintainable** - Related packages together
- **Efficient** - One repo, many packages
- **Flexible** - Mix sizes appropriately
- **Discoverable** - Automatic package detection

---

**Remember**: The goal is to balance convenience, maintainability, and resource efficiency. Group packages logically and keep repository sizes manageable!
