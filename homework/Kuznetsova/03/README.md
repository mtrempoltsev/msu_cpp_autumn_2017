Целочисленный калькулятор, разбирающий выражение рекурсивным спуском.

Запуск из командной строки: calc "(5 + 3 * (8 / Pi) * 4) + (1)"

Грамматика калькулятора:
(+ возможны скобки и константы Pi и e)

expr = term
    | expr + term
    | expr - term

term = prim
    | term * prim
    | term / prim

prim = number
    | -number

number = [0-9]+



