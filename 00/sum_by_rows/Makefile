CPPFLAGS+=-O2 -Wall -std=c++14 -fsanitize=undefined
.PHONY: all clean run test

all: sum_by_rows

sum_by_rows: sum_by_rows.o
    g++ $(CPPFLAGS) -o $@ $^

sum_by_rows.o: sum_by_rows.cpp
    g++ $(CPPFLAGS) -c $<

run:
    ./sum_by_rows

test:
    pwd

clean:
    rm -rf *.o