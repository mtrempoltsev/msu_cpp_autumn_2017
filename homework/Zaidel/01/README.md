#Результаты:

**Среднее время работы по 100 итерациям:**
sum_by_cols:        872248 ms
sum_by_rows:       250967 ms

**Работа с кэшем:**
sum_by_cols: LL miss rate:              4.0% 
sum_by_rows: LL miss rate:            2.2%

**Сборка программы**

sum_by_cols:   g++  sum_by_cols.cpp -o sum_by_cols  --std=c++11  -O2

sum_by_rows:  g++  sum_by_rows.cpp -o sum_by_rows  --std=c++11 -O2