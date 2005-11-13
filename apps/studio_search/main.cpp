#include <qapplication.h>
#include "frmSearch.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    frmSearch w;
    w.show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
