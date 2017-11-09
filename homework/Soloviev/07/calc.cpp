#include <iostream>
#include <limits>
#include <string.h>
#include <unordered_map>
#include <string>
#include <exception>

using std::runtime_error;

std::unordered_map<std::string, double> constants = 
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };

//Exception classes
class WrongExprFormatException: public runtime_error{
public:
	WrongExprFormatException():runtime_error("Wrong expression format"){}
};

class ZeroDivisionException: public runtime_error{
public:
	ZeroDivisionException():runtime_error("Zero division"){}
};

class NotANumberException: public runtime_error{
public:
	NotANumberException():runtime_error("Not a number"){}
};

class UneqParenthException: public runtime_error{
public:
	UneqParenthException():runtime_error("Unequal paranthesis"){}
};

class OutOfRangeException: public runtime_error{
public:
	OutOfRangeException():runtime_error("Number is out of range"){}
};

class WrongParseFormatException: public runtime_error{
public:
	WrongParseFormatException():runtime_error("Wrong parser format"){}
};

//Properties structure
//Use to get access to max an min values of int, long, double
template <typename T>
struct NumericTraits
{
};

template <>
struct NumericTraits<int>
{
    static constexpr int min = std::numeric_limits<int>::min();
    static constexpr int max = std::numeric_limits<int>::max();
};

template <>
struct NumericTraits<long>
{
    static constexpr long min = std::numeric_limits<long>::min();
    static constexpr long max = std::numeric_limits<long>::max();
};

template <>
struct NumericTraits<double>
{
    static constexpr double min = std::numeric_limits<double>::min();
    static constexpr double max = std::numeric_limits<double>::max();
};

//Parser classes
//Throws exception if value is not in between min and max or has wrong format
class parser_Int{
public:
	int parse(const std::string data){
		long res;

		for(uint i = 0; i < data.size(); i++)
			if(data[i] == '.')
				throw WrongParseFormatException();

		res = std::stol(data);

		if(res < NumericTraits<int>::min || res > NumericTraits<int>::max)
			throw OutOfRangeException();

		return res;
	}
};

class parser_Long{
public:
	long parse(const std::string data){
		long res;

		for(uint i = 0; i < data.size(); i++)
			if(data[i] == '.')
				throw WrongParseFormatException();

		res = std::stol(data);

		if(res < NumericTraits<long>::min || res > NumericTraits<long>::max)
			throw OutOfRangeException();
		
		return res;
	}
};

class parser_Double{
public:
	double parse(const std::string data){
		double res;

		res = std::stod(data);

		if(res < NumericTraits<double>::min || res > NumericTraits<double>::max)
			throw OutOfRangeException();
		
		return res;
	}
};

// exp_p_m -> exp_m_d{+ exp_m_d} | exp_m_d{- exp_m_d}
// exp_m_d -> exp_neg{* exp_neg} | exp_neg{/ exp_neg}
// exp_neg -> -exp_n | (exp_p_m) | exp_n
// exp_n-> [0-9]{[0-9]}

template <typename T, typename Parser>
class Calculator{
public:
	T calculate(const char* str){
		counter = 0;

		for(uint i = 0; i < strlen(str) + 1; i++)
			if(str[i] !=  ' ')
				expr += str[i];
		
		T res;

		res = start();
		
		return res;
	}

private:
	std::string expr; //Pointer to the string containing expression
	int counter = 0;      //Iterator over the expression
	Parser parser;

	T start(){

		T res = exp_p_m();

		if(expr[counter] != '\0')
			throw WrongExprFormatException();

		return res;
	}

	T exp_p_m(){

		T res = exp_m_d();

		while(expr[counter] == '+' || expr[counter] == '-'){
			
			counter++;

			if(expr[counter - 1] == '+')
				res += exp_m_d();
			else
				res -= exp_m_d();
		}

		return res;
	}

	T exp_m_d(){

		T res = exp_neg();

		while(expr[counter] == '*' || expr[counter] == '/'){

			counter++;

			if(expr[counter - 1] == '*')
				res *= exp_neg();
			else{
				T tmp = exp_neg();
				//Check for zero division
				if(tmp == 0)
					throw ZeroDivisionException();
				res /= tmp;
			}
		}

		return res;
	}

	T exp_neg(){

		if(expr[counter] == '-')
		{
			counter++;
			return -exp_n();
		}else if(expr[counter] == '(')
		{
			counter++;
			T res = exp_p_m();
			//Check for equal paranthesis
			if(expr[counter] == ')'){
				counter++;
				return res;
			}
			else
				throw UneqParenthException();
		}else
			return exp_n();
	}

	T exp_n(){

		T res;

		//Check for consts
		if(expr[counter] == 'P'){
			counter += 2;
			return constants["Pi"];
		}

		if(expr[counter] == 'e'){
			counter++;
			return constants["e"];
		}

		//Check if a number
		if((expr[counter] < '0' || expr[counter] > '9') && expr[counter] != '.')
			throw NotANumberException();

		//Counting the size of number
		int size = 0;
		while((expr[counter + size] >= '0' && expr[counter + size] <= '9') || expr[counter + size] == '.')
			size++;

		//Parsing number
		res = parser.parse(expr.substr(counter, size));
		counter += size;

		return res;
	}
};

int main(int argc, char* argv[]){

	//Check if there is enough args
	if(argc != 2){
		std::cout << "Wrong number of arguments\n";
		return 1;
	}

	Calculator<int, parser_Int> calc;
	int res;

	try
	{
		res = calc.calculate(argv[1]);
	}
	catch(runtime_error& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	std::cout << res << std::endl;

	return 0;
}