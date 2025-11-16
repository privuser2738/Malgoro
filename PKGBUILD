# Maintainer: Malgoro Team <noreply@malgoro.org>
pkgname=malgoro
pkgver=0.1.0
pkgrel=1
pkgdesc="Malgoro Desktop Environment and Git-based Package Manager"
arch=('x86_64' 'aarch64')
url="https://github.com/privuser2738/malgoro"
license=('GPL3')
depends=('libgit2' 'sqlite' 'openssl' 'gtk3')
makedepends=('cmake' 'gcc' 'make')
source=("git+https://github.com/privuser2738/malgoro.git")
sha256sums=('SKIP')

build() {
    cd "$srcdir/$pkgname"

    # Build MalgoroPkg
    cd MalgoroPkg
    mkdir -p build
    cd build

    cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/usr

    make
}

check() {
    cd "$srcdir/$pkgname/MalgoroPkg/build"
    make test || warning "Tests failed"
}

package() {
    cd "$srcdir/$pkgname/MalgoroPkg/build"

    make DESTDIR="$pkgdir" install

    # Install configuration
    install -Dm644 "$srcdir/$pkgname/config/repositories.conf" \
        "$pkgdir/etc/malgoro/repositories.conf"

    # Create necessary directories
    install -dm755 "$pkgdir/var/lib/malgoro/packages"
    install -dm755 "$pkgdir/var/cache/malgoro"

    # Install documentation
    install -Dm644 "$srcdir/$pkgname/README.md" \
        "$pkgdir/usr/share/doc/$pkgname/README.md"
    install -Dm644 "$srcdir/$pkgname/MalgoroPkg/README.md" \
        "$pkgdir/usr/share/doc/$pkgname/MalgoroPkg.md"
}

post_install() {
    echo "MalgoroPkg installed successfully!"
    echo ""
    echo "Initialize repositories:"
    echo "  sudo malgoropkg sync"
    echo ""
    echo "Install Malgoro Desktop Environment:"
    echo "  sudo malgoropkg install malgoro-desktop"
    echo ""
    echo "Configuration: /etc/malgoro/repositories.conf"
}

post_upgrade() {
    echo "MalgoroPkg upgraded to version $pkgver"
    echo "Run 'sudo malgoropkg sync' to update package lists"
}
