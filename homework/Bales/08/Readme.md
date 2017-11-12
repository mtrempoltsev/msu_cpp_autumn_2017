# Work_08
Написать свой контейнер **Vector**, аналогичный __std::vector__ и итератор для него. 
Поддерживаемые методы:
* operator[], 
* push_back, 
* pop_back, 
* empty, 
* size, 
* clear, 
* begin, 
* end, 
* rbegin, 
* rend, 
* resize.

## How run
Осуществляем сборку исходников следующим образом:
```sh
$ make
```
Запускаем калькулятор + автоматически запускаем тесты:
```sh
$ ./vector
```
Результат работы, как и ожидалось:
```sh
CheckIntParses is ended.
CheckLongParses is ended.
CheckDoubleParses is ended.
Warning: Incorrect type conversion '3.1' from real to integer.
Warning: Incorrect type conversion '4.5' from real to integer.
IntParserForDouble is ended.
Warning: Incorrect type conversion '2147483650' out of domain range.
IntParserForLong is ended.
-4.28904
```