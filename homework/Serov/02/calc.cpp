#include <iostream>

using namespace std;

int term(const char*& input);
int prim(const char*& input);

enum symbol{
	plus,
	minus,
	multiply,
	divide,
	number,
	wrong,
	end
};

symbol next(const char*& input){
	while (char curr=*input++){
		switch (curr){
			case ' ': continue;
			case '+': return symbol::plus; 
			case '-': return symbol::minus;
			case '*': return symbol::multiply;
			case '/': return symbol::divide;
		}
		if ((curr>='0')&&(curr<='9'))
			return symbol::number;
		else
			return symbol::wrong;
		}
	return symbol::end;
}

int expr(const char*& input) //разбиваем на слагаемые
{
	int res=term(input);
	symbol s=next(input);
	if (s!=symbol::end)
		return s==symbol::plus ? res+expr(input) : res-expr(input);
	else
		return res;
}

int term(const char*& input) //разбиваем на множители
{
	int res=prim(input);
	symbol s=next(input);
	if ((s==symbol::multiply)||(s==symbol::divide))
		return s==symbol::multiply ? res*term(input) : res/term(input);
	else{
		--input; //могли считать + или -, а не * или / => возвращаем в input
		return res;
	}
}

int prim(const char*& input) //считывание числа
{
	char s=next(input);
	int res=0;
	if (s==symbol::number){
		input--;
		char s=*input;
		while ((s>='0')&&(s<='9')){
			res = res * 10 + s - '0'; //переводим из char в int
			s=*++input;
		}
		return res;
	}
	else
		return -prim(input); 
}


int main(int argc, const char* argv[])
{
	//проверяем, сколько ввели параметров в командной строке
	if (argc!=2){
		cout<<"Wrong input"<<endl;
		return 0;
	}
const char* input=argv[1];
	cout<<expr(input)<<endl;

return 1;
}


