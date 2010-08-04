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

inherit eutils

src_prepare() {
    epatch "${FILESDIR}/${PF}-gentoo-makefile.patch" || die "epatch failed"
    if use studio_manage || use studio_play; then
        epatch "${FILESDIR}/${PF}-gentoo-studiopostgres.patch" || die "epatch failed"
    fi
    if use dps-www; then
        epatch "${FILESDIR}/${PF}-gentoo-www.patch" || die "epatch failed"
    fi
}

src_compile() {
    if use db; then
        MAKES="${MAKES} db"
    fi
    if use dpsadmin; then
        MAKES="${MAKES} backend"
    fi
    if use studio_play; then
        MAKES="${MAKES} studio_play"
    fi
    if use studio_manage; then
        MAKES="${MAKES} studio_manage"
    fi
    if use sueplay; then
        MAKES="${MAKES} sueplay"
    fi
    if use suesched; then
        MAKES="${MAKES} suesched"
    fi
    if use playin; then
        MAKES="${MAKES} playin"
    fi

    if [ "${MAKES}" = "" ]; then
        if use dps-www; then
            einfo "Installing only www files"
        else
            eerror "No use flags set, so not building anything"
            die "Refuse to build nothing"  
        fi
    else
        einfo "Making targets:"
        einfo ${MAKES}
        cd ${PF}
        emake DPSDIR="/usr/share/dps" ${MAKES} || die "emake failed"
    fi
}

src_install() {
    SHAREDIR="/usr/share/dps"
    DOCDIR="/usr/share/doc/dps"
    insopts -v
    
    dodir ${DOCDIR}
    docinto ${DOCDIR}
    dodoc ${PF}/README ${PF}/AUTHORS
    
    if use db; then
        dodir ${DOCDIR}/examples

        insinto /etc
        doins ${PF}/share/doc/examples/digiplay.conf
        docinto ${DOCDIR}/examples
        dodoc ${PF}/share/doc/examples/digiplay.conf

        dodir ${SHAREDIR} ${SHAREDIR}/db
        insinto ${SHAREDIR}/db
        exeinto ${SHAREDIR}/db
        doexe ${PF}/share/dps/db/cleardb ${PF}/share/dps/db/dpsinstall
        doins ${PF}/share/dps/db/digiplay-data.sql
        doins ${PF}/share/dps/db/digiplay-triggers.sql ${PF}/share/dps/db/digiplay-views.sql
        doins ${PF}/share/dps/db/digiplay.sql ${PF}/share/dps/db/dpspatch
        doins ${PF}/share/dps/db/patch1.sql
    fi

    if use dpsadmin; then
        dodir ${DOCDIR}/examples
        dobin ${PF}/src/dpsadmin/dpsadmin
        insinto /etc
        doins ${PF}/share/doc/examples/digiplay.conf
        doman ${PF}/share/man/man1/dpsadmin.1.gz
        docinto ${DOCDIR}/examples
        dodoc ${PF}/share/doc/examples/digiplay.conf
        dodoc ${PF}/share/doc/examples/sample.xml
        dodoc ${PF}/share/doc/examples/sample2.xml
    fi

    if use studio_play; then
        dodir ${DOCDIR}/examples
        dodir ${SHAREDIR} ${SHAREDIR}/images

        insinto ${SHAREDIR}/images
        doins ${PF}/share/dps/images/*

        dobin ${PF}/src/studio_play/studio_play
        insinto /etc
        doins ${PF}/share/doc/examples/digiplay.conf
        doman ${PF}/share/man/man1/studio_play.1.gz
        docinto ${DOCDIR}/examples
        dodoc ${PF}/share/doc/examples/digiplay.conf
    fi

    if use studio_manage; then
        dodir ${DOCDIR}/examples

        dobin ${PF}/src/studio_manage/studio_manage
        insinto /etc
        doins ${PF}/share/doc/examples/digiplay.conf

        doman ${PF}/share/man/man1/studio_manage.1.gz
        docinto ${DOCDIR}/examples
        dodoc ${PF}/share/doc/examples/digiplay.conf
    fi

    if use sueplay; then
        dodir ${DOCDIR}/examples

        dobin ${PF}/src/sueplay/sueplay

        insinto /etc
        doins ${PF}/share/doc/examples/digiplay.conf

        docinto ${DOCDIR}/examples
        dodoc ${PF}/share/doc/examples/digiplay.conf
        doman ${PF}/share/man/man1/sueplay.1.gz
    fi

    if use suesched; then
        dodir ${DOCDIR}/examples

        dobin ${PF}/src/suesched/suesched

        insinto /etc
        doins ${PF}/share/doc/examples/digiplay.conf

        docinto ${DOCDIR}/examples
        dodoc ${PF}/share/doc/examples/digiplay.conf
        doman ${PF}/share/man/man1/suesched.1.gz
    fi

    if use playin; then
        dodir ${DOCDIR}/examples

        dobin ${PF}/src/playin/playin

        insinto /etc
        doins ${PF}/share/doc/examples/digiplay.conf

        doman ${PF}/share/man/man1/playin.1.gz

        docinto ${DOCDIR}/examples
        dodoc ${PF}/share/doc/examples/digiplay.conf
    fi
    
    if use dps-www; then
        dodir ${SHAREDIR}/www
        insinto ${SHAREDIR}/www/
        doins -r ${PF}/src/www/*
        dodir ${SHAREDIR}/www/Smarty/tmp
        fperms 0777 ${SHAREDIR}/www/Smarty/tmp
        fperms 0777 ${SHAREDIR}/www/DPS/uploads
    fi
            
}

pkg_setup() {
    if use dpsadmin; then
        enewuser dps -1 -1 -1 "adm" "-r"
    fi
}
