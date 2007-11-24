#include "QtTrigger.h"

QtTrigger::QtTrigger(const char* name, std::string trigger)
		: Trigger(trigger) {
			
}

QtTrigger::~QtTrigger() throw() {
	
}

void QtTrigger::operator()(int be_pid) {
	emit trigger();	
}
