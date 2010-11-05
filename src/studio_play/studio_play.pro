TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

SOURCES	+= main.cpp

#The following line was changed from FORMS to FORMS3 by qt3to4
FORMS3	= frmPlayout.ui

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



#The following line was inserted by qt3to4
QT +=  qt3support 
#The following line was inserted by qt3to4
CONFIG += uic3

#The following line was inserted by qt3to4
QT +=  
