#include <iostream>

#ifndef DEBUG
//#define DEBUG
#endif // DEBUG


#define next(x) if(*(x+1) != '\n') x+=2; \
				else x++;

// number with sign
double prim(const char*& str){

	int sign = 1;
	if (*str == '-'){
		sign = -1;
		str++;
	}
	double result = (*str - '0');
	while(*(str+1) != '\n' && std::isdigit(*(str+1)))
		result = result * 10 + (*++str - '0');

#ifdef DEBUG
	std::cout << "Number values: " << sign * result << std::endl;
#endif 

	return sign * result;
}

// term value
double term(const char*& str){
	double result = prim(str);
	next(str);
	while(*str != '\n'){
		char c = *str;
		if (c=='*' || c=='/'){
			next(str);
			if (c == '/') result /= prim(str);
			if (c == '*') result *= prim(str);
			next(str);
		}
		else break;
	}
	if (*str!='\n')
		str-=2;

#ifdef DEBUG
	std::cout << "Transitional term values: " << result << ",  " << std::endl;
#endif

	return result;
}

double expr(const char*& str){
	double result = term(str);
	next(str);
	while(*str!='\n'){
		char c = *str;
		if (c=='+' || c=='-'){
			next(str);
			if (c == '+') result += term(str);
			if (c == '-') result -= term(str);
			next(str);
		}
		else break;
	}
	return result;
}

int main(int argc, char * argv[]){

	if (argc < 2){
		std::cout << "INPUT_FAILURE";
		return -1;
	}
	const char * str = argv[1];
	std::cout << expr(str) << std::endl;
	return 0;
}