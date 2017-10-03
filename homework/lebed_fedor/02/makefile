CXX = clang++
OPTIONS = -std=c++14 -O3 -Wpedantic -Wall -Wextra

.PHONY: test clean

all: parse
test: parse test.py
	./test.py parse
parse: parse.cpp parsing.cpp parsing_error.cpp
	$(CXX) -o $@ $^ $(OPTIONS)
clean:
	rm -rf parse
