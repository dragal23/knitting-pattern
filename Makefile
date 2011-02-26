

all: test build


test: build pattern-test


build: pattern.o


pattern.o: pattern.c++ pattern.h++
	g++ -c pattern.c++


pattern-test: pattern-test.c++ pattern.o
	g++ -o pattern-test pattern-test.c++ pattern.o