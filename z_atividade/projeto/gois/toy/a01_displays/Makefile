CC = gcc
CFLAGS = -Wall -fPIC -O0 -g

all: clean libinterpose.so main

libinterpose.so: interpose.c
	$(CC) $(CFLAGS) -lraylib -shared -o $@ interpose.c graph.c interpose_graph.c -ldl

main: main.c
	$(CC) $(CFLAGS) -o $@ $<

run: main
	./main

run_ld:
	LD_PRELOAD=./libinterpose.so ./main

clean:
	rm -f libinterpose.so main
