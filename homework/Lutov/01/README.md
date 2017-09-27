# Определение скорости суммирования матрицы

Программа собирается командой `make`.

Результаты замеров времени:

```sh
$ ./performance-benchmark
Sum by rows
2159 us
Sum by columns
7139 us
```

Выводы: суммирование по рядам работает более, чем в 3 раза быстрее.

```sh
$ valgrind --tool=cachegrind ./performance-benchmark --only-cols
...
D1  miss rate:          22.5% (       23.5%     +        1.0%  )
...
$ valgrind --tool=cachegrind ./performance-benchmark --only-rows
...
D1  miss rate:          90.0% (       94.1%     +        1.0%  )
...
```
