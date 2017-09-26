compile_rows:
	g++ sum_by_rows.cpp -o sum_by_rows --std=c++11 -O2

compile_cols:
	g++ sum_by_cols.cpp -o sum_by_cols --std=c++11 -O2

run_rows:
	make compile_rows
	./sum_by_rows

run_cols:
	make compile_cols
	./sum_by_cols

valgrind_rows:
	make compile_rows && valgrind --tool=cachegrind --log-file="valgrind_rows.out" ./sum_by_rows

valgrind_cols:
	make compile_cols && valgrind --tool=cachegrind --log-file="valgrind_cols.out" ./sum_by_cols

run:
	make compile_rows && make compile_cols && bash cmp.sh
