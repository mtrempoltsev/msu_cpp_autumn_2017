#define _CRT_SECURE_NO_WARNINGS

#ifndef _GRAMMAR_HPP_
#define _GRAMMAR_HPP_

#include "Grammar.h"

//=========================================================================================

template<typename T>
GrammarElement<T>::GrammarElement(const char* str, int shift) : string_(str), shift_(shift)
{}

template<typename T>
GrammarElement<T>::~GrammarElement()
{}

//=========================================================================================

template<typename T, typename NextElementType, const BinaryOperations<T>* operations>
BinaryGrammarElement<T, NextElementType, operations>::BinaryGrammarElement(const char* str, int shift) : GrammarElement<T>(str, shift)
{
	Parse_();
}

template<typename T, typename NextElementType, const BinaryOperations<T>* operations>
const BinaryOperation<T>* BinaryGrammarElement<T, NextElementType, operations>::GetOperationFromSymbol_(char symbol_p)
{
	for (unsigned int i = 0; i < operations->size(); ++i)
	{
		if (operations->at(i).first == symbol_p) { return &operations->at(i); }
	}

	return nullptr;
}

template<typename T, typename NextElementType, const BinaryOperations<T>* operations>
void BinaryGrammarElement<T, NextElementType, operations>::Parse_()
{
	if (this->string_[this->shift_] == '\0') { return; } //Ðàçáîð äîøåë äî êîíöà
	const BinaryOperation<T>* current_operation = nullptr;

	while (true)
	{
		this->subelements_.push_back(std::make_unique<NextElementType>(this->string_, this->shift_));
		this->shift_ = this->subelements_ [this->subelements_.size()-1]->GetShift();

		if (this->string_[this->shift_] == '\0') { break; } //Äîøëè äî êîíöà ñòðîêè

		current_operation = GetOperationFromSymbol_(this->string_[this->shift_]);
		if (current_operation == nullptr) { break; }
		else
		{
			opetations_between_arguments_.push_back(current_operation->second);
		}
		this->shift_++;
		if (this->string_[this->shift_] == '\0') { throw std::logic_error("No argument for the last operator!"); }
	}
}

//Îáû÷íûé ïðÿìîé ïîðÿäîê
template<typename T, typename NextElementType, const BinaryOperations<T>* operations>
T BinaryGrammarElement<T, NextElementType, operations>::GetValue() const
{
	CALC_ASSERT(this->subelements_.size() > 0);

	double result = this->subelements_[0]->GetValue();
	for (unsigned int i = 1; i < this->subelements_.size(); ++i)
	{
		result = opetations_between_arguments_[i - 1](result, this->subelements_[i]->GetValue());
	}

	return result;
}

//=========================================================================================

template<typename T, typename lowest_rule_decorator>
AtomicExpression<T, lowest_rule_decorator>::AtomicExpression(const char* str, int shift) : GrammarElement<T>(str, shift)
{
	Parse_();
}

template<typename T, typename lowest_rule_decorator>
void AtomicExpression<T, lowest_rule_decorator>::Parse_()
{
	//Åñëè ñêîáêà
	if (this->string_[this->shift_] == '(')
	{
		this->shift_++;
		if (this->string_[this->shift_] == '\0') { throw std::logic_error("Impaired brackets"); }

		this->subelements_.push_back(std::make_unique<typename lowest_rule_decorator::lowest_rule>(this->string_, this->shift_));
		this->shift_ = this->subelements_ [this->subelements_.size()-1]->GetShift();

		if (this->string_[this->shift_] != ')') { throw std::logic_error("Impaired brackets"); }
		this->shift_++;

		return;
	}

	// Åñëè ÷èñëî
	this->value_ = NumberParser<T>::GetNumber(this->string_, this->shift_);
}

template<typename T, typename lowest_rule_decorator>
T AtomicExpression<T, lowest_rule_decorator>::GetValue() const
{
	return this->subelements_.size() == 0 ? value_ : this->subelements_[0]->GetValue();
}

//=========================================================================================

//Äëÿ ñòåïåíè: îáðàòíûé ïîðÿäîê
//Êîñòûëü, íî øàáëîííàÿ ñïåöèàëèçàöèÿ íå ïîëó÷àåòñÿ. Âîçìîæíî, èç-çà ïñåâäîíèìà.
#define POW_SPECIALIZATION(type) template<> type Pow<type>::GetValue() const\
								 {\
								 	 CALC_ASSERT(this->subelements_.size() > 0);\
						 			 double result = this->subelements_ [this->subelements_.size() - 1]->GetValue();\
									 for (int i = this->subelements_.size()-2; i >= 0; --i)\
									 {\
										 result = opetations_between_arguments_ [i](this->subelements_ [i]->GetValue(), result);\
									 }\
									 return result;\
								 }\

POW_SPECIALIZATION(int)
POW_SPECIALIZATION(double)

//=========================================================================================

template<typename T>
void GetAnyNumber(const char* str, const char* scanf_str, int& shift, T& value, std::function<bool(T)> validation_func)
{
	int count_readed = 0;
	//Çàïðåòèòü óíàðíûé ïëþñ
	if (str[shift] == '+')
	{
		throw std::logic_error("Unary plus is prohibited");
	}

	int result = sscanf(str + shift, scanf_str, &value, &count_readed);
	if (result == 0 || result == EOF)
	{
		std::string exc_str("Wrong syntaxis: ");
		exc_str += (str + shift);
		throw std::logic_error(exc_str.c_str());
	}
	if (!validation_func(value))
	{
		throw std::logic_error("Overflow!");
	}

	shift += count_readed;
}

template<>
int NumberParser<int>::GetNumber(const char* str, int& shift)
{
	long value = 0;
	GetAnyNumber<long>(str, "%ld%n", shift, value, [](long val) {
																    if (val <= std::numeric_limits<int>::min() || val >= std::numeric_limits<int>::max())
																    {
																	    return false;
																    }
																    return true;
															    });
	return value;
}

template<>
double NumberParser<double>::GetNumber(const char* str, int& shift)
{
	double value = 0;
	GetAnyNumber<double>(str, "%lf%n", shift, value, [](double val) {return true; });
	return value;
}

template<>
long NumberParser<long>::GetNumber(const char* str, int& shift)
{
	long value = 0;
	GetAnyNumber<long>(str, "%ld%n", shift, value, [](long val) {return true; });
	return value;
}

//=========================================================================================

template<typename T>
int Calculator<T>::GetValue(std::string& expr)
{
	expr.erase(std::remove(expr.begin(), expr.end(), ' '), expr.end()); //Èãíîðèðóåì ïðîáåëû
	for (auto pair : constants_c)
	{
		expr = std::regex_replace(expr, std::regex(pair.first), pair.second);
	}

	int final_position = 0;
	try //Ìîãóò áûòü èñêëþ÷åíèÿ!
	{
		typename Calculator<T>::lowest_rule grammar(expr.c_str(), 0);
		final_position = grammar.GetShift();

		if (final_position != expr.length()) //Ðàçáîð íå äîøåë äî êîíöà - âåðîÿòíî, âñòðåòèëñÿ íåèçâåñòíûé ñèìâîë
		{
			std::cout << expr << std::endl;
			std::cout << std::string(final_position, ' ') << '^' << std::endl;
			std::cout << "There is in error in the input string near the marked position" << std::endl;
			return ERROR_CODE;
		}
		else
		{
			std::cout << grammar.GetValue() << std::endl;
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return ERROR_CODE;
	}

	return 0;
}

//=========================================================================================

#endif
