#pragma once

#ifndef _GRAMMAR_H_
#define _GRAMMAR_H_

//=========================================================================================

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <exception>

#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

#include <math.h>

#define CALC_ASSERT(x) if (!(x)) {throw std::logic_error(#x);}
#define ERROR_CODE 1

//=========================================================================================

//Sum = Mul +<or>- Mul
//Mul = Atomic *<or>/ Atomic
//Atomic = Number <or> '(' Sum ')'
//Number = (-)[0...9].[0...9] <or> Pi <or> e

const std::unordered_map<std::string, std::string> constants_c =
{
	{ "Pi", "3.14" },
	{ "e", "2.7" }
};


//GrammarElement строит дерево разбора. ƒерево нужно, потому что некоторые операции выполн€ютс€ справа налево, а некоторые слева направо
template <typename T>
class GrammarElement
{
	protected:
		const char* string_; //—трока дл€ разбора (без смещени€)
		int shift_; //“екущее смещение

		std::vector<GrammarElement*> subelements_; //ѕодчиненные элементы

	protected:
		virtual void Parse_() = 0; //¬ыдел€ет подэлементы

	public:
		GrammarElement(const char* str, int shift);
		virtual T GetValue() const = 0; //¬озвращает значение в узле

		int GetShift() const { return shift_; }

		virtual ~GrammarElement();
};

//=========================================================================================

//ƒалее везде в шаблонах T - тип чисел, обрабатываемых калькул€тором

template <typename T>
using BinaryOperationFunction = std::function<T(T, T)>;

template <typename T>
using BinaryOperation = std::pair<char, BinaryOperationFunction<T> >;

template <typename T>
using BinaryOperations = std::vector<BinaryOperation<T> >;

//“ип operations должен содержать статическую переменную operations типа BinaryOperations, описывающую возможные действи€ дл€ правила грамматики
//NextElementType - правило более высокого приоритета
template<typename T, typename NextElementType, const BinaryOperations<T>* operations>
class BinaryGrammarElement : public GrammarElement<T>
{
	protected:
		std::vector<BinaryOperationFunction<T>> opetations_between_arguments_; //«апоминает операции между аргументами - из operations

	protected:
		virtual void Parse_();

		static const BinaryOperation<T>* GetOperationFromSymbol_(char symbol_p);

	public:
		BinaryGrammarElement(const char* str, int shift);

		virtual T GetValue() const;
};

//=========================================================================================

template<typename T>
class NumberParser
{
	public:
		static T GetNumber(const char* str, int& shift);
};

//AtomicExpression - самое базовое правило. ќно принимает тип чисел калькул€тора и класс-декоратор правила низшего приоритета.
template <typename T, typename lowest_rule_decorator>
class AtomicExpression : public GrammarElement<T>
{
	protected:
		T value_;

	protected:
		virtual void Parse_();

	public:
		AtomicExpression(const char* str, int shift);

		virtual T GetValue() const;
};

//=========================================================================================

//«адача класса: обеспечивать передачу пользовательского типа в иерархию классов грамматики, считать выражени€ (создава€ корневой объект грамматики)
//ƒополнительна€ задача: декорировать lowest_rule дл€ AtomicExpression
template <typename T>
class Calculator;

//ƒл€ добавлени€ бинарной операции (шаблонна€, тип T): создаетс€ структура (чтобы была возможность шаблона),
//котора€ содержит BinaryOperations дл€ передачи в BinaryGrammarElement
//name_operation - им€ класса декларируемой бинарной операции
//next_operation - им€ класса следующей по приоритету операции
#define DEFINE_BINARY_OPERATION(name_operation, next_operation, ...)\
										struct name_operation##_struct_operations\
										{\
											static const BinaryOperations<T> operations;\
										};\
										template<typename T>\
										const BinaryOperations<T> name_operation##_struct_operations<T>::operations = __VA_ARGS__;\
										template <typename T>\
										using name_operation = BinaryGrammarElement<T, next_operation,\
																				    &name_operation##_struct_operations<T>::operations>

//—пецификаци€ бинарной грамматики
template<typename T>
using AtomicExpressionSpecified = AtomicExpression<T, Calculator<T>>;

template<typename T>
DEFINE_BINARY_OPERATION(Pow, AtomicExpressionSpecified<T>, {\
															   {'^', [](T a, T b)\
																     {\
																	     if (b == 0.0) { return (T) 1.0; }\
																	     return (T) pow(a, b);\
															         }\
														       }\
											               });

template<typename T>
DEFINE_BINARY_OPERATION(MultiplicationDivision, Pow<T>, {\
														     {'*', [](T a, T b) { return a * b; }},\
														     {'/', [](T a, T b)\
																   {\
																        if (b == 0) { throw std::invalid_argument("Dividing by zero!"); }\
																        return a / b;\
															       }\
														     }\
													    });

template<typename T>
DEFINE_BINARY_OPERATION(SumDifference, MultiplicationDivision<T>, {\
																	  {'+', [](T a, T b) { return a + b; }},\
																	  {'-', [](T a, T b) { return a - b; }}\
															      });

// ƒекорирование самого низкоприоритетного правила
template <typename T>
class Calculator
{
	public:
		typedef T calc_type;
		typedef SumDifference<T> lowest_rule;

	public:
		//¬озвращает код ошибки
		static int GetValue(std::string& str);
};

//=========================================================================================

#endif