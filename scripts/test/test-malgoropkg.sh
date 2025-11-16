#!/bin/bash
#
# Test MalgoroPkg Installation
# Quick smoke test for MalgoroPkg
#

set -e

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}╔════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║     MalgoroPkg Test Suite                  ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════════╝${NC}"
echo ""

MALGOROPKG="${1:-malgoropkg}"
TESTS_PASSED=0
TESTS_FAILED=0

test_command() {
    echo -n "Testing: $1 ... "
    if eval "$2" > /dev/null 2>&1; then
        echo -e "${GREEN}✓ PASS${NC}"
        ((TESTS_PASSED++))
    else
        echo -e "${RED}✗ FAIL${NC}"
        ((TESTS_FAILED++))
    fi
}

# Test 1: Binary exists
test_command "malgoropkg binary exists" "command -v $MALGOROPKG"

# Test 2: Help command
test_command "malgoropkg help" "$MALGOROPKG help"

# Test 3: Version command
test_command "malgoropkg version" "$MALGOROPKG version"

# Test 4: List repositories
test_command "malgoropkg repo-list" "$MALGOROPKG repo-list"

# Test 5: List installed packages
test_command "malgoropkg list --installed" "$MALGOROPKG list --installed"

# Test 6: Configuration file exists
test_command "repository config exists" "test -f /etc/malgoro/repositories.conf || test -f ~/.config/malgoro/repositories.conf"

# Test 7: Database directory exists
test_command "database directory exists" "test -d /var/lib/malgoro || test -d ~/.local/share/malgoro"

# Summary
echo ""
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo "Tests passed: $TESTS_PASSED"
echo "Tests failed: $TESTS_FAILED"

if [ $TESTS_FAILED -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi
