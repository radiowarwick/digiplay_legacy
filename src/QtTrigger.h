#ifndef CLASS_QTTRIGGER
#define CLASS_QTTRIGGER

#include <string>

#include <QtCore/QObject>
#include <QtGui/QApplication>

#include "DbTrigger.h"

class QtTrigger		: 	public QObject,
						public Trigger {
	Q_OBJECT
	
	public:
		QtTrigger(const char* name, std::string trigger);
		~QtTrigger() throw();
	
	signals:
		void trigger();
			
	private:
		void operator()(int be_pid);
		
};

#endif
