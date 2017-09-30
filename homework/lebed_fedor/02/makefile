CXX = clang++
OPTIONS = -std=c++14 -O3 -Wpedantic -Wall -Wextra

all: parse
parse: parse.cpp parsing.o parsing_error.o
	$(CXX) -o $@ $^ $(OPTIONS)
%.o: %.cpp %.h
	$(CXX) -c -o $@ $< $(OPTIONS)
clean:
	rm -rf parse *.o
