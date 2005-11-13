TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

SOURCES	+= main.cpp

FORMS	= frmAdmin.ui \
	frmAdminEditNewInfo.ui

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}



