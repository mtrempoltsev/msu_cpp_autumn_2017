// Simple calculator

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

using namespace std;

int expr(char*& str);
int _expr(char*& str, int left_operand);
int term(char*& str);
int _term(char*& str, int left_operand);
int prim(char*& str);
int number(char*& str);

int select_operation( int a, int b, char op) {
	switch (op) {
		case '+':return a + b;
		case '-':return a - b;
		case '*':return a * b;
		case '/':if (b == 0)
				throw - 1;
			return a / b;
		default:
			return 0;
	}
}

void deleteSpace(char* src) {
	char* dets = src;
	while ((*dets = *src++))
		if (*dets != ' ')
			dets++;
}


int main(int argc, char* argv[]) {
	if (argc != 2) { 
		cout << "Something was wrong" << endl;
		return 1;
	}

	deleteSpace(argv[1]);
	
	for (int i = 0; argv[1][i] != '\0'; ++i) {
		if ((argv[1][i] == '+' || argv[1][i] == '-' || argv[1][i] == '*' || argv[1][i] == '/'))
			if (argv[1][i + 1] != '-' && !(isdigit(argv[1][i + 1]))) {
				cout << "Invalid Expression" << endl;
				return 1;
			}
		if (!isdigit(argv[1][i]))
			if (argv[1][i] != '+' && argv[1][i] != '-' && argv[1][i] != '*' && argv[1][i] != '/') {
				cout << "Invalid Expression" << endl;
				return 1;
			}
	}
	try {
		cout << expr(argv[1]) << endl;
	}
	catch (const char* text) {
		cout << text << endl;
		return 1;
	}
	return 0;
}

// *|/| number
// +|-
int expr(char*& str) {
	int left_operand = term(str);
	if (*str == '+' || *str == '-') { 
		return _expr(str, left_operand);
	}
	return left_operand; // just one operand
}

int _expr(char*& str, int left_operand) {
	char operation = *str; 
	++str;
	int right_operand = term(str); 
	if (*str == '\0') {		
		return select_operation(left_operand, right_operand, operation);;
	}
	else { // another operand
		return  _expr(str, select_operation(left_operand, right_operand, operation));
	}
}

//Unary minus
int prim(char*& str) { 
	if (*str == '-') { 
		++str;
		return -number(str);
	}
	return number(str);
}

int term(char*& str) {
	int left_part = prim(str); 
	if (*str == '*' || *str == '/') {
		return _term(str, left_part);
	}
	return left_part; // if it number
}

int _term(char*& str, int left_part) {
	char operation = *str;
	if (operation == '+' || operation == '-') 
		throw left_part; 
	++str;
	int right_part = prim(str); 
	if (*str == '\0') { 
		try {
			return select_operation(left_part, right_part, operation); // result
		}
		catch (int a) {
			if (a == -1) { // div by 0
				throw "Division by zero is impossible";
			}
		}
	}
	else { 
		int right_term; 
		try {
			right_term = _term(str, select_operation(left_part, right_part, operation));
		}
		catch (int a) {
			if (a == -1) { 
				throw "Division by zero is impossible";
			}
			return a;	
		}
		return right_term; // result
	}
	return 0;
}

int number(char*& str) {
	char* str_numb = (char*)malloc(sizeof(char));
	int i = 0;
	while (*str >= '0' && *str <= '9') { 		
		str_numb[i] = *str;
		++i;
		str_numb = (char*)realloc(str_numb, (i + 1)*sizeof(char));
		str++;
	}
	str_numb[i] = '\0';
	int numb = atoi(str_numb); //  char* -> int	
	free(str_numb);
	return numb; 
}
