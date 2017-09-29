#ifndef _PARSER_H_
#define _PARSER_H_

//=========================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <cassert>
#include <algorithm>

//=========================================================================================

struct BinaryOperation
{
	using BinaryFunction = std::function<int(int, int)>;

	char symbol;
	BinaryFunction function;
};

struct BinaryGrammarElement
{
	std::vector<BinaryOperation> operations;
	const BinaryGrammarElement* higher_priority_element; //Если NULL, то это бинарная операция с наивысшим приоритетом => она уже будет вызывать GetNumber

	const BinaryOperation* GetOperationFromSymbol(char symbol_p) const; //Т.к. хотим возвращать nullptr, если не найдено, а это - только указатель
};

//-----------------------------------------------------------------------------------------

//Наша грамматика
const BinaryGrammarElement Grammar_c [] =
	{
		//+; -
		{
			{
				{'+', [](int a, int b) {return a + b; }},
				{'-', [](int a, int b) {return a - b; }}
			},
			&Grammar_c [1]
		},
		//*; /
		{
			{
				{'*', [](int a, int b) {return a * b; }},
				{'/', [](int a, int b) //Деление на 0 требует особого внимания
					  {
						   if (b == 0) { throw std::invalid_argument("Dividing by zero!"); }
					       return a / b;
					  }}
			},
			nullptr
		},
	};

//=========================================================================================

//Получает из строки целое число, начиная с указанной позиции
//Возвращает позицию в строке сразу после окончания числа или (-start-1), если ошибка. -1 еще нужно, т.к. может быть start = 0, а -0 = 0 - корр. позиция
int GetNumberFromString(const std::string& str, int start, int& result);

//Вызывает старшее правило граматики (по отношению к element) или GetNumber, если такого нет
int GetOperandFromString(const std::string& str, int start, const BinaryGrammarElement& element, int& result);

//Разбирает строку, начиная с момента start и до тех пор, пока применимо правило элемента element (не встретился неизвестный знак), вызывая более приоритетные правила
//Возвращает позицию окончания своего разбора или (-start-1), если ошибка
//Записывает в result результат применения более приоритетного правила грамматики, даже если сама функция не проводила никаких операций на своем уровне грамматики
//first_call - параметр, указывающий, был ли уже получен первый аргумент (потому что со второго раза start будет указывать на знак операции, а промежуточный итог уже будет в result)
int GetBinaryGrammarElementFromString(const std::string& str, int start, const BinaryGrammarElement& element, int& result, bool first_call);

//=========================================================================================

#endif
