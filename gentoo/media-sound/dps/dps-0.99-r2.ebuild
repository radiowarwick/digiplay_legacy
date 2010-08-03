# Copyright 1999-2010 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

DESCRIPTION="Radio Warwick's Digiplay digital playout system"
HOMEPAGE="http://www.broadcastsoftware.org"
SRC_URI="http://oss.livewire1350.com/${PF}.tar.gz"

LICENSE="GPL-2"
SLOT="0"
KEYWORDS="x86"
IUSE="db dpsadmin dps-www studio_play studio_manage sueplay suesched playin"
EAPI="2"

RDEPEND="
    db? (
        dev-db/postgresql-server
        app-office/tedia2sql
    )
    dpsadmin? (
        dev-libs/libpqxx
        net-nds/openldap
    )
    studio_play? (
        media-sound/jack-audio-connection-kit
        media-libs/alsa-lib
        media-libs/flac
        media-sound/mpg123
        dev-libs/libpqxx
        =x11-libs/qt-3.3.8b-r2
    )
    studio_manage? (
        =x11-libs/qt-3.3.8b-r2
        dev-libs/libpqxx
        net-nds/openldap
    )
    sueplay? ( 
        media-sound/jack-audio-connection-kit
        dev-libs/libpqxx
        media-libs/alsa-lib
        media-libs/flac
        media-sound/mpg123
    )
    suesched? ( dev-libs/libpqxx )
    playin? (
        dev-libs/libpqxx
        media-sound/cdparanoia
    )"
DEPEND="${RDEPEND}"

src_prepare() {
    epatch "${FILESDIR}/${PF}-gentoo-makefile.patch"
    if use studio_manage || use studio_play; then
        epatch "${FILESDIR}/${PF}-gentoo-studiopostgres.patch"
    fi
    if use dps-www; then
        epatch "${FILESDIR}/${PF}-gentoo-www.patch"
    fi
}

src_compile() {
    MAKES="
        db? ( db )
        dpsadmin? ( backend )
        studio_play? ( studio_play )
        studio_manage? ( studio_manage )
        sueplay? ( sueplay )
        suesched? ( suesched )
        playin? ( playin )
    "
    emake ${MAKES} || die "emake failed"
}

src_install() {
    einfo "Not installing as this is in development!"
}
