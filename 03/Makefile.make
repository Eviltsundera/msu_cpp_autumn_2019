CPPFLAGS+=-O2 -Wall -std=c++14 -fsanitize=undefined
.PHONY: all clean run test

all: Matrix

Matrix: Matrix.o
	g++ $(CPPFLAGS) -o $@ $^

Matrix.o: Matrix.cpp
	g++ $(CPPFLAGS) -c $<

run:
	./Matrix

clean:
	rm -rf *.o
