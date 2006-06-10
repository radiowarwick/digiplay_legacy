#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/cdrom.h>
#include <ncurses.h>
#include <form.h>

#define MIN(x,y) (((x) < (y)) ? x : y)

#define NAME "RaW // Radio Warwick // Audio archive playin"

struct track {
	int num;	/* physical track number */
	int length_fr;	/* length of track in frames (75fps) */
	int selected;	/* will we rip it ? */

	unsigned char uid[16];	/* unique id */
	char *title;	/* track title */
	char *album;	/* album name */
	char *artists;	/* artists */
	char *origin;	/* track origin */
	char *reclibid;	/* reclibid (catalognumber) */
	char *genres;	/* genres */
	char *year_rel;	/* release year */
	char *result;	/* cdparanoia result */
	char *reclibinsert; /* insert into reclib */

	/* private, used to keep it all easy as pie */
	FIELD *fields[9];
	FORM  *form;
};

void freetracks(struct track *t, int num)
{
	int i;
	for (i = 0; i < num; i++) {
		if(t[i].title)
			free(t[i].title);
		if(t[i].album)
			free(t[i].album);
		if(t[i].artists)
			free(t[i].artists);
		if(t[i].origin)
			free(t[i].origin);
		if(t[i].reclibid)
			free(t[i].reclibid);
		if(t[i].genres)
			free(t[i].genres);
		if(t[i].year_rel)
			free(t[i].year_rel);
		if(t[i].result)
			free(t[i].result);
		if(t[i].reclibinsert)
			free(t[i].reclibinsert);
	}
}

struct track ttmp = {0};

int term_rows = 0;
int term_cols = 0;

WINDOW *win_title;
WINDOW *win_main;
WINDOW *win_status;

int cdp2tracks(struct track **t, char *buf, int len)
{
	int i,j;
	int ret = 0;
	int n,l,c;
	char x;

	*t = NULL;

//	fprintf(stderr, "buf:%s\n", buf);
	for (i = 0; i < len; i++) {
		if (!strncmp(buf+i, "TOTAL", 5))
			return ret;
		
		j = sscanf(buf + i,
			"%d.%d [%*d:%*d.%*d]%*d [%*d:%*d.%*d%c%n",
			&n, &l, &x, &c);
//		fprintf(stderr, "j:%d x:%c\n", j, x);

		if (j == 3 && x == ']') {
			ret++;
			*t = (struct track *) realloc(*t, sizeof(struct track) * ret);
			memset(*t + ret - 1, 0, sizeof(struct track));
			/* got line */
			(*t)[ret - 1].num = n;
			(*t)[ret - 1].length_fr = l;
			i += c;
		}
	}

	return ret;
}

void getresult(char **res, char *buf)
{
	int i;
	int len = strlen(buf);

	for (i = 0; i < len; i++) {
		if (!strncmp(buf+i, "(== PROGRESS", 12)) {
			if(*res)
				free(*res);
			*res = (char *) strdup(buf + i);
			return;
		}
	}
}

int csv2tracks(struct track **t, char *buf, int len)
{
	int i;
	int ret = 0;
	char *c;
	
	*t = NULL;
	
	for (i = 0; i < len; i++) {
		ret++;
		*t = (struct track *) realloc(*t, sizeof(struct track) * ret);
		memset(*t + ret - 1, 0, sizeof(struct track));
		/* got line */
		(*t)[ret - 1].num = strtol(buf + i, &c, 10);
		i = c - buf + 1;
		(*t)[ret - 1].length_fr = strtol(buf + i, &c, 10);
		i = c - buf;
	}

	return ret;
}

void wnd_splash(char *text)
{
	int w, h;
	getmaxyx(win_title, h, w);
	mvwprintw(win_title, 0, w - strlen(NAME), "%s", NAME);
	wclear(win_main);
	getmaxyx(win_main, h, w);
	mvwprintw(win_main, h / 2, (w - strlen(text)) / 2, "%s", text);
	wrefresh(win_main);
	wrefresh(win_title);
//	refresh();
}

void updstatus(char *text)
{
	int x=0,y=0;

	getsyx(y,x);
	mvwprintw(win_status, 1,0, text);
	wnoutrefresh(win_status);
	setsyx(y,x);
	doupdate();
}


void drawselection(WINDOW *win, struct track *tracks, int tracks_num, int start)
{
	int i = start;
	int w,h;
	
	getmaxyx(win, h,w);
	for(; i < MIN(h+start,tracks_num); i++) {
		mvwprintw(win, i-start,0, "[%c]   %3d     %2d:%.2d.%.2d",
					tracks[i].selected ? 'X' : ' ',
					tracks[i].num,
					tracks[i].length_fr / (75*60),
					(tracks[i].length_fr / 75) % 60,
					tracks[i].length_fr % 75);
	}
}

void dotrackselect(struct track *tracks, int tracks_num)
{
	int pos = 0;
	WINDOW *tmpwin;
	int w,h,i;

	getmaxyx(win_main, h, w);
	tmpwin = derwin(win_main, h - 6, w - 3, 6,3);
	keypad(tmpwin, TRUE);
	scrollok(tmpwin, TRUE);
	getmaxyx(tmpwin, h, w);

	drawselection(tmpwin, tracks, tracks_num, 0);
	wmove(tmpwin, 0,1);
	wrefresh(tmpwin);

	/* this is a tedious bit, we have to interact with the user */

	w=0;
	while((i = wgetch(tmpwin)))
	{
		switch (i)
		{
			case 'A':
			case 'a':
			{
				int i;
				for (i = 0; i < tracks_num; i++)
					tracks[i].selected = ~0;
				break;
			}

			case 'C':
			case 'c':
			{
				int i;
				for (i = 0; i < tracks_num; i++)
					tracks[i].selected = 0;
				break;
			}
			
			case 'i':
			case 'I':
			{
				int i;
				for (i = 0; i < tracks_num; i++)
					tracks[i].selected = ~tracks[i].selected;
				break;
			}
		
			/* TODO at somepoint implement a play feature */
			case '\n':
			case '\r':
			case KEY_ENTER:
			case 'X':
			case 'x':
			case ' ':
				tracks[pos].selected = ~tracks[pos].selected;
				break;
				
			case 'n':
			case KEY_DOWN:
				if(pos + 1 < tracks_num)
					pos++;
				break;

			case 'p':
			case KEY_UP:
				if(pos > 0)
					pos--;
				break;

			case KEY_F(1):
//			case '\n':
//			case '\r':
//			case KEY_ENTER:
				delwin(tmpwin);
				return;
		}
		if (pos >= h + w) {
			w++;
			wscrl(tmpwin, 1);
		} else if (pos < w) {
			w--;
			wscrl(tmpwin, -1);
		}
		drawselection(tmpwin, tracks, tracks_num, w);
		wmove(tmpwin, pos - w,1);
		wrefresh(tmpwin);
	
	}
}

int createtrackform(struct track *t)
{
	int i;

	int w,h;
	
	/* height, width, toprow, leftcol, ofscreenrows, nbuffers */

	/* 012345678901234567890
	 * title:     _____...
	 * artists:   _____...
	 * album:     _____...
	 * reclibnum: _____...
	 * released:  _____...
	 * genres:    _____...
	 * origin:    _____...
	 */
	
	keypad(win_main, TRUE);
#define OFFSET 3
	t->fields[0] = new_field(1, 60, OFFSET+1, 11, 0, 0);
	t->fields[1] = new_field(1, 60, OFFSET+3, 11, 0, 0);
	t->fields[2] = new_field(1, 60, OFFSET+5, 11, 0, 0);
	t->fields[3] = new_field(1, 10, OFFSET+7, 11, 0, 0);
	t->fields[4] = new_field(1,  6, OFFSET+9, 11, 0, 0);
	t->fields[5] = new_field(1, 60, OFFSET+11, 11, 0, 0);
	t->fields[6] = new_field(1, 60, OFFSET+13, 11, 0, 0);
	t->fields[7] = new_field(1,  5, OFFSET+15, 11, 0, 0);
	t->fields[8] = NULL;

	/* set field options */
	for (i = 0; i < 9; i++) {
		set_field_back(t->fields[i], A_UNDERLINE);
		field_opts_off(t->fields[i], O_AUTOSKIP);
		field_opts_off(t->fields[i], O_STATIC);
	}

	set_field_buffer(t->fields[1], 0, ttmp.artists);
	set_field_buffer(t->fields[2], 0, ttmp.album);
	set_field_buffer(t->fields[3], 0, ttmp.reclibid);
	set_field_buffer(t->fields[4], 0, ttmp.year_rel);
	set_field_buffer(t->fields[5], 0, ttmp.genres);
	set_field_buffer(t->fields[6], 0, ttmp.origin);
	set_field_buffer(t->fields[7], 0, ttmp.reclibinsert);

	t->form = new_form(t->fields);
	set_form_win(t->form, win_main);
	post_form(t->form);
	wrefresh(win_main);

	
	getmaxyx(win_main, h, w);	
	mvwprintw(win_main, 0, w/2 - 4, "Track %d", t->num);
	mvwprintw(win_main, 1, 0, "Please fill in the following.  Press F1 when complete");

	mvwprintw(win_main, OFFSET+1,0, "title:");
	mvwprintw(win_main, OFFSET+3,0, "artists:");
	mvwprintw(win_main, OFFSET+5,0, "album:");
	mvwprintw(win_main, OFFSET+7,0, "reclibnum:");
	mvwprintw(win_main, OFFSET+9,0, "released:");
	mvwprintw(win_main, OFFSET+11,0, "genres:");
	mvwprintw(win_main, OFFSET+13,0, "origin:");
	mvwprintw(win_main, OFFSET+15,0, "rcinsrt:");
	wmove(win_main, OFFSET+1,11);
	wrefresh(win_main);
}

void cleanuptrackform(struct track *t)
{
	int i;
	unpost_form(t->form);
	free_form(t->form);
	for (i = 0; i < 8; i++)
		free_field(t->fields[i]);
}

int validatetrackform(struct track *t)
{
	int rows;
	
	dynamic_field_info(t->fields[0], NULL, &rows, NULL);
	t->title = (char *) malloc(rows + 1);
	memcpy(t->title, field_buffer(t->fields[0], 0), rows);
	t->title[rows] = 0;
	
	dynamic_field_info(t->fields[1], NULL, &rows, NULL);
	t->artists = (char *) malloc(rows + 1);
	memcpy(t->artists, field_buffer(t->fields[1], 0), rows);
	t->artists[rows] = 0;
	
	dynamic_field_info(t->fields[2], NULL, &rows, NULL);
	t->album = (char *) malloc(rows + 1);
	memcpy(t->album, field_buffer(t->fields[2], 0), rows);
	t->album[rows] = 0;

	dynamic_field_info(t->fields[3], NULL, &rows, NULL);
	t->reclibid = (char *) malloc(rows + 1);
	memcpy(t->reclibid, field_buffer(t->fields[3], 0), rows);
	t->reclibid[rows] = 0;
	
	dynamic_field_info(t->fields[4], NULL, &rows, NULL);
	t->year_rel = (char *) malloc(rows + 1);
	memcpy(t->year_rel, field_buffer(t->fields[4], 0), rows);
	t->year_rel[rows] = 0;
	
	dynamic_field_info(t->fields[5], NULL, &rows, NULL);
	t->genres = (char *) malloc(rows + 1);
	memcpy(t->genres, field_buffer(t->fields[5], 0), rows);
	t->genres[rows] = 0;
	
	dynamic_field_info(t->fields[6], NULL, &rows, NULL);
	t->origin = (char *) malloc(rows + 1);
	memcpy(t->origin, field_buffer(t->fields[6], 0), rows);
	t->origin[rows] = 0;
	
	dynamic_field_info(t->fields[7], NULL, &rows, NULL);
	t->reclibinsert = (char *) malloc(rows + 1);
	memcpy(t->reclibinsert, field_buffer(t->fields[7], 0), rows);
	t->reclibinsert[rows] = 0;
	
	ttmp.artists = (char *) strdup(t->artists);
	ttmp.album = (char *) strdup(t->album);
	ttmp.reclibid = (char *) strdup(t->reclibid);
	ttmp.year_rel = (char *) strdup(t->year_rel);
	ttmp.genres = (char *) strdup(t->genres);
	ttmp.origin = (char *) strdup(t->origin);
	ttmp.reclibinsert = (char *) strdup(t->reclibinsert);
	return 0;
}

int handletrackinfo(struct track *t)
{
	int i;
	int ch;

	(ch = wgetch(win_main));
	{
		switch(ch)
		{
		case KEY_F(1):
			form_driver(t->form, REQ_VALIDATION);
			validatetrackform(t);
			wmove(win_main,1,0);
			wclrtoeol(win_main);
			mvwprintw(win_main, 1,0, "Please wait ...");
			wrefresh(win_main);
			return 1;
		case '\n':
		case '\r':
		case KEY_ENTER:
		case KEY_DOWN:
			form_driver(t->form, REQ_NEXT_FIELD);
			form_driver(t->form, REQ_END_LINE);
			break;
		case KEY_UP:
			form_driver(t->form, REQ_PREV_FIELD);
			form_driver(t->form, REQ_END_LINE);
			break;
		case '\b':
		case '\177':
		case KEY_DC:
		case KEY_BACKSPACE:
			form_driver(t->form, REQ_DEL_PREV);
			break;
		case KEY_LEFT:
			form_driver(t->form, REQ_LEFT_CHAR);
			break;
		case KEY_RIGHT:
			form_driver(t->form, REQ_RIGHT_CHAR);
			break;
		default:
			form_driver(t->form, ch);
			break;
		}
	}
	wrefresh(win_main);
	return 0;
}

int main(int argc, char *argv[])
{
	int fd;
	char mcn[14] = {0};
	char buf[10240];
	int len;
	int i;

	/* initialization */
	initscr();
	cbreak();
	noecho();
	getmaxyx(stdscr, term_rows, term_cols);

	if (term_rows == 0 || term_cols == 0) {
		endwin();
		fprintf(stderr, "Terminal is not of suitable size (zero)\n");
		return -1;
	}

	win_status = newwin(2, term_cols, term_rows - 2, 0);
	win_title = newwin(2, term_cols, 0, 0);
	win_main = newwin(term_rows - 4, term_cols, 2, 0);
	wborder(win_title, ' ', ' ', ' ', '-', ' ', ' ', '-', '-');
	wborder(win_status, ' ', ' ', '-', ' ', '-', '-', ' ', ' ');
	wrefresh(win_title);
	wrefresh(win_status);
	leaveok(win_status, TRUE);

	while(1) {
		int fdpair[2];
		int tracks_num;
		struct track *tracks;
		
		memset(mcn, 0, sizeof (mcn));
	
		/* 1. display splash screen */
		wnd_splash("Please insert an Audio CD");

		/* 2. poll the cdrom drive to see if a CD has been inserted */
		fd = open((argc == 2) ? argv[1] : "/dev/cdrom", O_RDONLY | O_NONBLOCK);
		while (1) {
			int ret;
			sleep(1);
			ret = ioctl(fd, CDROM_DRIVE_STATUS);
			if (ret != CDS_DISC_OK)
				continue;
			ret = ioctl(fd, CDROM_DISC_STATUS);
			if (ret == CDS_AUDIO || ret == CDS_MIXED)
				break;
		}
		ioctl(fd, CDROM_GET_MCN, mcn);
		close(fd);
		wnd_splash("Please wait ...");

		pipe(fdpair);
		switch(fork())
		{
		case 0:
			close(2);
			dup2(fdpair[1],2);
			close(fdpair[1]);
			close(fdpair[0]);
			/*
			execl("/usr/bin/perl", "perl", "-e", "open FD, \"/audioplayin/cdparanoia -Q 2>&1 |\"; while(<FD>) { ($track, $length) = m!^\\s*(\\d+)\\.\\s+(\\d+)\\s+\\[\\d+:\\d+\\.\\d+\\]\\s+(\\d+)\\s+\\[\\d+:\\d+\\.\\d+\\]!; next if (!defined($track)); print \"$track,$length\\n\"; }", NULL);
			*/
			execl("/usr/local/bin/cdparanoia", "cdparanoia",
					"-Q", NULL);
			_exit(0);
			
		default:
			close(fdpair[1]);
			len = 0;
			while ((i = read(fdpair[0], buf + len, 10240 - len)))
				len += i;
			close(fdpair[0]);
			wait(NULL);
		}
		wclear(win_main);
		tracks_num = cdp2tracks(&tracks, buf, len);
		/* tracks_num = csv2tracks(&tracks, buf, len); */
		mvwprintw(win_main, 1,0, "Please select the tracks to rip using the spacebar.  More than 1 may be selected.");
		mvwprintw(win_main, 2,0, "the UP and DOWN cursor keys move between tracks.  Press F1 when complete");
		mvwprintw(win_main, 4,2,  "Selct  Track     Time", tracks_num);
		mvwprintw(win_main, 5,2,  "=========================");
		wrefresh(win_main);
		dotrackselect(tracks, tracks_num);
		
		for (i = 0; i < tracks_num; i++) {
			if(!tracks[i].selected)
				continue;

			len = snprintf(buf, 1023, "%s,%d,%s,%d", mcn, tracks[i].num, gethostname, time(NULL));
			md5_buffer(buf, len, tracks[i].uid);
			createtrackform(&tracks[i]);
			pipe(fdpair);
			switch (fork())
			{
			case 0:
			{	
				char buf2[128];
				close(2);
				dup2(fdpair[1],2);
				close(fdpair[1]);
				close(fdpair[0]);
				snprintf(buf2, 128, "%d", tracks[i].num);
				snprintf(buf, 1023, "/mnt/audio/audio/inbox/%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x",
					tracks[i].uid[0], tracks[i].uid[1], tracks[i].uid[2], tracks[i].uid[2],
					tracks[i].uid[4], tracks[i].uid[5], tracks[i].uid[6], tracks[i].uid[7],
					tracks[i].uid[8], tracks[i].uid[9], tracks[i].uid[10], tracks[i].uid[11],
					tracks[i].uid[12], tracks[i].uid[13], tracks[i].uid[14], tracks[i].uid[15]);
				execl("/usr/local/bin/cdparanoia", "cdparanoia", "-r", "-Y", buf2, buf, NULL);
				//execl("/audioplayin/cdparanoia", "cdparanoia", "-r", buf2, buf, NULL);
				_exit(-2);
			}
				
			default:
			{
				int complete = 0;
				fd_set fdset;
				close(fdpair[1]);
				while(complete != 0x3) {
					FD_ZERO(&fdset);
					FD_SET(0, &fdset);
					if (fdpair[0])
						FD_SET(fdpair[0], &fdset);
					select(fdpair[0]+1, &fdset, NULL, NULL, NULL);
					if(fdpair[0] && FD_ISSET(fdpair[0], &fdset)) {
						len = read(fdpair[0], buf, 1023);
						if (len > 0) {
							buf[len] = 0;
							updstatus(buf);
							getresult(&tracks[i].result, buf);
						} else {
							close(fdpair[0]);
							fdpair[0] = 0;
							complete |= 0x02;
						}
					}
					if(FD_ISSET(0, &fdset)) {
						if(!(complete & 0x1))
							complete |= handletrackinfo(&tracks[i]);
						else
							wgetch(win_main);
					}
				}
				cleanuptrackform(&tracks[i]);
				updstatus("Track Complete");
			}
			}
			snprintf(buf, 1023, "/mnt/audio/audio/inbox/%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x.info",
					tracks[i].uid[0], tracks[i].uid[1], tracks[i].uid[2], tracks[i].uid[2],
					tracks[i].uid[4], tracks[i].uid[5], tracks[i].uid[6], tracks[i].uid[7],
					tracks[i].uid[8], tracks[i].uid[9], tracks[i].uid[10], tracks[i].uid[11],
					tracks[i].uid[12], tracks[i].uid[13], tracks[i].uid[14], tracks[i].uid[15]);
			fd = open(buf, O_WRONLY | O_CREAT, 0644);
			len = snprintf(buf, 1023, "uid: %.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x\n",
					tracks[i].uid[0], tracks[i].uid[1], tracks[i].uid[2], tracks[i].uid[2],
					tracks[i].uid[4], tracks[i].uid[5], tracks[i].uid[6], tracks[i].uid[7],
					tracks[i].uid[8], tracks[i].uid[9], tracks[i].uid[10], tracks[i].uid[11],
					tracks[i].uid[12], tracks[i].uid[13], tracks[i].uid[14], tracks[i].uid[15]);
			write(fd, buf, len);
			len = snprintf(buf, 1023, "title: %s\n", tracks[i].title);
			write(fd, buf, len);
			len = snprintf(buf, 1023, "artists: %s\n", tracks[i].artists);
			write(fd, buf, len);
			len = snprintf(buf, 1023, "album: %s\n", tracks[i].album);
			write(fd, buf, len);
			len = snprintf(buf, 1023, "tracknum: %d\n", tracks[i].num);
			write(fd, buf, len);
			len = snprintf(buf, 1023, "genres: %s\n", tracks[i].genres);
			write(fd, buf, len);
			len = snprintf(buf, 1023, "released: %s\n", tracks[i].year_rel);
			write(fd, buf, len);
			len = snprintf(buf, 1023, "lengthfr: %d\n", tracks[i].length_fr);
			write(fd, buf, len);
			len = snprintf(buf, 1023, "mcn: %s\n", mcn);
			write(fd, buf, len);
			len = snprintf(buf, 1023, "reclibid: %s\n", tracks[i].reclibid);
			write(fd, buf, len);
			len = snprintf(buf, 1023, "origin: %s\n", tracks[i].origin);
			write(fd, buf, len);
			len = snprintf(buf, 1023, "cdpresult: %s\n", tracks[i].result);
			write(fd, buf, len);
			len = snprintf(buf, 1023, "reclibinsert: %s\n", tracks[i].reclibinsert);
			write(fd, buf, len);
			close(fd);

		}

		/* eject cd */
		fd = open((argc == 2) ? argv[1] : "/dev/cdrom", O_RDONLY | O_NONBLOCK);
		ioctl(fd, CDROMEJECT);
		close(fd);
	
		freetracks(tracks, tracks_num);
		tracks_num = 0;
		tracks = NULL;
		memset(&ttmp, 0, sizeof(struct track));
	}
	
	/* clean up*/
	refresh();
	endwin();

	printf("mcn is %s\n", mcn);

	return 0;
}