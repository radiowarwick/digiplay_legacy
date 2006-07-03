#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include <qapplication.h>
#include "frmAdmin.h"

int main( int argc, char ** argv )
{    
    QApplication a( argc, argv );
    frmAdmin w;
    w.show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
