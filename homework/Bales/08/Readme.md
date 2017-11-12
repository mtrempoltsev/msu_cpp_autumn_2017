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
Запускаем набор тестов для проверки работоспособности методов **Vector**'а
```sh
$ ./vector
```
Если между строками "... is started!" и "... is ended!" не отображается ошибок => методы работают корректно:
```sh
CheckInit is started!
CheckInit is ended!
CheckPushAndPopBack is started!
CheckPushAndPopBack is ended!
CheckIterators is started!
CheckIterators is ended!
```