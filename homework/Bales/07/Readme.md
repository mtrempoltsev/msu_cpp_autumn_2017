# Work_07
Необходимо модернизировать [Work_06](https://github.com/mtrempoltsev/msu_cpp_autumn_2017/tree/master/homework/Bales/06):

* Добавить обработку ошибок
* Заменить выделение памяти в куче на использования умных указателей

## Пример выражения:
```
-( -((5.2 + 3)/Pi - 4.2) * e)
```

## How run
Осуществляем сборку исходников следующим образом:
```sh
$ make
```
Запускаем калькулятор + автоматически запускаем тесты:
```sh
$ ./calc
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