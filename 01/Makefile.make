CPPFLAGS+=-O2 -Wall -std=c++14 -fsanitize=undefined
.PHONY: all clean run test

all: calc

calc: calc.o
	g++ $(CPPFLAGS) -o $@ $^

calc.o: calc.cpp
	g++ $(CPPFLAGS) -c $<

run:
	./calc

test:
	python3 ./check.py

clean:
	rm -rf *.o
