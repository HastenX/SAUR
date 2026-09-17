pkgname="saur"
pkgdesc="Safe AUR package Manager :3"

pkgver="1.0.0"
pkgrel="1"

arch=("x86_64")
license=("MIT")

source=("bin/main")
sha256sum=("b2")

package() {
    pacman -Qqm > "${pkgdir}/PKGLIST" 
    mkdir -p ${pkgdir/usr/share}
    cp "${pkgdir}/src/main" "${srcdir}/usr/share/saur" 
        
    chmod +x "${srcdir}/usr/share/saur"
}


