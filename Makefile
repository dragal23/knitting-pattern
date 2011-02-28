

all: build test generators

test: build test/pattern-test test/pattern-test-static

build: build/libpattern.so build/libpattern.a

generators: build build/generators/modulation



build/libpattern.a: src/pattern.c++ src/pattern.h++
	g++ -Wall -c -fpic -o build/libpattern.a src/pattern.c++

build/libpattern.so: build/libpattern.a
	g++ -Wall -shared -fpic -o build/libpattern.so build/libpattern.a




test/pattern-test-static: src/pattern-test.c++ build/libpattern.a
	g++ -Wall -static -o test/pattern-test-static src/pattern-test.c++ -Lbuild -lpattern

test/pattern-test: src/pattern-test.c++ build/libpattern.so
	g++ -Wall -o test/pattern-test src/pattern-test.c++ -Lbuild -lpattern




build/generators/modulation: src/generators/modulation.c++
	g++ -Wall -static -o build/generators/modulation src/generators/modulation.c++ -Lbuild -lpattern

