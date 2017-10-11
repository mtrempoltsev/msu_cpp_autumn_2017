#include <iostream>
#include <unordered_map>
using namespace std;

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
	left,
	right,
	wrong,
	end
};

class Calculator{
	public:
		Calculator(const char* text){
			input=text;
			curr=start;
			inverse=0;
			bracket_count=0;
		};
		int expr();
		bool check_brackets();
	private:
		int term(int inverse);
		int prim();
		int inverse;
		int bracket_count;
		const char* input;
		symbol next();
		symbol curr;
		symbol s;
		symbol s_prev;
 
};	
		
bool Calculator::check_brackets(){ //проверяем количество скобок
	if (bracket_count!=0)
		return 1;
	else
		return 0;
}

symbol Calculator::next(){  //смотрим какой объект сейчас считываем
	while (char curr=*input++){
		s_prev=s;
		switch (curr){
			case ' ': continue;
			case '(': return symbol::left;
			case ')': return symbol::right;
			case '+': {
					if (s_prev==symbol::left){
						cerr<<"Wrong input (+"<<endl;
						exit(5);
					}
					return symbol::plus;
			}
			case '-': return symbol::minus;
			case '*': {
					if (s_prev==symbol::left){
						cerr<<"Wrong input (*"<<endl;
						exit(5);
					}
					return symbol::multiply;
			}
			case '/': {
					if (s_prev==symbol::left){
						cerr<<"Wrong input (/"<<endl;
						exit(5);
					}
					return symbol::divide;
			}
			case 'e': return symbol::exp;
			case 'P': {
				curr=*input++;
				if (curr=='i')
					return symbol::Pi;
				else{
					cerr<<"Wrong input"<<endl;
					exit(3);
				}				 
			}
		}
		if ((curr>='0')&&(curr<='9'))
			return symbol::number;
		else{
			cerr<<"Wrong input"<<endl; //проверяем, что введены только цифры или +,-,*,/	
			exit(3);
		}
		}
	return symbol::end;
}

int Calculator::expr() //разбиваем на слагаемые
{
	int res=term(inverse=0);
	if (s==symbol::right){
		s_prev=symbol::right;
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

int Calculator::term(int inverse) //разбиваем на множители 
{
	int res=prim(); //  6/2*2 воспринимается, как 6/(2*2), значит если было деление, то следующую операцию необходимо инвертировать	
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
				cerr<<"Zero division error"<<endl;
			exit(1);
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
	if (s==symbol::right)
		return res;
	--input; //могли считать + или -, а не * или / => возвращаем в input
	return res;
	
}
int Calculator::prim() //считывание числа
{
	s=next();
	int res=0;
	if ((s_prev!=symbol::left)&&(s_prev!=symbol::right)){
		if ((s==symbol::plus)||(s==symbol::divide)||(s==symbol::multiply)){ 
			cerr<<"Two or more operations is a row"<<endl; //проверяем, что подряд не идут операции, или операция и )
			exit(3);
		}
		if (s==symbol::right){
			cerr<<"Operation and ) in a row"<<endl;
			exit(5);
		}
	}
		if (s==symbol::number) {
			input--;
			char currs=*input;
			while ((currs>='0')&&(currs<='9')){
				res = res * 10 + currs - '0'; //переводим из char в int
				currs=*++input;
			if (currs=='\0')
				s=symbol::end;
			}
			return res;
		}
		if (s==symbol::minus)  return -prim(); 
		if (s==symbol::exp)  return constants["exp"];
		if (s==symbol::Pi)  return constants["Pi"];
		if (s==symbol::left)  {bracket_count++;res=expr(); return res;}
		if (s==symbol::right) {bracket_count--;return res;}
	return res;
}


int main(int argc, const char* argv[])
{
	//проверяем, сколько ввели параметров в командной строке
	if (argc!=2){
		cout<<"Wrong number of arguments"<<endl;
		return 2;
	}
	int result=0;
	const char* input=argv[1];
	Calculator calc(input);
	result=calc.expr();
	if (calc.check_brackets()==1){
		cout<<"Wrong number of brackets"<<endl;
		return 4;
	}
	cout<<result<<endl;

return 0;
}


