.SUFFIXES: .o .cpp
CC=g++

CFLAGS=-I/usr/include/postgresql
LIBS=-lpq /usr/lib/libpqxx.a -lreadline -lm -lpthread

OBJS=Logger.o

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

all: audio admin studio_play studio_manage $(OBJS)

clean:
	rm -rf *.o

audio:
	cd audio; make all;
admin:
	cd admin; make all;
studio_play:
	cd studio_play; make all;
studio_manage:
	cd studio_manage; make all;

Logger.o: Logger.cpp Logger.h
