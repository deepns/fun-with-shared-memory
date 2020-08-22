CC=gcc
CFLAGS=-g -Wall
EXES=shm_writer.exe shm_reader.exe shm_clean.exe
DEPS=shm_common.h
OBJS=*.o
DBGS=*.dSYM

all: $(EXES)

# References
# $@ - left side of : (i.e. target)
# $^ - right side of :	(i.e. all prerequisites)
# $< - first prerequisite (e.g. filename that triggered the inference)
# See https://www.gnu.org/software/make/manual/make.html#Automatic-Variables

%.exe : %.o
	$(CC) $(CFLAGS) -o $@ $<

%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -rf $(EXES) $(OBJS) $(DBGS)