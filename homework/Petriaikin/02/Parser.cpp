#include "Parser.h"

//=========================================================================================

const BinaryOperation* BinaryGrammarElement::GetOperationFromSymbol(char symbol_p) const
{
	int size = operations.size();
	for (int i = 0; i < size; i++)
	{
		if (operations [i].symbol == symbol_p) { return &(operations [i]); }
	}
	return nullptr;
}

//=========================================================================================

int GetNumberFromString(const std::string& str, int start, int& result)
{
	int str_len = str.length();
	assert(start < str_len);

	int end = start;
	if (str [end] == '-') { end++; } //Разрешаем унарный минус

	while (str [end] >= '0' && str [end] <= '9' && end < str_len) { ++end; }

	try { result = std::stoi(str.substr(start, end - start)); }
	catch (...) { return -start - 1; } //Все равно как ошибку напишем на первой позиции "числа с ошибкой"

	return end;
}

int GetOperandFromString(const std::string& str, int start, const BinaryGrammarElement& element, int& result)
{
	int current_position = start;

	if (element.higher_priority_element == nullptr) { current_position = GetNumberFromString(str, start, result); }
	//Переход на новый уровень грамматики подразумевает first_call = true
	else { current_position = GetBinaryGrammarElementFromString(str, start, *element.higher_priority_element, result, true); }

	return current_position;
}

int GetBinaryGrammarElementFromString(const std::string& str, int start, const BinaryGrammarElement& element, int& result, bool first_call)
{
	int str_len = str.length();
	if (start >= str_len) { return start; } //Разбор дошел до конца

	int second_operand = 0;
	int current_position = start;

	if (first_call) { current_position = GetOperandFromString(str, current_position, element, result); }
	if (current_position >= str_len || current_position < 0) { return current_position; } //При ошибке или при достижении конца строки - возврат

	const BinaryOperation* current_operation = element.GetOperationFromSymbol(str [current_position]);
	if (current_operation == nullptr) //Если nullptr, то это операция, которую мы не можем распознать => возврат
	{
		return current_position;
	}
	else //Чтобы начать получать второй аргумент
	{
		++current_position;
		if (current_position >= str_len) { return -str_len - 1; } //"Висячий" оператор в конце строки
	}

	current_position = GetOperandFromString(str, current_position, element, second_operand);
	if (current_position < 0) { return current_position; } //Если ошибка. Если конец строки - это зафиксирует следующий вызов функции

	result = current_operation->function(result, second_operand);

	//Попытаемся получить следующую операцию на нашем уровне грамматики
	return GetBinaryGrammarElementFromString(str, current_position, element, result, false);
}