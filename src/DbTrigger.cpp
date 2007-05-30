#include "DbTrigger.h"

//DbTrigger::DbTrigger(QWidget* parent, const char* name, std::string trigger) 
DbTrigger::DbTrigger(const char* name, std::string trigger) 
        : pqxx::trigger(*C,trigger) {

}

DbTrigger::~DbTrigger() throw() {
    stop();
}

void DbTrigger::operator()(int be_pid) {
    cout << "Triggered" << endl;
    emit trigger();
}

void DbTrigger::run() {
    enabled = true;
    while (enabled) {
        usleep(100000);
        C->get_notifs();
    }
}

void DbTrigger::stop() {
    enabled = false;
}

