CC = gcc
CFLAGS = -Wall -fPIC -O0 -g

all: clean libinterpose.so main run run_ld

libinterpose.so: interpose.c
	$(CC) $(CFLAGS) -shared -o $@ $< -ldl

main: main.c
	$(CC) $(CFLAGS) -o $@ $<

run: main
	./main

run_ld:
	LD_PRELOAD=./libinterpose.so ./main

clean:
	rm -f libinterpose.so main
