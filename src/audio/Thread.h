#ifndef CLASS_THREAD
#define CLASS_THREAD

#include <vector>
using namespace std;

#include "pthread.h"

#ifndef ENUM_MESSAGE
#define ENUM_MESSAGE
//#pragma message( No thread messages defined! )
enum MESSAGE { NONE=0,
				STOP=1
			};
#endif

class Thread {
	public:
        Thread();
		virtual ~Thread() = 0;

	protected:
		int threadStart();
		virtual void threadExecute() =0;
		void threadSend(int m);
		int threadReceive();
		bool isThreadActive();
		void threadKill();
		void threadWait();

	private:
		static void *threadEntry(void*);
		pthread_t threadId;
		vector<int> t_messages;
		bool t_active;
		pthread_mutex_t t_messages_mutex;
		pthread_mutex_t t_active_mutex;
};

#endif
