#include <iostream>
#include <limits>
#include <string.h>
#include <stdio.h>
#include <unordered_map>

std::unordered_map<std::string, double> constants = 
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
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
	int parse(const char* data, size_t size){
		long res;
		char* parse_data = new char[size + 1];

		for(uint i = 0; i < size; i++){
			parse_data[i] = data[i];

			if(data[i] == '.'){
				delete [] parse_data;
				throw 5;
			}
		}
		parse_data[size] = '\0';

		sscanf(parse_data, "%ld", &res);

		try
		{
			if(res < NumericTraits<int>::min || res > NumericTraits<int>::max)
				throw 4;
		}
		catch(...){
			delete [] parse_data;
			throw;
		}

		delete [] parse_data;

		return res;
	}
};

class parser_Long{
public:
	long parse(const char* data, size_t size){
		long res;
		char* parse_data = new char[size + 1];

		for(uint i = 0; i < size; i++){
			parse_data[i] = data[i];

			if(data[i] == '.'){
				delete [] parse_data;
				throw 5;
			}
		}
		parse_data[size] = '\0';

		sscanf(parse_data, "%ld", &res);

		try
		{
			if(res < NumericTraits<long>::min || res > NumericTraits<long>::max)
				throw 4;
		}
		catch(...){
			delete [] parse_data;
			throw;
		}

		delete [] parse_data;

		return res;
	}
};

class parser_Double{
public:
	double parse(const char* data, size_t size){
		double res;
		char* parse_data = new char[size + 1];

		for(uint i = 0; i < size; i++)
			parse_data[i] = data[i];
		parse_data[size] = '\0';

		sscanf(parse_data, "%lf", &res);

		try
		{
			if(res < NumericTraits<double>::min || res > NumericTraits<double>::max)
				throw 4;
		}
		catch(...){
			delete [] parse_data;
			throw;
		}

		delete [] parse_data;

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
		expr = new char[strlen(str) + 1];
		int n = 0;
		T res;

		for(uint i = 0; i < strlen(str); i++)
			if(str[i] != ' ')
				expr[n++] = str[i];

		expr[n] = '\0';

		try{
			res = start();
		}catch(int){
			delete [] expr;
			throw;
		}

		delete [] expr;

		return res;
	}

private:
	char* expr = nullptr; //Pointer to the string containing expression
	int counter = 0;      //Iterator over the expression
	Parser parser;

	T start(){
		T res = exp_p_m();

		if(expr[counter] != '\0')
			throw 0;

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
					throw 1;
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
				throw 3;
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
			throw 2;

		//Counting the size of number
		int size = 0;
		while((expr[counter + size] >= '0' && expr[counter + size] <= '9') || expr[counter + size] == '.')
			size++;

		//Parsing number
		res = parser.parse(expr + counter, size);
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

	Calculator<double, parser_Double> calc;
	double res;

	try
	{
		res = calc.calculate(argv[1]);
	}
	catch(int er)
	{
		switch(er){
			case 0: std::cout << "Wrong format\n"; break;
			case 1: std::cout << "Zero division\n"; break;
			case 2: std::cout << "Not a number\n"; break;
			case 3: std::cout << "Unequal paranthesis\n"; break;
			case 4: std::cout << "Number is out of range\n"; break;
			case 5: std::cout << "Wrong parser format\n"; break;
		}
		return 1;
	}

	std::cout << res << std::endl;

	return 0;
}