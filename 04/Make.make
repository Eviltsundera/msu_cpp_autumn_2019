CPPFLAGS+=-O2 -Wall -std=c++14 -fsanitize=undefined
.PHONY: all clean run test

all: BigInt

BigInt: BigInt.o
	g++ $(CPPFLAGS) -o $@ $^

BigInt.o: BigInt.cpp
	g++ $(CPPFLAGS) -c $<

run:
	./BigInt

clean:
	rm -rf *.o
