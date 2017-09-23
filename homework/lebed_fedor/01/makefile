CXX = clang++ -std=c++14 -O3 -Wpedantic -Wall -Wextra

all: sum_by_rows sum_by_columns

%: %.cpp measure.h timer.h config.h
	$(CXX) -o $@ $<

measure: measure-sum_by_rows measure-sum_by_columns
measure-%: %
	valgrind --tool=cachegrind ./$< 2>cachegrind.out.$<.txt >/dev/null

clean:
	rm -f sum_by_rows sum_by_columns cachegrind.out.*
