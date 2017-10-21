#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;



class Calculator{
public:
        Calculator(const char* t){  // Конструкор
		text = t;
	}

        ~Calculator(){}             // Деструкор
	
	double calculate(){
		return calc(1);
	}
private:
        unordered_map<string, double> constants =  // Константы
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };
	const char* text;
        int nolb = 0; // Количество открывающихся скобок
        int norb = 0; // Количество закрывающихся скобок
        enum class Token{   // Список токенов
		Invalid,
		Minus,
		Plus,
		Mul,
		Div,
		Number,
		RightBrace,
		LeftBrace,
		End
	};

	Token getToken(double &s){
		string st;
		while(const char c = *text){
			switch(c){
				case ' ': 
					++text;
					continue;
				case '-':
					++text;
					return Token::Minus;
				case '(':
					++text;
					return Token::LeftBrace;
				case ')':
					++text;
					return Token::RightBrace;
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
				st.clear();
				for(auto ch = *text;ch >= '0' && ch <= '9';){
					st.push_back(ch);
					++text;
					ch = *text;
				}
				s = (double) stoi(st);
				return Token::Number;
			}
                        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
				st.clear();
				for(auto ch = *text;(ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');){
					st.push_back(ch);
					++text;
					ch = *text;
				}
				if (constants.find(st) != constants.end()){
					s = constants[st];
					return Token::Number;
				} else{
					return Token::Invalid;
				}
				
			}
			return Token::Invalid;
		}
		return Token::End;
	}

	double calc(int um){
		string st = "unary minus";
		double s;
		auto token = getToken(s);
		while (true){
			if (token == Token::Invalid){

                                exit(1);
			}
			else if (token == Token::LeftBrace){
                                ++nolb;
				s = um*calc(1);
				st = "number";
				token = getToken(s);
				if (token == Token::Number || token == Token::Invalid){
                                        exit(1);
				}
				continue;
			}
			else if (token == Token::RightBrace){
				if (st == "unary minus"){
                                        exit(1);
				}
                                ++norb;
                                if (norb > nolb){
                                        exit(1);
				}
				return s;
			}
			else if (token == Token::Plus){
				double r = calc(1);
                                if (st == "unary minus"){
                                        exit(1);
				}
				return um*s + r;
			}
			else if (token == Token::Minus){
				if (st == "unary minus"){
					return calc((-1)*um);
				}
				return um*s + calc(-1);
			}
			else if (token == Token::End){
                                if (norb != nolb){
                                        exit(1);
				}
				return s;
			}
			else if (token == Token::Mul){
				double l;
				int um2 = 1;
				auto t = getToken(l);
				while (t != Token::Number && t != Token::LeftBrace){
                                        if (t == Token::Minus){
						t = getToken(l);
						um2 *= -1;
                                        } else {
                                            exit(1);
					}
				}
				if (t == Token::LeftBrace){
					++nolb;
					l = um2*calc(1);
				} else {
					l *= um2;
				}
				s = um*s * l;
				st = "number";
				token = getToken(s);
				um = 1;
				if (token == Token::End)
					return s;
			}
			else if (token == Token::Div){
				double l;
				int um2 = 1;
				auto t = getToken(l);
				while (t != Token::Number && t != Token::LeftBrace){
                                        if (t == Token::Minus){  // унарный минус
						t = getToken(l);
						um2 *= -1;
                                        } else {
                                            exit(1);
					}
				}
				if (t == Token::LeftBrace){
					++nolb;
					l = um2*calc(1);
				} else {
					l *= um2;
				}
                                if (l == 0){
                                    exit(1);
				}
				s = um*s / l;
				token = getToken(s);
				um = 1;
				if (token == Token::End)
					return s;
			}
			else {
				st = "number";
				token = getToken(s);
				s *= um;
				um = 1;
			}
		}
	}
};


int main(int argc, char** argv){
        if (argc != 2){

                return 1;
	}
	Calculator c(argv[1]);
        cout << c.calculate() << endl;
	return 0;
}

