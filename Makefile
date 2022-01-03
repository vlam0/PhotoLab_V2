# Makefile: PhotoLab_v2

# variable definitions
  CC = gcc
  DEBUG = -DDEBUG -g
  O2 = -DNDEBUG
  CFLAGS = -Wall -ansi -std=c99 -lm -c
  LFLAGS = -Wall -lm -ansi -std=c99

# convience targets
all: PhotoLab

clean:
	rm -f *.o
	rm -f PhotoLab

test: PhotoLab
	./PhotoLab

PhotoLabTest: PhotoLabTestDebug
	./PhotoLabTest

# link libfilters
libfilter.a: DIPs.o Advanced.o
	ar rc libfilter.a DIPs.o Advanced.o
	ranlib libfilter.a

# compilation rules
FileIO.o: FileIO.c FileIO.h Constants.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

Advanced.o: Advanced.c Advanced.h Constants.h
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o

PhotoLab.o: PhotoLab.c FileIO.h DIPs.h Advanced.h Constants.h
	$(CC) $(CFLAGS) PhotoLab.c -o PhotoLab.o

PhotoLabTest.o: PhotoLab.c FileIO.h DIPs.h Advanced.h Constants.h
	$(CC) $(DEBUG) $(CFLAGS) PhotoLab.c -o PhotoLabTest.o

PhotoLab: PhotoLab.o FileIO.o libfilter.a
	$(CC) $(O2) $(LFLAGS) PhotoLab.o FileIO.o -L. -lfilter -o PhotoLab

PhotoLabTestDebug: PhotoLabTest.o FileIO.o libfilter.a 
	$(CC) $(DEBUG) $(LFLAGS) PhotoLabTest.o FileIO.o -L. -lfilter -o PhotoLabTest
