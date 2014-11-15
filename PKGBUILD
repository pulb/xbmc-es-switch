# Maintainer: Patrick Ulbrich <zulu99 at gmx . net>

pkgname=xbmc-es-switch
pkgver=0.1.0
pkgrel=1
pkgdesc="A small utility that switches between XBMC and Emulationstation at boottime via joypad button press"
arch=('i686' 'x86_64' 'armv6h' 'armv7h')
url="https://github.com/pulb/xbmc-es-button-switch"
license=('GPL')
depends=('xbmc' 'emulationstation')
source=('https://github.com/pulb/xbmc-es-switch/archive/v0.1.0.tar.gz')
md5sums=('34c9c68e2a09ce862b60b1d03d4e38e4')

build() {
	cd ${srcdir}/${pkgname}-${pkgver}
	make
}

package() {
	cd ${srcdir}/${pkgname}-${pkgver}
	make prefix="$pkgdir"/usr install
 	install -D -m644 LICENSE "${pkgdir}/usr/share/licenses/${pkgname}/LICENSE"
}
