#include <iostream>
#include <cctype>

#ifndef DEBUG
//#define DEBUG
#endif // DEBUG


#define exit_failure() 	std::cout << "INVALID" << std::endl; \
						exit(1);


// check binary operations
bool isbinop(const char & c){
	return (c=='+' || c=='*' || c=='/');
}

// check letters
void validate(const char* str){
	if (*(str+std::strlen(str)-1) == '-' || isbinop(*str+std::strlen(str)-1)){
		exit_failure();
	}
	while (*str){
		if (std::isalpha(*str)){
			exit_failure();
		}
		if (*str=='.'){
			exit_failure();
		}
		str++;
	}
}

void skip_space(char * str){
	while (*str != ' ' && *str != 0) {
		str++;
	}
	char* p = str;
	while (*str == ' ') {
		str++;
	}
	for(*p = *str; *str != 0;){
		if (*++str != ' ') *++p = *str;
	}
}

// number with sign
int prim(const char*& str){
	int sign = 1;
	if (*str == '-'){
		if (*(str+1) == '-'){
			exit_failure();
		}
		sign = -1;
		str++;
	}
	int result = *str - '0';
	while(*(str+1) != '\n' && std::isdigit(*(str+1))){
		result = result * 10 + (*++str - '0');
	}

#ifdef DEBUG
	std::cout << "Number values: " << sign * result << std::endl;
#endif 

	return sign * result;
}

// term value
int term(const char*& str){
	int result = prim(str);
	str++;
	while(*str != '\n'){
		char c = *str;
		if (c=='*' || c=='/'){
			str++;
			if (!isbinop(*str)){
				if (c == '/') result /= prim(str);
				if (c == '*') result *= prim(str);
				str++;
			}else{
				exit_failure();
			}
			// str++;
		}
		else break;
	}
	if (*str!='\n')
		str--;
	// str--;

#ifdef DEBUG
	std::cout << "Transitional term values: " << result << ",  " << std::endl;
#endif

	return result;
}

int _expr(const char*& str){
	int result = term(str);
	str++;
	while(*str!='\n'){
		char c = *str;
		if (c=='+' || c=='-'){
			str++;
			if (!isbinop(*str)){
				if (c == '+') result += term(str);
				if (c == '-') result -= term(str);
				str++;
			}else{
				exit_failure();
			}
			// str++;
		}
		else break;
	}
	return result;
}

int expr(char* str){
	skip_space(str);
	const char * cstr = str;
	validate(cstr);
	return _expr(cstr);
}


int main(int argc, char * argv[]){

	if (argc < 2){
		std::cout << "INPUT_FAILURE";
		return -1;
	}
	// char * str = argv[1];
	// skip_space(str);
	//std::cout << *str << std::endl;
	// const char * cstr = str;
	// validate(cstr);
	std::cout << expr(argv[1]) << std::endl;

	return 0;
}