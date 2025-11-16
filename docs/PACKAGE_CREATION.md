# Creating Packages for MalgoroPkg

This guide explains how to create packages for the MalgoroPkg system.

## Important: Multi-Package Repositories

**Key Concept**: A single Git repository can contain **multiple packages**!

This means you can group related packages together:
- Reduces number of repositories to manage
- Shares common resources and build scripts
- More efficient use of Git resources
- Easier maintenance

**See detailed examples**: [REPOSITORY_EXAMPLES.md](REPOSITORY_EXAMPLES.md)
**See structure guide**: [REPOSITORY_STRUCTURE.md](REPOSITORY_STRUCTURE.md)

## Repository Options

### Option 1: Multi-Package Repository (Recommended)

**Best for**: Small to medium packages, related packages, theme collections

```
my-packages/
├── README.md
├── LICENSE
└── packages/
    ├── app1/
    │   ├── PKGINFO
    │   └── files/
    ├── app2/
    │   ├── PKGINFO
    │   └── files/
    └── app3/
        ├── PKGINFO
        └── files/
```

**Advantages:**
- ✅ Fewer repositories to manage
- ✅ Share common resources
- ✅ Group related packages
- ✅ Efficient Git usage

### Option 2: Single-Package Repository

**Best for**: Large packages (>50MB), complex applications

```
my-app/
├── README.md
├── PKGINFO
├── build.sh
└── files/
    └── ... (package files)
```

**Use when:**
- Package is very large
- Complex build process
- Flagship application
- Frequently updated separately

## Package Repository Structure (Multi-Package)

```
my-package-repo/
├── README.md
├── LICENSE
├── .gitignore
├── scripts/              # Optional: shared build scripts
│   └── common.sh
└── packages/
    ├── my-app/
    │   ├── PKGINFO
    │   ├── build.sh (optional)
    │   ├── install.sh (optional)
    │   └── files/
    │       └── ... (package files)
    └── another-app/
        ├── PKGINFO
        └── files/
            └── ...
```

**MalgoroPkg automatically discovers all packages in the `packages/` directory!**

## PKGINFO Format

The `PKGINFO` file contains package metadata:

```ini
name=my-application
version=1.2.3
description=A short description of the package
maintainer=Your Name <your.email@example.com>
license=GPL-3.0
depends=dependency1,dependency2,dependency3
conflicts=conflicting-package
provides=virtual-package
```

### Required Fields

- `name`: Package name (lowercase, no spaces)
- `version`: Semantic version (e.g., 1.0.0)
- `description`: Brief package description

### Optional Fields

- `maintainer`: Package maintainer information
- `license`: Software license (SPDX identifier preferred)
- `depends`: Comma-separated list of dependencies
- `conflicts`: Packages that conflict with this one
- `provides`: Virtual packages this provides

## Package Files

Place all package files in the `files/` directory:

```
files/
├── usr/
│   ├── bin/
│   │   └── my-app
│   └── share/
│       ├── applications/
│       │   └── my-app.desktop
│       └── doc/
│           └── my-app/
│               └── README.md
└── etc/
    └── my-app/
        └── config.conf
```

Files will be installed to their corresponding system locations.

## Build Scripts (Optional)

If your package needs to be compiled, create a `build.sh` script:

```bash
#!/bin/bash
set -e

# Build script for my-application

echo "Building my-application..."

# Example: C++ project
cd src
g++ -o ../files/usr/bin/my-app main.cpp -O2

echo "Build complete!"
```

Make it executable:
```bash
chmod +x build.sh
```

## Install Scripts (Optional)

For post-installation tasks, create `install.sh`:

```bash
#!/bin/bash

# Post-installation script

echo "Setting up my-application..."

# Create user data directory
mkdir -p /var/lib/my-app

# Set permissions
chmod 755 /usr/bin/my-app

echo "Setup complete!"
```

## Example: Simple Application Package

### Directory Structure

```
packages/hello-malgoro/
├── PKGINFO
└── files/
    └── usr/
        └── bin/
            └── hello-malgoro
```

### PKGINFO

```ini
name=hello-malgoro
version=1.0.0
description=Hello World application for Malgoro
maintainer=Malgoro Team <team@malgoro.org>
license=MIT
```

### files/usr/bin/hello-malgoro

```bash
#!/bin/bash
echo "Hello from Malgoro!"
```

## Example: Application with Dependencies

### PKGINFO

```ini
name=advanced-editor
version=2.5.1
description=Advanced text editor with syntax highlighting
maintainer=Developer <dev@example.com>
license=GPL-3.0
depends=python3,python-pygments,gtk3
conflicts=basic-editor
provides=text-editor
```

## Example: Library Package

### Directory Structure

```
packages/libawesome/
├── PKGINFO
├── build.sh
└── src/
    ├── awesome.cpp
    └── awesome.h
```

### PKGINFO

```ini
name=libawesome
version=3.0.0
description=Awesome library for doing awesome things
maintainer=Library Author <author@example.com>
license=BSD-3-Clause
```

### build.sh

```bash
#!/bin/bash
set -e

echo "Building libawesome..."

mkdir -p files/usr/lib
mkdir -p files/usr/include

cd src
g++ -shared -fPIC -o ../files/usr/lib/libawesome.so.3.0.0 awesome.cpp
cp awesome.h ../files/usr/include/

cd ../files/usr/lib
ln -s libawesome.so.3.0.0 libawesome.so.3
ln -s libawesome.so.3 libawesome.so

echo "Build complete!"
```

## Creating a Package Repository

1. Create a Git repository:

```bash
mkdir my-packages
cd my-packages
git init
```

2. Create the packages directory:

```bash
mkdir packages
```

3. Add your first package:

```bash
mkdir -p packages/my-app/files/usr/bin
echo '#!/bin/bash' > packages/my-app/files/usr/bin/my-app
echo 'echo "Hello!"' >> packages/my-app/files/usr/bin/my-app
chmod +x packages/my-app/files/usr/bin/my-app

cat > packages/my-app/PKGINFO << EOF
name=my-app
version=1.0.0
description=My first package
maintainer=Me <me@example.com>
license=MIT
EOF
```

4. Commit and push:

```bash
git add .
git commit -m "Add my-app package"
git push origin main
```

5. Add repository to MalgoroPkg:

```bash
sudo malgoropkg repo-add my-packages https://github.com/username/my-packages
sudo malgoropkg sync
```

6. Install your package:

```bash
sudo malgoropkg install my-app
```

## Best Practices

### Naming Conventions

- Use lowercase names
- Use hyphens for word separation
- Avoid special characters
- Be descriptive but concise

Good examples:
- `python-requests`
- `my-text-editor`
- `libawesome-dev`

Bad examples:
- `MyTextEditor` (uppercase)
- `text_editor` (underscores)
- `editor!!!` (special characters)

### Versioning

Use semantic versioning (MAJOR.MINOR.PATCH):

- `1.0.0` - Initial release
- `1.0.1` - Bug fixes
- `1.1.0` - New features (backwards compatible)
- `2.0.0` - Breaking changes

### Dependencies

- List all runtime dependencies
- Don't include build-time dependencies in `depends`
- Use exact package names from repositories
- Order dependencies logically

### File Organization

- Follow Filesystem Hierarchy Standard (FHS)
- Place binaries in `/usr/bin`
- Place libraries in `/usr/lib`
- Place headers in `/usr/include`
- Place configuration in `/etc`
- Place data in `/usr/share`

### Build Scripts

- Use `set -e` to exit on errors
- Echo progress messages
- Clean up temporary files
- Validate build outputs

### Testing

Before publishing:

1. Test package installation:
   ```bash
   malgoropkg install my-package
   ```

2. Test functionality:
   ```bash
   my-app --version
   ```

3. Test removal:
   ```bash
   malgoropkg remove my-package
   ```

4. Verify no leftover files

## Advanced Topics

### Conditional Dependencies

Use shell scripts to check for optional dependencies:

```bash
# In install.sh
if command -v python3 &> /dev/null; then
    echo "Python support enabled"
fi
```

### Multiple Architectures

Create separate packages or use build scripts that detect architecture:

```bash
# In build.sh
ARCH=$(uname -m)

if [ "$ARCH" = "x86_64" ]; then
    # Build for x86_64
    gcc -m64 ...
elif [ "$ARCH" = "aarch64" ]; then
    # Build for ARM64
    gcc -march=armv8-a ...
fi
```

### Package Splitting

For large applications, split into multiple packages:

- `myapp` - Main application
- `myapp-docs` - Documentation
- `myapp-dev` - Development files
- `myapp-plugins` - Optional plugins

## Publishing

1. Create a GitHub repository
2. Organize packages as described
3. Push to GitHub
4. Add to MalgoroPkg repository list
5. Share repository URL with users

## Example Repository

See the official Malgoro package repository for examples:

https://github.com/privuser2738/malgoro-core

## Getting Help

- Documentation: https://github.com/privuser2738/malgoro/docs
- Issues: https://github.com/privuser2738/malgoro/issues
- Community: [To be established]
