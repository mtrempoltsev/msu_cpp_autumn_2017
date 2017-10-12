#define _CRT_SECURE_NO_WARNINGS

#include <math.h>

#include "Grammar.h"

//=========================================================================================

GrammarElement::GrammarElement(const char* str, int shift) : string_(str), shift_(shift)
{}

GrammarElement::~GrammarElement()
{
	for (unsigned int i = 0; i < subelements_.size(); ++i)
	{
		delete subelements_ [i];
	}
}

//=========================================================================================

template<typename NextElementType, typename operations>
BinaryGrammarElement<NextElementType, operations>::BinaryGrammarElement (const char* str, int shift) : GrammarElement(str, shift)
{
	Parse_();
}

//Без этого линкер g++ отказывается собирать
template<> SumDifference::BinaryGrammarElement(const char* str, int shift) : GrammarElement(str, shift)
{
	Parse_();
}

template<typename NextElementType, typename operations>
const BinaryOperation* BinaryGrammarElement<NextElementType, operations>::GetOperationFromSymbol_(char symbol_p)
{
	for (unsigned int i = 0; i < operations::operations.size(); ++i)
	{
		if (operations::operations [i].first == symbol_p) { return &operations::operations [i]; }
	}

	return nullptr;
}

template<typename NextElementType, typename operations>
void BinaryGrammarElement<NextElementType, operations>::Parse_()
{
	if (string_ [shift_] == '\0') { return; } //Разбор дошел до конца
	const BinaryOperation* current_operation = nullptr;

	while (true)
	{
		NextElementType* new_element = new NextElementType(string_, shift_);
		subelements_.push_back(new_element);
		shift_ = new_element->GetShift();

		if (string_ [shift_] == '\0') { break; } //Дошли до конца строки

		current_operation = GetOperationFromSymbol_(string_ [shift_]);
		if (current_operation == nullptr) { break; }
		else
		{
			opetations_between_arguments_.push_back(current_operation->second);
		}
		shift_++;
		if (string_ [shift_] == '\0') { throw std::logic_error("No argument for the last operator!"); }
	}
}

//Обычный прямой порядок
template<typename NextElementType, typename operations>
double BinaryGrammarElement<NextElementType, operations>::GetValue() const
{
	CALC_ASSERT(subelements_.size() > 0);

	double result = subelements_ [0]->GetValue();
	for (unsigned int i = 1; i < subelements_.size(); ++i)
	{
		result = opetations_between_arguments_ [i-1](result, subelements_ [i]->GetValue());
	}

	return result;
}

//Для степени: обратный порядок
template<> double Pow::GetValue() const
{
	CALC_ASSERT(subelements_.size() > 0);

	double result = subelements_ [subelements_.size() - 1]->GetValue();
	for (int i = subelements_.size()-2; i >= 0; --i)
	{
		result = opetations_between_arguments_ [i](subelements_ [i]->GetValue(), result);
	}

	return result;
}


//=========================================================================================

AtomicExpression::AtomicExpression(const char* str, int shift) : GrammarElement(str, shift)
{
	Parse_();
}

void AtomicExpression::Parse_()
{
	//Если скобка
	if (string_ [shift_] == '(')
	{
		shift_++;
		if (string_ [shift_] == '\0') { throw std::logic_error("Impaired brackets"); }

		SumDifference* new_element = new SumDifference(string_, shift_);
		subelements_.push_back(new_element);
		shift_ = new_element->GetShift();

		if (string_ [shift_] != ')') { throw std::logic_error("Impaired brackets"); }
		shift_++;

		return;
	}

	//Если число
	int count_readed = 0;
	int result = sscanf(string_+shift_, "%lf%n", &value_, &count_readed);
	if (result == 0 || result == EOF)
	{
		std::string exc_str("Wrong syntaxis: ");
		exc_str += (string_ + shift_);
		throw std::logic_error(exc_str.c_str());
	}
	shift_ += count_readed;
}

double AtomicExpression::GetValue() const
{
	return subelements_.size() == 0 ? value_ : subelements_ [0]->GetValue();
}

//=========================================================================================

//Спецификация бинарной грамматики
const BinaryOperations PowOperations::operations =
{
	{'^', [](double a, double b)
		  { 
			   if (b == 0.0) { return 1.0; }
		       return pow(a, b); 
		  }}
};
const BinaryOperations MulDivOperations::operations =
{
	{'*', [](double a, double b) { return a * b; }},
	{'/', [](double a, double b) //Деление на 0 требует особого внимания
		  {
		      if (b == 0) { throw std::invalid_argument("Dividing by zero!"); }
			  return a / b;
		  }
	}
};
const BinaryOperations SumDiffOperation::operations =
{
	{'+', [](double a, double b) { return a + b; }},
	{'-', [](double a, double b) { return a - b; }}
};