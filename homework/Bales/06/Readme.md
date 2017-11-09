# Work_06
Необходимо модернизировать [Work_03](https://github.com/mtrempoltsev/msu_cpp_autumn_2017/tree/master/homework/Bales/03):

* Добавить шаблоны
* Добавить парсер, который будет проверять на корректность типы в выражении
* Парсер должен работать с **int**, **long**, **double**
* [Опционально] Теперь калькулятор должен уметь обрабатывать и вещественный тип
* Если в выражении содержатся недопустимые типы, который парсер "не понимает", необходимо бросить исключение

## Пример выражения:
```
(5 + 3 * (8 / Pi) * 4) + (1)
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
Warning: Incorrect type conversion!
Error: look exit code
FailedIntParserForDouble is ended.
Warning: Value out of range!
Error: look exit code
FailedIntParserForLong is ended.
```