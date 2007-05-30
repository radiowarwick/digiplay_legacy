#include <iostream>
using namespace std;

#include "Thread.h"
using Audio::Thread;

Thread::Thread() {
    init_flag = false;
    t_active = false;
    pthread_mutex_init(&t_messages_mutex,NULL);
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
	threadKill();

    // get default attributes
	pthread_attr_init(&threadAttr);
	
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
	pthread_join(threadId,NULL);
}

/**
 * This routine requests termination of our thread. By default, this occurs at
 * the next 'cancellation point', set using \c threadTestKill
 */
void Thread::threadKill() {
    if (!init_flag) return;
	pthread_cancel(threadId);
    pthread_join(threadId,NULL);
}

/**
 * Mark a cancellation point in the \c threadExecute implementation. This
 * allows the thread to be killed off at any such points if requested.
 */
void Thread::threadTestKill() {
	pthread_testcancel();
}
