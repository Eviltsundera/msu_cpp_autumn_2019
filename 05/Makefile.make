CPPFLAGS+=-O2 -Wall -std=c++14 -fsanitize=undefined
.PHONY: all clean run test

all: sd

sd: sd.o
	g++ $(CPPFLAGS) -o $@ $^

sd.o: sd.cpp
	g++ $(CPPFLAGS) -c $<

run:
	./sd

clean:
	rm -rf *.o
