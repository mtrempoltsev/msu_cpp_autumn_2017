CC=g++
CPPFLAGS=-O2 -std=c++11
RUNS_NUM=5
NAMER=sum_by_rows
NAMEC=sum_by_columns
NAMES=benchmark_script/make_a_few_runnings.sh

.PHONY: all benchmark clean
.SILENT: benchmark

all:
	mkdir .tmp
	$(CC) $(CPPFLAGS) -o .tmp/$(NAMER) $(NAMER).cpp
	$(CC) $(CPPFLAGS) -o .tmp/$(NAMEC) $(NAMEC).cpp
benchmark:
	echo "===ROWS==="
	bash $(NAMES) .tmp/$(NAMER) $(RUNS_NUM)
	echo "===COLUMNS==="
	bash $(NAMES) .tmp/$(NAMEC) $(RUNS_NUM)
clean:
	rm -r .tmp
