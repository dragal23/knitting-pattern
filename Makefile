

all: test build


test: test/pattern-test test/pattern-test-static

build: build/libpattern.so build/libpattern.a

build/libpattern.a: pattern.c++ pattern.h++
	g++ -Wall -c -fpic -o build/libpattern.a pattern.c++

build/libpattern.so: build/libpattern.a
	g++ -Wall -shared -fpic -o build/libpattern.so build/libpattern.a

test/pattern-test-static: pattern-test.c++ build/libpattern.a
	g++ -Wall -static -o test/pattern-test-static pattern-test.c++ -Lbuild -lpattern

test/pattern-test: pattern-test.c++ build/libpattern.so
	g++ -Wall -o test/pattern-test pattern-test.c++ -Lbuild -lpattern