# Single-Package Repository Template

This is a template for creating a single-package repository for MalgoroPkg.

## When to Use Single-Package Repository

Use this template when:

- ✅ Package is large (> 50MB)
- ✅ Package updates independently
- ✅ Package has its own development cycle
- ✅ Package requires separate version control

Examples: Large applications, media editors, IDEs, games

## Structure

```
my-package/
├── README.md              # This file - describe your package
├── LICENSE                # Choose appropriate license
├── .gitignore            # Git ignore rules
├── PKGINFO               # Required package metadata
├── build.sh              # Optional build script
├── install.sh            # Optional install script
└── files/                # Files to install
    ├── usr/
    │   ├── bin/          # Executables
    │   ├── lib/          # Libraries
    │   └── share/        # Data files
    └── etc/              # Configuration files
```

## Quick Start

### 1. Clone this template

```bash
git clone <this-repo> my-package
cd my-package
rm -rf .git
git init
```

### 2. Customize PKGINFO

Edit the `PKGINFO` file with your package details:

```ini
name=my-package
version=1.0.0
description=My amazing application
maintainer=Your Name <you@example.com>
license=MIT
depends=gtk3,libpng
```

### 3. Add your files

```bash
# Add executables
mkdir -p files/usr/bin
cp my-app files/usr/bin/

# Add libraries
mkdir -p files/usr/lib
cp libmyapp.so files/usr/lib/

# Add data files
mkdir -p files/usr/share/my-package
cp -r data/* files/usr/share/my-package/
```

### 4. Test locally

```bash
malgoropkg install .
```

### 5. Publish

```bash
git add .
git commit -m "Initial package"
git remote add origin https://github.com/username/my-package
git push -u origin main
```

### 6. Use from repository

```bash
# Add to your repositories.conf:
# [my-package]
# url = https://github.com/username/my-package
# description = My amazing application

malgoropkg repo-add my-package https://github.com/username/my-package
malgoropkg sync
malgoropkg install my-package
```

## PKGINFO Fields

Required fields:

- `name` - Package name (lowercase, hyphens)
- `version` - Version string (semantic versioning recommended)
- `description` - Short description
- `maintainer` - Your name and email
- `license` - License identifier

Optional fields:

- `depends` - Comma-separated list of dependencies
- `conflicts` - Packages this conflicts with
- `provides` - Virtual packages this provides
- `replaces` - Packages this replaces

## File Locations

Standard Linux filesystem hierarchy:

- `/usr/bin/` - User executables
- `/usr/lib/` - Libraries
- `/usr/share/` - Architecture-independent data
- `/usr/share/applications/` - Desktop entries
- `/usr/share/icons/` - Icons
- `/usr/share/doc/` - Documentation
- `/etc/` - Configuration files
- `/var/` - Variable data

## Build Script

If your package needs compilation, create `build.sh`:

```bash
#!/bin/bash
set -e

# Configure
./configure --prefix=/usr

# Build
make -j$(nproc)

# Install to files/ directory
make DESTDIR="$(pwd)/files" install
```

## Documentation

- [Package Creation Guide](https://github.com/privuser2738/malgoro/docs/PACKAGE_CREATION.md)
- [Repository Structure](https://github.com/privuser2738/malgoro/docs/REPOSITORY_STRUCTURE.md)

## Support

- Issues: https://github.com/privuser2738/malgoro/issues
- Documentation: https://github.com/privuser2738/malgoro/docs
