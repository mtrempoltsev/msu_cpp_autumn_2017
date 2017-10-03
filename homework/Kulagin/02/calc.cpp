#include <iostream>

using namespace std;

void skip_spaces(char*& expr) {
	while(*expr == ' ') {
		expr++;
	}
}

// [GET_PRIM]: parsing '[0-9]+ | -[0-9]+'
int get_prim(char*& expr) {
	skip_spaces(expr);
	
	bool is_negative = false;
	
	switch(*expr) {
	case '+': {
		expr++;
		
		break;
	}
	case '-': {
		is_negative = true;
		
		expr++;
		
		break;
	}
	default:
		break;
	}
	
	int prim = 0;
	
	if(*expr >= '0' && *expr <= '9') {
		do {
			prim = 10 * prim + (*expr - '0');
			
			expr++;
		} while(*expr >= '0' && *expr <= '9');
	} else {
		throw "Error: invalid charater";
	}
	
	return is_negative ? (-prim) : (prim);
}

// [GET_TERM]: parsing 'prim | term * prim | term / prim'
int get_term(char*& expr) {
	int term_1 = get_prim(expr);
	
	while(1) {
		skip_spaces(expr);
		
		char op = *expr;
		
		switch(op) {
		case '*': {
			expr++;
			
			term_1 *= get_prim(expr);
			
			break;
		}
		case '/': {
			expr++;
			
			int term_2 = get_prim(expr);
			
			if(term_2 == 0) {
				throw "Error: division by zero";
			}
			
			term_1 /= term_2;
			
			break;
		}
		default:
			return term_1;
		}
	}
}

// [GET_EXPR]: parsing 'expr = term | expr + term | expr - term'
int get_expr(char*& expr) {
	int term_1 = get_term(expr);
	
	while(1) {
		skip_spaces(expr);
		
		char op = *expr;
		
		switch(op) {
		case '+': {
			expr++;
			
			term_1 += get_term(expr);
			
			break;
		}
		case '-': {
			expr++;
			
			term_1 -= get_term(expr);
			
			break;
		}
		default:
			return term_1;
		}
	}
}

int calc(char* expr) {
	int result = get_expr(expr);
	
	if(*expr != '\0') {
		throw "Error: invalid character";
	}
	
	return result;
};



int main(int argc, char** argv) {
	if(argc < 2) {
		cout << "Usage: ./a.out <expression>" << endl;
		
		exit(1);
	}
	
	char* expr = argv[1];
	
	if(*expr == '\0') {
		cout << "Error: input expression is empty" << endl;
		
		exit(1);
	}
	
	try {
		cout << calc(expr) << endl;
	} catch(const char* e) {
		cout << e << endl;
		
		exit(1);
	}
	
	return 0;
}
