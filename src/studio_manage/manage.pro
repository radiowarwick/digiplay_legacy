TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

SOURCES	+= main.cpp

FORMS	= frmStudioManage.ui

IMAGES	= images/bin.bmp \
	images/dir_audio.bmp \
	images/dir_folder.bmp \
	images/logo.bmp

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}


