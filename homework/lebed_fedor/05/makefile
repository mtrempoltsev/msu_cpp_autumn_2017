CXX = clang++ -Wall -Wpedantic -Wextra -std=c++14 -O2

all: matrix_test
test: matrix_test
	./matrix_test
matrix_test: matrix_test.cpp matrix.cpp
	$(CXX) -o $@ matrix_test.cpp
clean:
	rm -f matrix_test
