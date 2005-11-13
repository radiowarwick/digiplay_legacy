#include "clockThread.h"

void clockThread::run() {
	time_t current_time;
	tm local;
	mutex.lock();
	stopped = FALSE;
	mutex.unlock();
	while (!stopped) {
		time(&current_time);
		local=*(localtime(&current_time));
		QString seconds = QString::number(local.tm_sec,10);
		if (seconds.length() == 1) seconds = "0" + seconds;
		QString minutes = QString::number(local.tm_min,10);
		if (minutes.length() == 1) minutes = "0" + minutes;
		QString hours = QString::number(local.tm_hour,10);
		if (hours.length() == 1) hours = "0" + hours;
		
		QCustomEvent *clockEvent = new QCustomEvent(20000);
		QCustomEvent *dateEvent = new QCustomEvent(20001);
		clockEvent->setData(new QString(hours + ":" + minutes + ":" + seconds));
		dateEvent->setData(new QString(getPrettyDate(&local)));
		QApplication::postEvent(receiver, clockEvent);
		QApplication::postEvent(receiver, dateEvent);
		sleep(1);
	}
}

void clockThread::stop() {
	mutex.lock();
	stopped = TRUE;
	mutex.unlock();
}

QString clockThread::getPrettyDate(tm *local) {
	QString date;
	switch (local->tm_wday) {
	case 0: date = "Sunday "; break;
	case 1: date = "Monday "; break;
	case 2: date = "Tuesday "; break;
	case 3: date = "Wednesday "; break;
	case 4: date = "Thursday "; break;
	case 5: date = "Friday "; break;
	case 6: date = "Saturday "; break;
	}
	date += QString::number(local->tm_mday);
	switch (local->tm_mon) {
	case 0: date += " January "; break;
	case 1: date += " February "; break;
	case 2: date += " March "; break;
	case 3: date += " April "; break;
	case 4: date += " May "; break;
	case 5: date += " June "; break;
	case 6: date += " July "; break;
	case 7: date += " August "; break;
	case 8: date += " September "; break;
	case 9: date += " October "; break;
	case 10: date += " November "; break;
	case 11: date += " December "; break;
	}
	date += QString::number(local->tm_year + 1900);
	return date;
}
// END ClockThread ========================================
