# homework 1
Сборка:
```sh
$ g++ sum_by_rows.cpp -o sum_by_rows -O2 -std=c++11
$ g++ sum_by_cols.cpp -o sum_by_cols -O2 -std=c++11
```
Примерные результаты замеров времени:
   **size = 1000**: 
   - sum_by_cols --- 2405 us;
   - sum_by_rows --- 3380 us;
   
   **size = 10000**: 
   - sum_by_cols --- 242721 us;
   - sum_by_rows --- 2369550 us;

Получается, что суммирование по строкам на больших матрицах работает примерно в 10 раз быстрее суммирования по столбцам.
Если сделать 
```sh
$ valgrind --tool=cachegrind ./sum_by_rows
$ valgrind --tool=cachegrind ./sum_by_cols
```
то видно, что при суммировании по столбцам промахов в кэш 23.7%, а по строкам всего 3.2%.