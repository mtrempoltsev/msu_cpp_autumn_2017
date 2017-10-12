#include "RDParser.h"


// check binary operations
bool RDParser::_isbinop(const char & c){
	return (c=='+' || c=='*' || c=='/');
}


//  remove spaces
char * RDParser::_skipspace(char * str){
	char * r = str;
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
	return r;
}

// сheck matching brackets
void RDParser::_checkbrackets(const char *str){
	int open_cnt = 0, close_cnt = 0;
	for(;*str; str++){
		if (*str=='(') open_cnt++;
		if (*str==')') close_cnt++;
	}
	if (open_cnt != close_cnt) throw std::invalid_argument("Missing bracket.");
}

RDParser::RType RDParser::_prim(const char*& str){

	int sign = 1;
	if (*str == '-'){
		if (*(str+1) == '-'){
			throw std::invalid_argument("The allowed number of operators '-' is exceeded.");
		}
		sign = -1;
		str++;
	}


	std::string name = "";
	while (std::isalpha(*str)){
		name += std::tolower(*str++);
	}

	if (name!=""){
		if (NamedConstants.count(name)!=0){
			str--;
			return sign*NamedConstants[name];
		}
		else{
			throw std::invalid_argument("Undefined constant name.");
		}
	}


	if (*str == '('){
		return sign*_expr(++str);
	}

	if (!std::isalpha(*str) && !std::isdigit(*str)){
		throw std::invalid_argument("Unauthorized expression in parentheses");
	}

	RType result = *str - '0';
	while(*(str+1) != '\n' && std::isdigit(*(str+1))){
		result = result * 10 + (*++str - '0');
	}

	return sign * result;
}

// term value
RDParser::RType RDParser::_term(const char*& str){
	RType result = _prim(str);
	str++;
	while(*str != '\n'){
		char c = *str;
		if (c=='*' || c=='/'){
			str++;
			if (!_isbinop(*str)){
				if (c == '/') {
					RType value = _prim(str);
					if (value != 0){
						result /= value;
					}
					else{
						throw std::invalid_argument("Division by zero.");
					}
				}
				if (c == '*') result *= _prim(str);
				str++;
			}else{
				throw std::invalid_argument("Incorrect use of binary operators.");
			}
		}
		else {
			if (std::isalpha(c)) 	throw std::invalid_argument("Invalid argument.");
			if (c == '.') 			throw std::invalid_argument("Invalid argument. Expect int.");
			if (std::isdigit(c)) 	throw std::invalid_argument("Invalid argument.");
			break;
		}
	}
	if (*str!='\n')
		str--;


	return result;
}


RDParser::RType RDParser::_expr(const char*& str){
	RType result = _term(str);
	str++;
	while(*str!='\n' && *str!=')'){
		char c = *str;
		if (c=='+' || c=='-'){
			str++;
			if (! _isbinop(*str)){
				if (c == '+') result += _term(str);
				if (c == '-') result -= _term(str);
				str++;
			}else{
				throw std::invalid_argument("Incorrect use of binary operators.");
			}
		}
		else {
			if (std::isalpha(c)) 	throw std::invalid_argument("Invalid argument.");
			if (c == '.') 			throw std::invalid_argument("Invalid argument. Expect int.");
			if (std::isdigit(c)) 	throw std::invalid_argument("Invalid argument.");
			break;
		}
	}
	return result;
}

RDParser::RType RDParser::calculateExprFromStr(char * str){
	const char * cstr = _skipspace(str);
	_checkbrackets(str);
	return _expr(cstr); 
}

