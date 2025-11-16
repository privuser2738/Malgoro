#!/bin/bash
#
# Validate Package Structure
# Checks if a package follows Malgoro standards
#

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

PACKAGE_DIR="${1:-.}"

echo -e "${BLUE}╔════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║     Malgoro Package Validator              ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════════╝${NC}"
echo ""
echo "Validating: $PACKAGE_DIR"
echo ""

ERRORS=0
WARNINGS=0

print_pass() {
    echo -e "${GREEN}✓${NC} $1"
}

print_fail() {
    echo -e "${RED}✗${NC} $1"
    ((ERRORS++))
}

print_warn() {
    echo -e "${YELLOW}⚠${NC} $1"
    ((WARNINGS++))
}

# Check PKGINFO exists
if [ ! -f "$PACKAGE_DIR/PKGINFO" ]; then
    print_fail "PKGINFO file not found"
else
    print_pass "PKGINFO file exists"

    # Validate PKGINFO contents
    echo ""
    echo "Checking PKGINFO fields..."

    check_field() {
        if grep -q "^$1=" "$PACKAGE_DIR/PKGINFO"; then
            VALUE=$(grep "^$1=" "$PACKAGE_DIR/PKGINFO" | cut -d'=' -f2-)
            if [ -z "$VALUE" ]; then
                print_fail "$1 is empty"
            else
                print_pass "$1: $VALUE"
            fi
        else
            if [ "$2" = "required" ]; then
                print_fail "$1 field missing (required)"
            else
                print_warn "$1 field missing (recommended)"
            fi
        fi
    }

    check_field "name" "required"
    check_field "version" "required"
    check_field "description" "required"
    check_field "maintainer" "recommended"
    check_field "license" "recommended"
    check_field "depends" "optional"
fi

# Check files directory
echo ""
echo "Checking package files..."

if [ ! -d "$PACKAGE_DIR/files" ]; then
    print_warn "files/ directory not found"
else
    print_pass "files/ directory exists"

    # Check if files directory has content
    if [ -z "$(ls -A "$PACKAGE_DIR/files" 2>/dev/null)" ]; then
        print_warn "files/ directory is empty"
    else
        FILE_COUNT=$(find "$PACKAGE_DIR/files" -type f | wc -l)
        print_pass "Contains $FILE_COUNT file(s)"
    fi

    # Check common directories
    if [ -d "$PACKAGE_DIR/files/usr/bin" ]; then
        BIN_COUNT=$(find "$PACKAGE_DIR/files/usr/bin" -type f 2>/dev/null | wc -l)
        if [ "$BIN_COUNT" -gt 0 ]; then
            print_pass "Contains $BIN_COUNT binary/script(s)"

            # Check executables
            find "$PACKAGE_DIR/files/usr/bin" -type f | while read -r file; do
                if [ ! -x "$file" ]; then
                    print_warn "$(basename "$file") is not executable"
                fi
            done
        fi
    fi

    if [ -d "$PACKAGE_DIR/files/usr/share/applications" ]; then
        DESKTOP_COUNT=$(find "$PACKAGE_DIR/files/usr/share/applications" -name "*.desktop" | wc -l)
        if [ "$DESKTOP_COUNT" -gt 0 ]; then
            print_pass "Contains $DESKTOP_COUNT .desktop file(s)"
        fi
    fi
fi

# Check build script
echo ""
echo "Checking optional files..."

if [ -f "$PACKAGE_DIR/build.sh" ]; then
    print_pass "build.sh exists"
    if [ ! -x "$PACKAGE_DIR/build.sh" ]; then
        print_warn "build.sh is not executable"
    fi
else
    print_pass "build.sh not present (optional)"
fi

if [ -f "$PACKAGE_DIR/README.md" ]; then
    print_pass "README.md exists"
else
    print_warn "README.md not found (recommended)"
fi

# Check for common issues
echo ""
echo "Checking for common issues..."

# Check for hidden files in files/
HIDDEN_COUNT=$(find "$PACKAGE_DIR/files" -name ".*" 2>/dev/null | wc -l)
if [ "$HIDDEN_COUNT" -gt 0 ]; then
    print_warn "Found $HIDDEN_COUNT hidden file(s) in files/"
fi

# Check for build artifacts
if [ -d "$PACKAGE_DIR/files/build" ]; then
    print_warn "files/build directory found (should not be in package)"
fi

if find "$PACKAGE_DIR/files" -name "*.o" 2>/dev/null | grep -q .; then
    print_warn "Object files (.o) found in files/"
fi

# Check file sizes
if [ -d "$PACKAGE_DIR/files" ]; then
    TOTAL_SIZE=$(du -sb "$PACKAGE_DIR/files" 2>/dev/null | cut -f1)
    SIZE_MB=$((TOTAL_SIZE / 1024 / 1024))

    if [ "$SIZE_MB" -gt 50 ]; then
        print_warn "Package size is ${SIZE_MB}MB (consider single-package repo)"
    elif [ "$SIZE_MB" -gt 10 ]; then
        print_pass "Package size: ${SIZE_MB}MB (medium)"
    else
        print_pass "Package size: ${SIZE_MB}MB (small)"
    fi
fi

# Summary
echo ""
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

if [ $ERRORS -eq 0 ] && [ $WARNINGS -eq 0 ]; then
    echo -e "${GREEN}✓ Package validation passed!${NC}"
    echo ""
    echo "Package is ready for distribution."
    exit 0
elif [ $ERRORS -eq 0 ]; then
    echo -e "${YELLOW}⚠ Package validation passed with $WARNINGS warning(s)${NC}"
    echo ""
    echo "Package is functional but has some recommendations."
    exit 0
else
    echo -e "${RED}✗ Package validation failed!${NC}"
    echo ""
    echo "Errors: $ERRORS"
    echo "Warnings: $WARNINGS"
    echo ""
    echo "Please fix the errors before distributing this package."
    exit 1
fi
