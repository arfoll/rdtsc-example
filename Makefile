CC=gcc
CFLAGS=-O -Wall 

all: clean
	@make rdtsc

rdtsc: a.o b.o
	@${CC} *.o -o rdtsc -luv -lrt -lpthread -lnsl -ldl -O2 -lmraa

clean:
	@rm -rf *.o
	@rm -rf rdtsc
