#include "Thread.h"

int Thread::threadStart() {
	int code = pthread_create(&threadId, NULL, Thread::threadEntry, 
									(void*)this);
	return code;
}

void *Thread::threadEntry(void *pthis) {
	Thread *pt = (Thread*)pthis;
	pt->threadExecute();
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
		for (int i = 0; i < t_messages.size(); i++) {
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
		
