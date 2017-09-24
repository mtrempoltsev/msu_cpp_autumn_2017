#!/bin/bash
echo "Collection of statistics: sum_by_cols"
for n in {1..5}; do ./sum_by_cols $n 1>>results/result_sum_by_cols.txt; done
echo "Collection of statistics: sum_by_rows"
for n in {1..5}; do ./sum_by_rows $n 1>>results/result_sum_by_rows.txt; done
echo "Valgrind: sum_by_cols"
valgrind --tool=cachegrind --log-file="./results/valgrind_sum_by_cols.txt" ./sum_by_cols
echo "Valgrind: sum_by_rows"
valgrind --tool=cachegrind --log-file="./results/valgrind_sum_by_rows.txt" ./sum_by_rows