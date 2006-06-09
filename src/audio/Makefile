.SUFFIXES: .o .cpp
CC=g++

CFLAGS=-I/usr/include/postgresql
LIBS=-lpq /usr/lib/libpqxx.a -lreadline -lm -lpthread

OBJS=Component.o Input.o Thread.o

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS)

clean:
	rm -rf *.o

Component.o: Component.cpp Component.h
Input.o: Input.cpp Input.h
Thread.o: Thread.cpp Thread.h
