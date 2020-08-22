CC=gcc
CFLAGS=-g -Wall
EXES=shm_writer.exe shm_reader.exe
DBGS=*.dSYM
OBJS=*.o
DEPS=shm_common.h
LIBS=

# Add librt when running on linux
OS=$(shell uname -s)
ifeq "$(OS)" "Linux"
    LIBS=-lrt
endif

all: $(EXES)

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(EXES) $(DBGS) $(OBJS)