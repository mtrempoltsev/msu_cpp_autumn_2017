CXX = clang++ -std=c++14 -O3

all: sum_by_rows sum_by_columns

%: %.cpp measure.h timer.h config.h
	$(CXX) -o $@ $<

clean:
	rm -f sum_by_rows sum_by_columns
