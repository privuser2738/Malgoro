# Multi-Package Repository Quick Start

**TL;DR**: One Git repo can contain many packages. MalgoroPkg finds them all automatically!

## Core Concept

```
❌ OLD WAY: One package = One repository
package1/  (repo)
package2/  (repo)
package3/  (repo)
= 3 repositories to manage

✅ NEW WAY: Many packages = One repository
my-packages/  (repo)
└── packages/
    ├── package1/
    ├── package2/
    └── package3/
= 1 repository managing 3 packages
```

## Basic Example

### Create Multi-Package Repository

```bash
mkdir malgoro-themes
cd malgoro-themes
git init

# Create structure
mkdir -p packages/{classic-theme,luna-theme,icons}

# Add package 1
cat > packages/classic-theme/PKGINFO << 'EOF'
name=malgoro-classic-theme
version=1.0.0
description=Classic theme
license=GPL-3.0
EOF

mkdir -p packages/classic-theme/files/usr/share/themes

# Add package 2
cat > packages/luna-theme/PKGINFO << 'EOF'
name=malgoro-luna-theme
version=1.0.0
description=Luna theme
license=GPL-3.0
EOF

# Add package 3
cat > packages/icons/PKGINFO << 'EOF'
name=malgoro-icons
version=1.0.0
description=Icon theme
license=GPL-3.0
EOF

# Commit
git add .
git commit -m "Initial themes"
git push origin main
```

### Use the Repository

```bash
# Add repository
sudo malgoropkg repo-add malgoro-themes https://github.com/user/malgoro-themes

# Sync (discovers all 3 packages automatically!)
sudo malgoropkg sync

# Install any package
sudo malgoropkg install malgoro-classic-theme
sudo malgoropkg install malgoro-luna-theme
sudo malgoropkg install malgoro-icons
```

## How MalgoroPkg Finds Packages

MalgoroPkg scans for:

1. **Multi-package**: `packages/*/PKGINFO`
2. **Single-package**: `PKGINFO` in root

**Example scan:**
```
Repository: malgoro-themes
Scanning: packages/
  ✓ Found: packages/classic-theme/PKGINFO
  ✓ Found: packages/luna-theme/PKGINFO
  ✓ Found: packages/icons/PKGINFO

Result: 3 packages discovered
```

## When to Use Multi-Package

✅ **Use multi-package for:**
- Related packages (all themes, all utilities)
- Small packages (< 10MB each)
- Same maintainer
- 5-20 packages per repo

❌ **Use single-package for:**
- Large applications (> 50MB)
- Complex builds
- Frequently updated separately
- Flagship apps (Firefox, LibreOffice)

## Size Guidelines

| Package Size | Packages per Repo | Example |
|-------------|-------------------|---------|
| < 1MB | 20-50 | Utilities, scripts |
| 1-10MB | 10-20 | Themes, small apps |
| 10-50MB | 3-5 | Medium apps |
| > 50MB | 1 | Browsers, IDEs |

## Real Examples

### malgoro-core (Multi-Package)
```
packages/
├── malgoro-wm/          (2MB)
├── malgoro-panel/       (1MB)
├── malgoro-menu/        (500KB)
├── malgoro-settings/    (800KB)
└── malgoro-session/     (100KB)

Total: 5 packages, ~4.5MB
Repository: malgoro-core
```

### firefox-malgoro (Single-Package)
```
PKGINFO
build.sh
files/

Total: 1 package, ~100MB
Repository: firefox-malgoro
```

## Benefits

### Multi-Package Approach

**Efficiency:**
- ✅ Fewer repos (8 repos vs 70 repos)
- ✅ Faster sync (1 clone vs 70 clones)
- ✅ Less disk space

**Maintenance:**
- ✅ Related packages together
- ✅ Shared build scripts
- ✅ Easier updates

**Organization:**
- ✅ Logical grouping
- ✅ Clear categories
- ✅ Easy discovery

## Adding Package to Existing Multi-Package Repo

```bash
# Clone repo
git clone https://github.com/user/malgoro-themes
cd malgoro-themes

# Create new package
mkdir packages/new-theme

cat > packages/new-theme/PKGINFO << 'EOF'
name=malgoro-new-theme
version=1.0.0
description=New theme
EOF

mkdir -p packages/new-theme/files

# Commit
git add packages/new-theme
git commit -m "Add new-theme"
git push
```

**Users get it automatically:**
```bash
sudo malgoropkg sync
sudo malgoropkg install malgoro-new-theme
```

## Structure Template

```
my-packages/
├── README.md           # Document all packages
├── LICENSE            # Shared license
├── .gitignore         # Common ignores
├── scripts/           # Optional: shared scripts
│   └── common.sh
└── packages/          # Individual packages
    ├── package1/
    │   ├── PKGINFO    # Required
    │   ├── build.sh   # Optional
    │   └── files/     # Package files
    ├── package2/
    │   ├── PKGINFO
    │   └── files/
    └── package3/
        ├── PKGINFO
        └── files/
```

## Quick Commands

```bash
# Create multi-package repo
mkdir my-packages
cd my-packages
git init
mkdir -p packages/{pkg1,pkg2,pkg3}

# Add to MalgoroPkg
sudo malgoropkg repo-add my-packages https://github.com/user/my-packages

# Sync (discovers all packages)
sudo malgoropkg sync

# List packages from repo
malgoropkg list --available | grep my-packages

# Install any package
sudo malgoropkg install pkg1
```

## Recommended Organization

**Official Malgoro:**
```
4-5 repositories → 70+ packages

malgoro-core         (5-7 packages)
malgoro-themes       (10-15 packages)
malgoro-applications (15-25 packages)
malgoro-utilities    (10-15 packages)
malgoro-community    (50+ packages)
```

**Your Packages:**
```
1 repository → Your packages

my-malgoro-apps/
└── packages/
    ├── app1/
    ├── app2/
    └── app3/
```

## See Also

- **Detailed Examples**: [REPOSITORY_EXAMPLES.md](REPOSITORY_EXAMPLES.md)
- **Full Structure Guide**: [REPOSITORY_STRUCTURE.md](REPOSITORY_STRUCTURE.md)
- **Recommended Setup**: [RECOMMENDED_REPOS.md](RECOMMENDED_REPOS.md)
- **Package Creation**: [PACKAGE_CREATION.md](PACKAGE_CREATION.md)

---

**Key Takeaway**: Group related packages in one Git repository. MalgoroPkg finds them all automatically. Much more efficient! 🚀
