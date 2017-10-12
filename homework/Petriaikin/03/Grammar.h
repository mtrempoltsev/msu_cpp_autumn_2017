#pragma once

#ifndef _GRAMMAR_ELEMENT_H_
#define _GRAMMAR_ELEMENT_H_

//=========================================================================================

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <exception>

#define CALC_ASSERT(x) if (!(x)) {throw std::logic_error(#x);}

//=========================================================================================

//Sum = Mul +<or>- Mul
//Mul = Atomic *<or>/ Atomic
//Atomic = Number <or> '(' Sum ')'
//Number = (-)[0...9].[0...9] <or> Pi <or> e

//GrammarElement строит дерево разбора. ƒерево нужно, потому что некоторые операции выполн€ютс€ справа налево, а некоторые слева направо
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
		virtual double GetValue() const = 0; //¬озвращает значение в узле

		int GetShift() const { return shift_; }

		virtual ~GrammarElement();
};

//=========================================================================================

using BinaryOperationFunction = std::function<double(double, double)>;
using BinaryOperation  = std::pair<char, BinaryOperationFunction>;
using BinaryOperations = std::vector<BinaryOperation>;

//“ип operations должен содержать статическую переменную operations типа BinaryOperations, описывающую возможные действи€ дл€ правила грамматики
//NextElementType - правило более высокого приоритета
template<typename NextElementType, typename operations>
class BinaryGrammarElement : public GrammarElement
{
	protected:
		std::vector<BinaryOperationFunction> opetations_between_arguments_; //«апоминает операции между аргументами - из operations

	protected:
		virtual void Parse_();

		static const BinaryOperation* GetOperationFromSymbol_(char symbol_p);

	public:
		BinaryGrammarElement(const char* str, int shift);

		virtual double GetValue() const;
};

//=========================================================================================

//lower_rule - правило грамматики, которое будет сто€ть в скобках - не получаетс€, требуетс€ циклический шаблон
class AtomicExpression : public GrammarElement
{
	protected:
		double value_;

	protected:
		virtual void Parse_();

	public:
		AtomicExpression(const char* str, int shift);

		virtual double GetValue() const;
};

//=========================================================================================

//ƒл€ добавлени€ бинарной операции: создаетс€ структура, котора€ содержит BinaryOperation дл€ передачи в BinaryGrammarElement
//Ќова€ спецификаци€ BinaryGrammarElement именуетс€ (дл€ возможного изменени€ поведени€, например, в случае степени - другой пор€док исполнени€)

//name_operation - им€ класса декларируемой бинарной операции
//next_operation - им€ класса следующей по приоритету операции
//name_struct - вспомогательное им€ структуры
//ѕосле добавлени€ нужно инициализировать name_operation::operations в cpp файле

#define DEFINE_BINARY_OPERATION(name_operation, next_operation, name_struct)\
										struct name_struct {static const BinaryOperations operations;};\
										using name_operation = BinaryGrammarElement<next_operation, name_struct>

DEFINE_BINARY_OPERATION(Pow, AtomicExpression, PowOperations); //Ќе получаетс€ построить шаблонный AtomicExpression - циклический шаблон!
DEFINE_BINARY_OPERATION(MultiplicationDivision, Pow, MulDivOperations);
DEFINE_BINARY_OPERATION(SumDifference, MultiplicationDivision, SumDiffOperation);

//=========================================================================================

#endif