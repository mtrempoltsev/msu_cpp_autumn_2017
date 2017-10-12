### Компиляция

```sh
$ make
```

### Использование

```sh
$./calc "(5 + 3 * (8 / Pi) * 4) + -(-1)"
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
number = [0-9]+ | expr
```

### Описание

Класс RDParser построен по шаблону Singleton, который обеспечивает существование единственного экземпляра в программе.
