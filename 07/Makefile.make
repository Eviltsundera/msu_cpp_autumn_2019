CPPFLAGS+=-O2 -Wall -std=c++14 -fsanitize=undefined
.PHONY: all clean run test

all: Vector

Vector: Vector.o
	g++ $(CPPFLAGS) -o $@ $^

Vector.o: Vector.cpp
	g++ $(CPPFLAGS) -c $<

run:
	./Vector

clean:
	rm -rf *.o
