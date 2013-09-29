#include <unistd.h>
#include "Logger.h"
#include "DataAccess.h"

#include "DbTrigger.h"

/*
 * TriggerRoot
 */
 
pqxx::connection* TriggerRoot::Ctrig = 0;
unsigned int TriggerRoot::instanceCount = 0;
 
TriggerRoot::TriggerRoot() {
	const char* routine = "TriggerRoot::TriggerRoot";
	
	++(TriggerRoot::instanceCount);
    if (TriggerRoot::instanceCount == 1) {
        try {
        	Ctrig = new pqxx::connection( DataAccess::getConnectionString() );
        }
        catch (const std::exception &e) {
        	L_ERROR(LOG_DB,e.what());
        	throw -1;
        }
        enabled = true;
		threadStart();
    }
}

TriggerRoot::~TriggerRoot() throw() {
	--(TriggerRoot::instanceCount);
	if (TriggerRoot::instanceCount == 0) {
		threadKill();
		threadWait();
		delete Ctrig;
	}
}

void TriggerRoot::threadExecute() {
	while (enabled) {
		Ctrig->get_notifs();
		usleep(10000);
	}
}


/*
 * Trigger
 */
Trigger::Trigger(std::string trigger) 
		: TriggerRoot(), pqxx::trigger(*Ctrig, trigger) {
	
}

Trigger::~Trigger() throw() {
	
}


/*
pqxx::connection* DbTrigger::Ctrig = 0;
unsigned int DbTrigger::instanceCount = 0;

DbTrigger::DbTrigger(const char* name, std::string trigger){ 
    const char* routine = "DbTrigger::DbTrigger";

	++(DbTrigger::instanceCount);
    if (DbTrigger::instanceCount == 1) {
        try {
            Ctrig = new pqxx::connection( DataAccess::getConnectionString() );
        }
        catch (const std::exception &e) {
            L_ERROR(LOG_DB,e.what());
            throw;
        }
    }
    trigname = trigger;
    Trig = new DbPqxxTrigger(name, Ctrig, trigger);
    connect(Trig,SIGNAL(trigger()),this,SLOT(triggered()));
}

DbTrigger::~DbTrigger() throw() {
    stop();
	--(DbTrigger::instanceCount);
	if (DbTrigger::instanceCount == 0) {
		delete Ctrig;
	}
}

void DbTrigger::triggered() {
    emit trigger();
}

void DbTrigger::run() {
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
DbPqxxTrigger::DbPqxxTrigger(const char* name, pqxx::connection * C, 
    std::string trigger) : pqxx::trigger(*C, trigger) {

}

DbPqxxTrigger::~DbPqxxTrigger() throw() {

}

void DbPqxxTrigger::operator()(int be_pid) {
    emit trigger();
}

*/
