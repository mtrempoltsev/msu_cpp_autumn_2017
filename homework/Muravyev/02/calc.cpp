#include <iostream>
#include <string>

using namespace std;

void help(){  // Just a small help for users
	cout << endl << "Help" << endl
	<< "Enter ./name_of_prog expression" << endl;
}

enum class Token{
	Invalid,
	Minus,
	Plus,
	Mul,
	Div,
	Number,
	End
};

Token getToken(const char*& text, string& s){
	while(const char c = *text){
		switch(c){
			case '"':
				++text;
				continue;
			case ' ': 
				++text;
				continue;
			case '-':
				++text;
				return Token::Minus;
			case '*': 
				++text;
				return Token::Mul;
			case '/': 
				++text;
				return Token::Div;
			case '+': 
				++text;
				return Token::Plus;
		}
		if (c >= '0' && c <= '9'){
			s.clear();
			for(auto ch = *text;ch >= '0' && ch <= '9';){
				s.push_back(ch);
				++text;
				ch = *text;
			}
			return Token::Number;
		}
		return Token::Invalid;
	}
	return Token::End;
}

int calc(const char* text, int um){
	string s = "unary minus";
	auto token = getToken(text, s);
	while (true){
		if (token == Token::Invalid){
			cout << "Incorrect input data" << endl;
			help();
			exit(-1);
		}
		else if (token == Token::Plus){
			int r = calc(text,1);
			if (s == "unary minus"){
				cout << "Incorrect input data" << endl;
				help();
				exit(-1);
			}
			return um*stoi(s) + r;
		}
		else if (token == Token::Minus){
			if (s == "unary minus")
				return calc(text, -1*um);
			return um*stoi(s) + calc(text, -1);
		}
		else if (token == Token::End){
			return um*stoi(s);
		}
		else if (token == Token::Mul){
			string l;
			int um2 = 1;
			auto t = getToken(text, l);
			while (t != Token::Number){
				if (t == Token::Minus){  // Work with unary minuses
					t = getToken(text, l);
					um2 *= -1;
				} else {
					cout << "Incorrect input data" << endl;
					help();
					exit(-1);
				}
			}
			s = to_string(um*stoi(s) * um2*stoi(l));
			token = getToken(text, s);
			um = 1;
			if (token == Token::End)
				return stoi(s);
		}
		else if (token == Token::Div){
			string l;
			int um2 = 1;
			auto t = getToken(text, l);
			while (t != Token::Number){
				if (t == Token::Minus){  // Work with unary minuses
					t = getToken(text, l);
					um2 *= -1;
				} else {
					cout << "Incorrect input data" << endl;
					help();
					exit(-1);
				}
			}
			if (stoi(l) == 0){
				cout << "Expressions like n/0 are not available" << endl;
				exit(-1);
			}
			s = to_string(um*stoi(s) / (um2*stoi(l)));
			token = getToken(text, s);
			um = 1;
			if (token == Token::End)
				return stoi(s);
		}
		else {
			token = getToken(text, s);
		}
	}
}

int main(int argc, char** argv){
	if (argc != 2){
		help();
		return -1;
	}
	const char* text = argv[1];
	cout << calc(text, 1) << endl; //  Start calculating
	return 0;
}