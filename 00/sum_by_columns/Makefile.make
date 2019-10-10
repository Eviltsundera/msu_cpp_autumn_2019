CPPFLAGS+=-O2 -Wall -std=c++14 -fsanitize=undefined
.PHONY: all clean run test

all: sum_by_columns

sum_by_columns: sum_by_columns.o
	g++ $(CPPFLAGS) -o $@ $^

sum_by_columns.o: sum_by_columns.cpp
	g++ $(CPPFLAGS) -c $<

run:
	./sum_by_columns

test:
	pwd

clean:
	rm -rf *.o