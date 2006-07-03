TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

SOURCES	+= main.cpp

FORMS	= frmPlayout.ui

IMAGES	= images/fastbackward.png \
	images/fastforward.png \
	images/pause.png \
	images/play.png \
	images/reset.png \
	images/stop.png

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}



