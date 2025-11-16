# Multi-Package Repository Template

This is a template for creating a multi-package repository for MalgoroPkg.

## Structure

```
my-packages/
├── README.md              # This file - describe your packages
├── LICENSE                # Choose appropriate license
├── .gitignore            # Git ignore rules
├── scripts/              # Optional: shared build scripts
│   └── common.sh
└── packages/             # Individual packages
    ├── package1/
    │   ├── PKGINFO       # Required package metadata
    │   ├── README.md     # Package documentation
    │   ├── build.sh      # Optional build script
    │   └── files/        # Files to install
    │       └── usr/
    │           └── bin/
    ├── package2/
    │   ├── PKGINFO
    │   └── files/
    └── package3/
        ├── PKGINFO
        └── files/
```

## Quick Start

### 1. Clone this template

```bash
git clone <this-repo> my-packages
cd my-packages
rm -rf .git
git init
```

### 2. Customize

Edit `README.md`, `LICENSE`, and add your packages in `packages/`

### 3. Create a package

```bash
mkdir -p packages/my-app
cat > packages/my-app/PKGINFO << EOF
name=my-app
version=1.0.0
description=My application
maintainer=Your Name <you@example.com>
license=MIT
EOF

mkdir -p packages/my-app/files/usr/bin
# Add your files...
```

### 4. Test locally

```bash
malgoropkg install packages/my-app
```

### 5. Publish

```bash
git add .
git commit -m "Initial packages"
git remote add origin https://github.com/username/my-packages
git push -u origin main
```

### 6. Use from repository

```bash
malgoropkg repo-add my-packages https://github.com/username/my-packages
malgoropkg sync
malgoropkg install my-app
```

## Guidelines

### When to use multi-package repository:

✅ **DO use for:**
- Related packages (all your apps, all themes, etc.)
- Small to medium packages (< 10MB each)
- 5-20 packages per repository
- Packages by same maintainer

❌ **DON'T use for:**
- Large packages (> 50MB)
- Unrelated packages
- Packages updated independently

### Package naming:

- Use lowercase
- Use hyphens for word separation
- Be descriptive but concise

Good: `my-text-editor`, `blue-theme`, `backup-tool`
Bad: `MyTextEditor`, `theme1`, `stuff`

### Dependencies:

List all runtime dependencies in PKGINFO:

```ini
depends=gtk3,libpulse,dbus
```

## Examples

See the official Malgoro repositories for examples:

- https://github.com/privuser2738/malgoro-core
- https://github.com/privuser2738/malgoro-themes
- https://github.com/privuser2738/malgoro-applications

## Documentation

- [Package Creation Guide](https://github.com/privuser2738/malgoro/docs/PACKAGE_CREATION.md)
- [Repository Structure](https://github.com/privuser2738/malgoro/docs/REPOSITORY_STRUCTURE.md)
- [Multi-Package Quick Start](https://github.com/privuser2738/malgoro/docs/MULTI_PACKAGE_QUICKSTART.md)

## Support

- Issues: https://github.com/privuser2738/malgoro/issues
- Documentation: https://github.com/privuser2738/malgoro/docs
