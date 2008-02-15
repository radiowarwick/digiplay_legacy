#include <iostream>
using namespace std;

#include "Thread.h"

Thread::Thread() {
    init_flag = false;
    terminate_flag = false;
    t_active = false;
    pthread_mutex_init(&t_messages_mutex,NULL);
    pthread_mutex_init(&t_terminate_mutex,NULL);
}

Thread::~Thread() {

}

/**
 * Starts the thread, triggering the \c threadExecute routine to be called.
 * This should be reimplemented in the derived class. If the thread is already
 * running, it is killed first.
 */
int Thread::threadStart() {
    // first kill our thread if it is running
	if (t_active) threadKill();

    // get default attributes
	pthread_attr_init(&threadAttr);
	// create thread detached.
	// it isn't valid to "join" detached threads. However, the thread will
	// automatically reclaim it's resources when completed.
	pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);
    terminate_flag = false;
	
    // create the new thread with default attributes starting \c threadEntry
    // The \c this pointer is passed to provide a reference to this instance
	int code = pthread_create(&threadId, &threadAttr, Thread::threadEntry, 
									(void*)this);
    init_flag = true;

	return code;
}

/**
 * Static routine to handle the creation of a new pthread
 */
void *Thread::threadEntry(void *pthis) {
    // Typecast void pointer back to \c Thread pointer
	Thread *pt = (Thread*)pthis;

    // Set thread active, run it, then set unactive
	pt->t_active = true;
    pt->terminate_flag = false;
	pt->threadExecute();
	pt->t_active = false;

    // terminate the thread cleanly
	pthread_exit(0);
}

void Thread::threadExecute() {

}

void Thread::threadSend(int m) {
	pthread_mutex_lock(&t_messages_mutex);

	if (pthread_self() == threadId) {
		m *= -1;
	}
	t_messages.push_back(m);

	pthread_mutex_unlock(&t_messages_mutex);
}

int Thread::threadReceive() {
	pthread_mutex_lock(&t_messages_mutex);
	
	int m = 0;
	if (t_messages.size() > 0) {
		int t = 1;
		if (pthread_self() != threadId) {
			t = -1;
		}
		for (unsigned int i = 0; i < t_messages.size(); i++) {
			if (t_messages.at(i) * t > 0) {
				m = t_messages.at(i) * t;
				t_messages.erase(t_messages.begin() + i);
				return t;
			}
		}
	}
	pthread_mutex_unlock(&t_messages_mutex);
	return m;
}

bool Thread::isThreadActive() {
    return t_active;
}

/**
 * This routine blocks the execution of the calling thread until our thread
 * terminates.
 */
void Thread::threadWait() {
	while (t_active) usleep(100);
}

/**
 * This routine requests termination of our thread. By default, this occurs at
 * the next 'cancellation point', set using \c threadTestKill
 */
void Thread::threadKill() {
    if (!init_flag) return;
    pthread_mutex_lock(&t_terminate_mutex);
    terminate_flag = true;
    pthread_mutex_unlock(&t_terminate_mutex);
}

/**
 * Mark a cancellation point in the \c threadExecute implementation. This
 * allows the thread to be killed off at any such points if requested.
 */
bool Thread::threadTestKill() {
    pthread_mutex_lock(&t_terminate_mutex);
    if (terminate_flag == true) {
        //terminate_flag = false;
        pthread_mutex_unlock(&t_terminate_mutex);
        return true;
    }
    pthread_mutex_unlock(&t_terminate_mutex);
    return false;
}


/**
 * ThreadMutex: object-orientated thread mutex.
 */
ThreadMutex::ThreadMutex() {
	pthread_mutex_init(&t_mutex,NULL);
}

ThreadMutex::~ThreadMutex() {
	pthread_mutex_destroy(&t_mutex);
}

void ThreadMutex::lock() {
	pthread_mutex_lock(&t_mutex);
}

bool ThreadMutex::tryLock() {
	if (pthread_mutex_trylock(&t_mutex) == 0) {
		return true;
	}
	else {
		return false;
	}
}

void ThreadMutex::unlock() {
	pthread_mutex_unlock(&t_mutex);
}
