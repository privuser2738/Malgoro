#!/bin/bash
#
# Create New Package Template
# Interactive script to create a new package
#

set -e

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}╔════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║     Malgoro Package Creator                ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════════╝${NC}"
echo ""

# Get package information
read -p "Package name: " PKG_NAME
read -p "Version (default: 1.0.0): " PKG_VERSION
PKG_VERSION=${PKG_VERSION:-1.0.0}

read -p "Description: " PKG_DESC
read -p "Maintainer name: " MAINTAINER_NAME
read -p "Maintainer email: " MAINTAINER_EMAIL
read -p "License (default: GPL-3.0): " PKG_LICENSE
PKG_LICENSE=${PKG_LICENSE:-GPL-3.0}

read -p "Dependencies (comma-separated, or leave empty): " PKG_DEPENDS

echo ""
echo -e "${YELLOW}Create package in:${NC}"
echo "  1) Current directory"
echo "  2) packages/ subdirectory (for multi-package repo)"
echo "  3) Custom path"
read -p "Choice [1-3]: " CHOICE

case $CHOICE in
    1)
        PKG_DIR="$PKG_NAME"
        ;;
    2)
        PKG_DIR="packages/$PKG_NAME"
        ;;
    3)
        read -p "Custom path: " CUSTOM_PATH
        PKG_DIR="$CUSTOM_PATH"
        ;;
    *)
        echo "Invalid choice"
        exit 1
        ;;
esac

# Create directory structure
echo ""
echo -e "${GREEN}Creating package structure...${NC}"

mkdir -p "$PKG_DIR"
mkdir -p "$PKG_DIR/files/usr/bin"
mkdir -p "$PKG_DIR/files/usr/share/applications"

# Create PKGINFO
cat > "$PKG_DIR/PKGINFO" << EOF
name=$PKG_NAME
version=$PKG_VERSION
description=$PKG_DESC
maintainer=$MAINTAINER_NAME <$MAINTAINER_EMAIL>
license=$PKG_LICENSE
EOF

if [ -n "$PKG_DEPENDS" ]; then
    echo "depends=$PKG_DEPENDS" >> "$PKG_DIR/PKGINFO"
fi

# Create README
cat > "$PKG_DIR/README.md" << EOF
# $PKG_NAME

$PKG_DESC

## Installation

\`\`\`bash
malgoropkg install $PKG_NAME
\`\`\`

## Building from Source

\`\`\`bash
cd $PKG_DIR
./build.sh  # if build script exists
\`\`\`

## Version

$PKG_VERSION

## License

$PKG_LICENSE

## Maintainer

$MAINTAINER_NAME <$MAINTAINER_EMAIL>
EOF

# Create example build script
cat > "$PKG_DIR/build.sh" << 'EOF'
#!/bin/bash
#
# Build script for package
#

set -e

echo "Building package..."

# Example: C++ project with CMake
# mkdir -p build
# cd build
# cmake ../src -DCMAKE_INSTALL_PREFIX=/usr
# make

# Example: Python project
# python3 setup.py build

# Example: Simple script
# Just copy files to files/ directory

echo "Build complete!"
EOF

chmod +x "$PKG_DIR/build.sh"

# Create example .desktop file
cat > "$PKG_DIR/files/usr/share/applications/$PKG_NAME.desktop" << EOF
[Desktop Entry]
Version=1.0
Type=Application
Name=$PKG_NAME
Comment=$PKG_DESC
Exec=$PKG_NAME
Icon=$PKG_NAME
Terminal=false
Categories=Utility;
EOF

# Create example binary script
cat > "$PKG_DIR/files/usr/bin/$PKG_NAME" << EOF
#!/bin/bash
#
# $PKG_NAME - $PKG_DESC
#

echo "$PKG_NAME version $PKG_VERSION"
echo "Replace this with your application"
EOF

chmod +x "$PKG_DIR/files/usr/bin/$PKG_NAME"

# Create .gitignore
cat > "$PKG_DIR/.gitignore" << EOF
build/
*.o
*.so
*.a
*.pyc
__pycache__/
EOF

# Summary
echo ""
echo -e "${GREEN}✓ Package created successfully!${NC}"
echo ""
echo "Package structure:"
echo "  $PKG_DIR/"
echo "  ├── PKGINFO"
echo "  ├── README.md"
echo "  ├── build.sh"
echo "  ├── .gitignore"
echo "  └── files/"
echo "      └── usr/"
echo "          ├── bin/"
echo "          │   └── $PKG_NAME"
echo "          └── share/"
echo "              └── applications/"
echo "                  └── $PKG_NAME.desktop"
echo ""
echo "Next steps:"
echo "  1. Add your files to $PKG_DIR/files/"
echo "  2. Update build.sh if needed"
echo "  3. Test: malgoropkg install $PKG_DIR"
echo "  4. Commit to Git repository"
echo ""
