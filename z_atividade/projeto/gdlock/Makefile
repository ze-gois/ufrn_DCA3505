.PHONY: all build run clean

all: build

build: liba1.so

liba1.so: approach_1.c hook.c graph.c
	gcc -shared -fPIC -o liba1.so hook.c graph.c approach_1.c -ldl -lpthread

run: build
	./make_test.sh

clean:
	rm -rf build hook.o hook.a liba1.so
