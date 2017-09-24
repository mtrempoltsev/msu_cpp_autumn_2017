# homework 1
Сборка:
```sh
$ g++ sum_by_rows.cpp -o sum_by_rows -O2 -std=c++11
$ g++ sum_by_cols.cpp -o sum_by_cols -O2 -std=c++11
```
Примерные результаты замеров времени:
   **size = 1000**: 
   - sum_by_cols --- 2630 us;
   - sum_by_rows --- 2268 us;
   
   **size = 10000**: 
   - sum_by_cols --- 851293 us;
   - sum_by_rows --- 235857 us;

Получается, что суммирование по столбцам на больших матрицах работает примерно в 4 раза быстрее суммирования по строкам.
Если сделать 
```sh
$ valgrind --tool=cachegrind ./sum_by_rows
$ valgrind --tool=cachegrind ./sum_by_cols
```
то видно, что при суммировании по столбцам промахов в кэш 3.1%, а по строкам 26.5%.