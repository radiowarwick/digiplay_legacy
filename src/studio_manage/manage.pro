TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

SOURCES	+= main.cpp

FORMS	= frmStudioManage.ui \
	dlgLogin.ui \
	dlgWarn.ui

IMAGES	= images/bin.bmp \
	images/dir_audio.bmp \
	images/dir_folder.bmp \
	images/email_new.bmp \
	images/email_old.bmp \
	images/logo.bmp \
	images/logo.png \
	images/sp_album.bmp \
	images/sp_artist.bmp \
	images/sp_audio.bmp

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}


