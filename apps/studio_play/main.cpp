#include <qapplication.h>
#include <qstring.h>
#include "frmPlayout.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    frmPlayout w;
    w.show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
