CPPFLAGS+=-O2 -Wall -std=c++14 -fsanitize=undefined
.PHONY: all clean run test

all: format

format: format.o
	g++ $(CPPFLAGS) -o $@ $^

format.o: format.cpp
	g++ $(CPPFLAGS) -c $<

run:
	./format

clean:
	rm -rf *.o