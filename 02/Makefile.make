CPPFLAGS+=-O2 -Wall -std=c++14 -fsanitize=undefined
.PHONY: all clean run test

all: alloc

alloc: alloc.o
	g++ $(CPPFLAGS) -o $@ $^

alloc.o: alloc.cpp
	g++ $(CPPFLAGS) -c $<

run:
	./alloc

test:
	python3 ./check.py

clean:
	rm -rf *.o
