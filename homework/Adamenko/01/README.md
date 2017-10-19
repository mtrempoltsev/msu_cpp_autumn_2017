#Problem
---

Написать две программы суммирующие элементы двумерного массива (матрицы) целых чисел. Одна программа суммирует по столбцам, вторая по строкам. Измерить время работы в обоих случаях, сравнить результаты. Для замеров можно использовать класс Timer. В репозитории в директории homework создать директорию со своей фамилией, внутри этой директории создать директорию 01, файлы с решением положить внутрь. Программа должна собираться из консоли одной командой, например, так:
#Answer
### 1188458 us по столбцам
### 232317  us по строкам
#Start command
---
```
g++ sum_by_rows.cpp -o sum_by_rows.o --std=c++11 -O2
g++ sum_by_columns.cpp -o sum_by_columns.o --std=c++11 -O2

valgrind --tool=cachegrind your_program
```
#Output
---
```
valgrind --tool=cachegrind ./sum_by_rows.o 
==11123== Cachegrind, a cache and branch-prediction profiler
==11123== Copyright (C) 2002-2017, and GNU GPL'd, by Nicholas Nethercote et al.
==11123== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==11123== Command: ./sum_by_rows.o
==11123== 
--11123-- warning: L3 cache found, using its data for the LL simulation.
--11123-- run: /usr/bin/dsymutil "./sum_by_rows.o"
warning: no debug symbols in executable (-arch x86_64)
2080770  us
==11123== 
==11123== I   refs:      815,877,350
==11123== I1  misses:          4,207
==11123== LLi misses:          3,032
==11123== I1  miss rate:        0.00%
==11123== LLi miss rate:        0.00%
==11123== 
==11123== D   refs:      305,211,090  (203,434,656 rd   + 101,776,434 wr)
==11123== D1  misses:     12,568,543  (  6,304,005 rd   +   6,264,538 wr)
==11123== LLd misses:     12,535,537  (  6,272,042 rd   +   6,263,495 wr)
==11123== D1  miss rate:         4.1% (        3.1%     +         6.2%  )
==11123== LLd miss rate:         4.1% (        3.1%     +         6.2%  )
==11123== 
==11123== LL refs:        12,572,750  (  6,308,212 rd   +   6,264,538 wr)
==11123== LL misses:      12,538,569  (  6,275,074 rd   +   6,263,495 wr)
==11123== LL miss rate:          1.1% (        0.6%     +         6.2%  )
```

```
valgrind --tool=cachegrind ./sum_by_columns.o 
==11125== Cachegrind, a cache and branch-prediction profiler
==11125== Copyright (C) 2002-2017, and GNU GPL'd, by Nicholas Nethercote et al.
==11125== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==11125== Command: ./sum_by_columns.o
==11125== 
--11125-- warning: L3 cache found, using its data for the LL simulation.
--11125-- run: /usr/bin/dsymutil "./sum_by_columns.o"
warning: no debug symbols in executable (-arch x86_64)
10538413 us
==11125== 
==11125== I   refs:      930,934,713
==11125== I1  misses:          4,179
==11125== LLi misses:          3,023
==11125== I1  miss rate:        0.00%
==11125== LLi miss rate:        0.00%
==11125== 
==11125== D   refs:      405,205,037  (303,427,005 rd   + 101,778,032 wr)
==11125== D1  misses:    118,808,803  (112,544,237 rd   +   6,264,566 wr)
==11125== LLd misses:    102,886,894  ( 96,623,380 rd   +   6,263,514 wr)
==11125== D1  miss rate:        29.3% (       37.1%     +         6.2%  )
==11125== LLd miss rate:        25.4% (       31.8%     +         6.2%  )
==11125== 
==11125== LL refs:       118,812,982  (112,548,416 rd   +   6,264,566 wr)
==11125== LL misses:     102,889,917  ( 96,626,403 rd   +   6,263,514 wr)
==11125== LL miss rate:          7.7% (        7.8%     +         6.2%  )
