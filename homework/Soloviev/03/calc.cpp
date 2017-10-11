#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unordered_map>

std::unordered_map<std::string, double> constants = 
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };

// exp_p_m -> exp_m_d{+ exp_m_d} | exp_m_d{- exp_m_d}
// exp_m_d -> exp_neg{* exp_neg} | exp_neg{/ exp_neg}
// exp_neg -> -exp_n | (exp_p_m) | exp_n
// exp_n-> [0-9]{[0-9]}

class Calculator{
public:
	int calculate(const char* str){
		counter = 0;
		expr = new char[strlen(str) + 1];
		int n = 0;
		int res;

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

	int start(){
		int res = exp_p_m();

		if(expr[counter] != '\0')
			throw 0;

		return res;
	}

	int exp_p_m(){

		int res = exp_m_d();

		while(expr[counter] == '+' || expr[counter] == '-'){

			counter++;
			
			if(expr[counter - 1] == '+')
				res += exp_m_d();
			else
				res -= exp_m_d();
		}

		return res;
	}

	int exp_m_d(){

		int res = exp_neg();

		while(expr[counter] == '*' || expr[counter] == '/'){

			counter++;
			
			if(expr[counter - 1] == '*')
				res *= exp_neg();
			else{
				int tmp = exp_neg();
				//Check for zero division
				if(tmp == 0)
					throw 1;
				res /= tmp;
			}
		}

		return res;
	}

	double exp_neg(){

		if(expr[counter] == '-')
		{
			counter++;
			return -exp_n();
		}else if(expr[counter] == '(')
		{
			counter++;
			int res = exp_p_m();
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

	double exp_n(){

		int res;

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
		if(expr[counter] < '0' || expr[counter] > '9')
			throw 2;

		//Reading a number from the string
		sscanf(expr + counter, "%d", &res);

		while(expr[counter] >= '0' && expr[counter] <= '9')
			counter++;

		return res;
	}
};

int main(int argc, char* argv[]){

	//Check if there is enough args
	if(argc != 2){
		std::cout << "Wrong number of arguments\n";
		return 1;
	}

	Calculator calc;
	int res;

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
		}
		return 1;
	}

	std::cout << res << std::endl;

	return 0;
}