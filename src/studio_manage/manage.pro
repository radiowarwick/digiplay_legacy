TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

SOURCES	+= main.cpp

FORMS	= frmStudioManage.ui \
	dlgLogin.ui \
	dlgWarn.ui

IMAGES	= images/logo.bmp \
	images/logo.png

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}


