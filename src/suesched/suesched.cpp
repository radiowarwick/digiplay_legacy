#include "scheduler.h"

int main() {
	system("clear");
	cout << "Radio Warwick Sustainer" << endl;
	cout << "-----------------------" << endl;
	cout << "Scheduling service started." << endl;
	scheduler *S = new scheduler();
	while (true) {
		if (S->getPlaylistSize() == 0) {
			cout << "SCH::FATAL:Nothing to schedule!" << endl;
			exit(-1);
		}
		else {
			if (S->getScheduleRemainSize() < 5)
				S->doSchedule(3600);
		}
		sleep(3);
	}
}
