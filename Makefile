

LIB_INSTALL_DIR=~/lib
INCLUDE_INSTALL_DIR=~/include


export LD_INSTALL_PATH=/home/dragal/lib


all: build test generators

install: build
	cp build/libpattern.a build/libpattern.so $(LIB_INSTALL_DIR)
	cp src/pattern.h++ $(INCLUDE_INSTALL_DIR)



build: build/libpattern.so build/libpattern.a

build/libpattern.a: src/pattern.c++ src/pattern.h++
	g++ -Wall -c -fpic -o build/libpattern.a src/pattern.c++

build/libpattern.so: build/libpattern.a
	g++ -Wall -shared -fpic -o build/libpattern.so build/libpattern.a




test: build test/pattern-test test/pattern-test-static

test/pattern-test-static: src/pattern-test.c++ build/libpattern.a
	g++ -Wall -static -o test/pattern-test-static src/pattern-test.c++ -Lbuild -lpattern

test/pattern-test: src/pattern-test.c++ build/libpattern.so
	g++ -Wall -o test/pattern-test src/pattern-test.c++ -Lbuild -lpattern




generators: build build/generators/modulation

build/generators/modulation: src/generators/modulation.c++
	g++ -Wall -static -o build/generators/modulation src/generators/modulation.c++ -L/home/dragal/lib -lpattern -lpsk

