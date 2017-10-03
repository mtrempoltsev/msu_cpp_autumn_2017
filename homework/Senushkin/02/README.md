### Компиляция

```sh
$ make
```

Компиляция утилиты с отладочной информацией:
```sh
$ make debug
```

### Использование

```sh
$./clclt "10 / 2 * 3 - -2"
```

### Грамматика

```
expr = term
    | expr + term
    | expr - term
term = prim
    | term * prim
    | term / prim
prim = number
    | -number
number = [0-9]+
```

