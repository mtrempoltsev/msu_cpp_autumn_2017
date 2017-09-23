CC      	= g++
CFLAGS  	= -g -Wall -pedantic -std=c++14 -O2
VLGR 		= valgrind
VLGRFLAGS 	= --tool=cachegrind
DF 			= diff
DFFLAGS		= --side-by-side

compile: clean
	$(CC) $(CFLAGS) optimal.cpp -o optimal
	$(CC) $(CFLAGS) slow.cpp -o slow

bench-cach-misses: compile # main target
	$(VLGR) $(VLGRFLAGS) --log-file=optimal.cache-misses.out ./optimal
	$(VLGR) $(VLGRFLAGS) --log-file=slow.cache-misses.out ./slow
	$(DF) $(DFFLAGS) optimal.cache-misses.out slow.cache-misses.out

clean:
	rm -rf *.o optimal slow *.out.*