#!/bin/bash
#
# Install Malgoro System-Wide
# Must be run as root
#

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
BUILD_DIR="${BUILD_DIR:-build}"

echo -e "${BLUE}╔════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║     Malgoro Installer                      ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════════╝${NC}"
echo ""

# Check root
if [ "$EUID" -ne 0 ]; then
    echo -e "${RED}Error: This script must be run as root${NC}"
    echo "Usage: sudo $0"
    exit 1
fi

print_success() {
    echo -e "${GREEN}✓${NC} $1"
}

print_error() {
    echo -e "${RED}✗${NC} $1"
}

print_section() {
    echo ""
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${BLUE}  $1${NC}"
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
}

# Install MalgoroPkg
print_section "Installing MalgoroPkg"

cd "$PROJECT_ROOT/MalgoroPkg/$BUILD_DIR"

if [ ! -f "malgoropkg" ]; then
    print_error "MalgoroPkg not built. Run build-all.sh first."
    exit 1
fi

make install || { print_error "Installation failed"; exit 1; }
print_success "MalgoroPkg installed to /usr/bin/malgoropkg"

# Create system directories
print_section "Creating System Directories"

mkdir -p /var/lib/malgoro/packages
mkdir -p /var/cache/malgoro
mkdir -p /etc/malgoro

print_success "System directories created"

# Install configuration
if [ ! -f /etc/malgoro/repositories.conf ]; then
    cp "$PROJECT_ROOT/config/repositories.conf" /etc/malgoro/
    print_success "Installed default repository configuration"
else
    print_success "Repository configuration already exists"
fi

# Install MalgoroDE (if built)
if [ -f "$PROJECT_ROOT/MalgoroDE/$BUILD_DIR/src/wm/malgoro-wm" ]; then
    print_section "Installing MalgoroDE"

    cd "$PROJECT_ROOT/MalgoroDE/$BUILD_DIR"
    make install || { print_error "Installation failed"; exit 1; }

    print_success "MalgoroDE installed"
else
    echo ""
    echo -e "${YELLOW}Note: MalgoroDE not built, skipping${NC}"
fi

# Summary
print_section "Installation Complete"

echo ""
echo -e "${GREEN}Malgoro has been installed successfully!${NC}"
echo ""
echo "Installed components:"
echo "  • malgoropkg - Package manager"
echo "  • Configuration: /etc/malgoro/repositories.conf"
echo "  • Database: /var/lib/malgoro/packages.db"
echo "  • Cache: /var/cache/malgoro/"
echo ""

if [ -f /usr/bin/malgoro-wm ]; then
    echo "  • malgoro-wm - Window manager"
    echo "  • malgoro-panel - Desktop panel"
    echo "  • malgoro-session - Session manager"
    echo ""
fi

echo "Next steps:"
echo ""
echo "1. Sync package repositories:"
echo "   sudo malgoropkg sync"
echo ""

if [ -f /usr/bin/malgoro-wm ]; then
    echo "2. Start Malgoro Desktop:"
    echo "   Select 'Malgoro Desktop' from your display manager"
    echo "   Or run: malgoro-session"
    echo ""
else
    echo "2. Install Malgoro Desktop Environment:"
    echo "   sudo malgoropkg install malgoro-session"
    echo ""
fi

echo "3. View available packages:"
echo "   malgoropkg list --available"
echo ""
echo "4. Install packages:"
echo "   sudo malgoropkg install <package-name>"
echo ""
