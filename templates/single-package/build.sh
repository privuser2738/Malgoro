#!/bin/bash
#
# Build script template
# Replace this with your actual build process
#

set -e

PACKAGE_NAME="my-package"
VERSION="1.0.0"

echo "Building ${PACKAGE_NAME} ${VERSION}..."

# Example build steps - replace with your actual build:

# 1. Clean previous build
echo "Cleaning previous build..."
rm -rf build/
mkdir -p build/

# 2. Configure
echo "Configuring..."
# ./configure --prefix=/usr
# cmake -B build -DCMAKE_INSTALL_PREFIX=/usr

# 3. Build
echo "Building..."
# make -C build -j$(nproc)
# cmake --build build --parallel

# 4. Run tests (optional)
echo "Running tests..."
# make -C build test
# ctest --test-dir build

# 5. Install to files/ directory (staging)
echo "Installing to staging directory..."
mkdir -p files/usr/bin
# make -C build DESTDIR="$(pwd)/files" install
# cmake --install build --prefix "$(pwd)/files/usr"

# Copy your built files
# cp build/my-app files/usr/bin/

echo "✓ Build completed successfully"
echo ""
echo "To install locally:"
echo "  malgoropkg install ."
echo ""
echo "To test the package:"
echo "  ./files/usr/bin/${PACKAGE_NAME}"
