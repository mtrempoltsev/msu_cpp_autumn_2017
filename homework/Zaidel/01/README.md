#Результаты:

**Время работы:**
sum_by_cols:       1215969 us
sum_by_rows:        264304 us

**Работа с кэшем:**
sum_by_cols: LL miss rate:            4.1% 
sum_by_rows: LL miss rate:            0.4%

**Сборка программы**

sum_by_cols:   g++  sum_by_cols.cpp -o sum_by_cols  --std=c++11  -O2

sum_by_rows:   g++  sum_by_rows.cpp -o sum_by_rows  --std=c++11 -O2

