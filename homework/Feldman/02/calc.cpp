#include <stdlib.h>
#include <ctype.h>
#include <iostream>
using namespace std;

int select_operation(int a, int b, char op) {//Функция выбора оберации
	switch (op) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			if (b == 0)
				throw -1;
			return a / b;
		default:
			return 0;
	}
}


int expr(char*& str);
int _expr(char*& str, int left_operand);
int term(char*& str);
int _term(char*& str, int left_operand);
int prim(char*& str);
int number(char*& str);

int main(int argc, char** argv) {
	if (argc != 2) { //Количество аргументов командной строки не равно 2
		cout << "Too few arguments!" << endl;
		return -1;
	}
	try {
		cout << expr(argv[1]) << endl;
	}
	catch(int a) {
		if (a == 0) //Неверное выражение
			cout << "INVALID EXPRESSION!" << endl;
	}
	return 0;
}

/*Далее под операндом будем понимать произведение | частное |число 
 * под выражением будем понимать сумму | разность операндов
 */
int expr(char*& str) {
	int left_operand = term(str); //Левый операнд выражения
	if (*str == '+' || *str == '-') { //Если он не единственный
		return _expr(str,left_operand); 
	}
	return left_operand; //Если он единственный
}

int _expr(char*& str, int left_operand) {
	char operation = *str; //Операция между правым и левым операндом
	++str; 
	int right_operand = term(str); //Получаем правый операнд
	if (*str == '\0') {	//Выражение закончилось, возвращаем ответ	
		return select_operation(left_operand,right_operand,operation);;
	}
	else { //В выражении есть другие операнды
		return  _expr(str, select_operation(left_operand,right_operand,operation));
	}
}

int term(char*& str) { 
	int left_part = prim(str); //Вычисление левой части операнда
	if (*str == '*' || *str == '/') {//Если операнд - произведение | частное
		return _term(str,left_part);
	}
	return left_part; //Если операнд - число

}

int _term(char*& str, int left_part) {//Вычисление операнда - левую часть уже вычислили
	char operation = *str;//Операция между частями операнда
	if (operation == '+' || operation == '-') //Если + | - вычисление операнда закончилось
		throw left_part; //Выкидываем результат
	++str;
	int right_part = prim(str); //Вычисляем правую часть
	if (*str == '\0') { //Это был последний операнд
		try {
			//вычисляем значение операнда
			return select_operation(left_part,right_part,operation);
		
		}		
		catch (int a) {
			if (a == -1) { //Спецификация - деление на нуль
				//в ответе получаем мусор
				cout << "DIVISION BY ZERO!" << endl;
			}
		}		
	}
	else { //это был не последний операнд
		int right_term; //Вычисляем дальше операнды справа
		try {
			right_term = _term(str,select_operation(left_part,right_part,operation));
		}
		catch (int a) {
			if (a == -1) { //Опять деление на нуль
				cout << "DIVISION BY ZERO!" << endl;
			}
			return a;	// Ловим то, что выкинули, если встретили + | -		
		}
		return right_term; //возвращаем значение
	}
	return 0;
}

int prim(char*& str) { //Получаем число
	if (*str == '-') { //унарный минус
		++str;
		return -number(str);
	}
	return number(str);
}

int number(char*& str) {
	if (!isdigit(*str)) //Если символ не цифра, кидаем исключение
		throw 0;
	char* str_num = (char*)malloc(sizeof(char));
	int index = 0;	
	while (*str >= '0' && *str <= '9') { //Читаем символы до первого сивола операции		
		str_num[index] = *str;	//записываем их в строку
		++index;
		str_num = (char*)realloc(str_num,(index + 1)*sizeof(char));
		str++;
	}	
	str_num[index] = '\0';	
	int num = atoi(str_num); //Преобразуем char* в int	
	free(str_num);	
	return num; //возвращаем цифру
}






