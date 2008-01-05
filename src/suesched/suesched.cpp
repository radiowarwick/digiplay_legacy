/*
 * Sustainer Scheduling application
 * suesched.cpp
 * Schedules music for hour-long periods
 * TODO: Real-time scheduling
 * TODO: A lot more...
 *
 * Copyright (c) 2004-2005 Chris Cantwell
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#include "scheduler.h"

int main() {
	system("clear");
	cout << "Radio Warwick Sustainer" << endl;
	cout << "-----------------------" << endl;
	cout << "Scheduling service started." << endl;

    bool detach=0;

    if (detach) {
        if(fork()) return 0;

        chdir("/");
        setsid();
        umask(0);

        int pid = fork();

        if (pid) {
            cout << "Daemon PID: " << pid << endl;
            return 0;
        }
    }

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
