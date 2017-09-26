Comparing time for calculating sum looping through rows/columns of 2D-array.

g++ -Wall -Werror sum_by_rows.cpp -o sum_by_rows --std=c++11 -O2
g++ -Wall -Werror sum_by_columns.cpp -o sum_by_columns --std=c++11 -O2

By rows:

419407 us
422943 us
427267 us
420997 us
420206 us

Mean: 422164.0 us

By columns:

6909292 us
6936497 us
6883519 us
6913123 us
7092473 us

Mean: 6946980.8

