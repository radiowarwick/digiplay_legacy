#include "DbTrigger.h"
#include "DataAccess.h"

Connection* DbTrigger::Ctrig = 0;
bool DbTrigger::init = false;

DbTrigger::DbTrigger(const char* name, std::string trigger){ 
    if (!init) {
        try {
            Ctrig = new Connection( DataAccess::getConnectionString() );
            init = true;
        }
        catch (...) {
            cout << "DbTrigger::";
            cout << "An error occured while trying to connect to DB" << endl;
            throw;
        }
    }
    trigname = trigger;
    Trig = new DbPqxxTrigger(name, Ctrig, trigger);
    connect(Trig,SIGNAL(trigger()),this,SLOT(triggered()));
}

DbTrigger::~DbTrigger() throw() {
    stop();
}

void DbTrigger::triggered() {
    cout << "DbTrigger '" << trigname << "' triggered" << endl;
    emit trigger();
}

void DbTrigger::run() {
    cout << "Running trigger" << endl;
    enabled = true;
    while (enabled) {
        usleep(100000);
        Ctrig->get_notifs();
    }
}

void DbTrigger::stop() {
    enabled = false;
}

// =================================
DbPqxxTrigger::DbPqxxTrigger(const char* name, Connection * C, 
    std::string trigger) : pqxx::trigger(*C, trigger) {

}

DbPqxxTrigger::~DbPqxxTrigger() throw() {

}

void DbPqxxTrigger::operator()(int be_pid) {
    emit trigger();
}

