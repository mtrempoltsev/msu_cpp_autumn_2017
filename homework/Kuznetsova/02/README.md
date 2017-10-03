Целочисленный калькулятор, разбирающий выражение рекурсивным спуском.

Запуск из командной строки: calc "2 + 3 * 4 - -2"

Грамматика калькулятора:

expr = term
    | expr + term
    | expr - term

term = prim
    | term * prim
    | term / prim

prim = number
    | -number

number = [0-9]+




