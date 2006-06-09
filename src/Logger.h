#ifndef CLASS_LOGGER_H
#define CLASS_LOGGER_H

#ifndef APP_NAME
#error "Logger:: Must define APP_NAME for this application to use Logger!"
#endif

#include <string>
#include <fstream>
using namespace std;

class Logger
{
	public:

		static Logger& log() {
			static Logger logger("./" APP_NAME ".log");
			return logger;
		}
		void write(string srcObject, string srcMethod, string srcMessage);

		~Logger();

	private:
		Logger(string filename);
		Logger(const Logger&);
		Logger& operator=(const Logger&);

		ofstream* logFile;
};

#endif
