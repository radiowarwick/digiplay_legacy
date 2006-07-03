#include <qapplication.h>
#include "frmStudioManage.h"
#include "clockThread.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
	frmStudioManage w;
    w.show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
