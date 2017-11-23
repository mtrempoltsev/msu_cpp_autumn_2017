#include <iostream>
#include <limits>
#include <unordered_map>
#include "Parser.h"
using namespace std;

class Error {
public:
    Error(std::string msg, int code): msg(msg), code(code) {}

    void print() const {
        printf("Code: %d. %s\n", this->code, this->msg.c_str());
    }

    std::string msg;
    int code;
};

std::unordered_map<std::string, double> constants =
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };

enum symbol{
	start,
	plus,
	minus,
	multiply,
	divide,
	number,
	exp,
	Pi,
	open_br,
	close_br,
	wrong,
	end
};

template <class T>
class NumericLimits{
public:
	static constexpr T min = std::numeric_limits<T>::lowest();
	static constexpr T max = std::numeric_limits<T>::max();
};

template <class T, class Parser>
class Calculator{
	public:
		Calculator(const char* text){
			input=text;
			curr=start;
			inverse=0;
			bracket_count=0;
		};
		T expr();
		bool check_brackets();
		T answer;
	private:
		Parser pars;
		T term(int inverse);
		T prim();
		int inverse;
		int bracket_count;
		const char* input;
		symbol next();
		symbol curr;
		symbol s;
		symbol s_prev;
 
};	

template <class T, class Parser>		
bool Calculator<T, Parser>::check_brackets(){ //проверяем количество скобок
	if (bracket_count!=0)
		return false;
	else
		return true;
}

template <class T, class Parser>
symbol Calculator<T, Parser>::next(){  //смотрим какой объект сейчас считываем
	while (char curr=*input++){
		s_prev=s;
		switch (curr){
			case ' ': continue;
			case '(': return symbol::open_br;
			case ')': return symbol::close_br;
			case '+': {
					if (s_prev==symbol::open_br){
						throw Error("Wrong input (+", 5);
					}
					return symbol::plus;
			}
			case '-': return symbol::minus;
			case '*': {
					if (s_prev==symbol::open_br){
						throw Error("Wrong input (*", 5);
					}
					return symbol::multiply;
			}
			case '/': {
					if (s_prev==symbol::open_br){
						throw Error("Wrong input (/", 5);
					}
					return symbol::divide;
			}
			case 'e': return symbol::exp;
			case 'P': {
				curr=*input++;
				if (curr=='i')
					return symbol::Pi;
				else{
					throw Error("Wrong input", 3);
				}				 
			}
		}
		if ((curr>='0')&&(curr<='9'))
			return symbol::number;
		else{
			throw Error("Wrong input", 3); //проверяем, что введены только цифры или +,-,*,/	
		}
		}
	return symbol::end;
}

template <class T, class Parser>
T Calculator<T, Parser>::expr() //разбиваем на слагаемые
{
	T res=term(inverse=0);
	if (s==symbol::close_br){
		s_prev=symbol::close_br;
		bracket_count--;
		return res;
	}
	if (s==symbol::end)
		return res; 
	s=next();	
	
	if (s!=symbol::end)
		return s==symbol::plus ? res+expr() : res-expr();
	else
		return res;
}

template <class T, class Parser>
T Calculator<T, Parser>::term(int inverse) //разбиваем на множители 
{
	double res=prim(); //  6/2*2 воспринимается, как 6/(2*2), значит если было деление, то следующую операцию необходимо инвертировать	
	if (s==symbol::end)
		return res;
	s=next();
	bool flag=(inverse & 1);
	if ((s==symbol::multiply)||(s==symbol::divide)){
		if (s==symbol::divide){ //деление
			inverse++;
			int check=term(inverse);

			if (check==0)//проверка деления на ноль
			{
				throw Error("Zero division error", 1);
			}	

			if (flag){

				return res*check;
			}
			else{ 
			
				return res/check;
			}
			
		}

		if (s==symbol::multiply){ //умножение
			if (flag){

				return res/term(inverse);
			}
			else 

				return res*term(inverse);
		}

	}
	if (s==symbol::close_br)
		return res;
	--input; //могли считать + или -, а не * или / => возвращаем в input
	return res;
	
}

template <class T, class Parser>
T Calculator<T, Parser>::prim() //считывание числа
{
	s=next();
	double res=0;
	string number_as_str;
	if ((s_prev!=symbol::close_br)&&(s_prev!=symbol::open_br)){
		if ((s==symbol::plus)||(s==symbol::divide)||(s==symbol::multiply)){ 
			throw Error("Two or more operations is a row", 4); //проверяем, что подряд не идут операции, или операция и )
		}
		if (s==symbol::close_br){
			throw Error("Operation and ) in a row", 5);
		}
	}
	if ((s_prev==symbol::open_br)&&(s==symbol::close_br)){
		throw Error("Nothing in brackets", 6);
	}
	if (s==symbol::number) {
		input--;
		char currs=*input;
		while (((currs>='0')&&(currs<='9')) || (currs == '.')){
			number_as_str.push_back(currs); 
			currs=*++input;
		if (currs=='\0')
			s=symbol::end;
		}
		res = pars.str_to_d(number_as_str);
		if (!pars.check(number_as_str)){
			throw Error("Wrong type", 8);
		}
		NumericLimits<T> lim;
		if ((res > lim.max)||(res< lim.min)){
			throw Error("Number is out of range", 7);
		}	
		return res;
	}
	if (s==symbol::minus)  return -prim(); 
	if (s==symbol::exp){
		if (pars.check("2.7"))
			return constants["e"];
		else{
			throw Error("Wrong type", 8);
		}
	}
	if (s==symbol::Pi){
		if (pars.check("3.14"))
			return constants["Pi"];
		else{
			throw Error("Wrong type", 8);
		}
	}
	if (s==symbol::open_br)  {bracket_count++;res=expr(); return res;}
	if (s==symbol::close_br) {bracket_count--;return res;}

	return res;
}


int main(int argc, const char* argv[])
{
	//проверяем, сколько ввели параметров в командной строке
	if (argc!=2){
		cout<<"Wrong number of arguments"<<endl;
		return 2;
	}

	const char* input=argv[1];
	Calculator<int, Parser<int>> calc(input);
	
	try{
		auto result=calc.expr();

		if (calc.check_brackets() != 1)
			throw Error("Wrong number of brackets", 4);

		std::cout << result << std::endl;
	}
	catch (const Error& error){ // в сообщении об ошибке первый символ - номер ошибки
		error.print();
	}
	catch (...){
		std::cout << "Some error" << std::endl;
		return 10;
	}
	
	return 0;
}


