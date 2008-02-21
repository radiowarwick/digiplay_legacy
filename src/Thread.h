#ifndef CLASS_THREAD
#define CLASS_THREAD

#include <vector>
using namespace std;

#include "pthread.h"

//#include "Audio.h"

#ifndef ENUM_MESSAGE
#define ENUM_MESSAGE
//#pragma message( No thread messages defined! )
enum MESSAGE { NONE=0,
				STOP=1
			};
#endif

/** C++ Wrapper for a pthread.
 * Implementation of an object orientated thread base class. This object
 * manages a single thread with routines to start and stop the thread, as well
 * as a blocking routine to wait for thread termination. To use this class,
 * derive a class from it and implement the \c threadExecute routine to perform
 * the required task of the thread. Call \c threadTestKill to mark
 * 'cancellation points' within the \c threadExecute routine where the thread
 * may be terminated if requested.
 */
class Thread {
	public:
		/// Create a new thread object
        Thread();
		virtual ~Thread() = 0;

	protected:
		/// Start the thread
		int threadStart();
		/// Implementation of thread
		virtual void threadExecute() =0;

		/// Send a message to the thread
		void threadSend(int m);
		/// Received a message
		bool threadReceive(int m);

		/// Check if the thread is running
		bool isThreadActive();
		/// Create a cancellation point
		bool threadTestKill();
		/// Cancel the thread execution
		void threadKill();
		/// Wait for thread to finish
		void threadWait();

	private:
		// Entry point for thread
		static void *threadEntry(void*);

		// Holds the thread ID of the currently active thread
		pthread_t threadId;
		// Stores thread attributes for the thread
		pthread_attr_t threadAttr;

        bool init_flag;
        bool terminate_flag;

		// Storage for inter-thread messages
		vector<int> t_messages;
		bool t_active;
		pthread_mutex_t t_messages_mutex;
        pthread_mutex_t t_terminate_mutex;
};


/**
 * Implements a mutex object.
 */
class ThreadMutex {
 	public:
 		ThreadMutex();
 		~ThreadMutex();
 		
 		void lock();
 		bool tryLock();
 		void unlock();
 		
 	private:
 		pthread_mutex_t t_mutex;
};

#endif
