# homework 02

## Калькулятор, основанный на методе рекурсивного спуска

Сборка
```make calc```

Грамматика калькулятора
	expr = term
   		| expr + term
		| expr - term
	term = prim
	    | term * prim
    	| term / prim
	prim = number
	    | -number
	number = [0-9]+

Калькулятор работает с целыми числами (int), деление тоже целочисленное
