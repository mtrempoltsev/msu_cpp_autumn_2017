# Калькулятор
Программа предаставляет собой улучшенный калькулятор,
поддерживающий операции **+ - * /**, константы **Pi**, **e** и **вложенные выражения**.
### Сборка и тестирование
для сборки используйте комманду ```make```, для тестирования ```make test```
### Использование
```
Input : ./calc '1 - 2*(3+4)'
Output: -13
```
### Грамматика
```
<expr> ::= <term> | <expr> + <term> | <expr> - <term>
<term> ::= <prim> | <term> * <prim> | <term> / <prim>
<prim> ::= <factor> | - <factor>
<factor> ::= <number> | <constant> | ( <expr> )
<number> ::= [0-9]+
<constant> ::= [a-zA-Z]+
```
### Диагностика ошибок
При получение некорректной строки программа выводит сообщение об ошибке, например
```
Input : ./calc '1-2+'
Output: Erorr: number, constant or subexpression expected
        1-2+
            ^
```