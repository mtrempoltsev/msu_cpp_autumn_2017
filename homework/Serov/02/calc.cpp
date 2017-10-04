#include <iostream>

using namespace std;

int term(const char*& input, bool inverse=0);
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
		else{
			cerr<<"Wrong input"<<endl; //проверяем, что введены только цифры или +,-,*,/	
			exit(0);
		}
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

int term(const char*& input, bool inverse) //разбиваем на множители 
{
	int res=prim(input); //  6/2*2 воспринимается, как 6/(2*2), значит если было деление, то следующую операцию необходимо инвертировать
	symbol s=next(input);
	if ((s==symbol::multiply)||(s==symbol::divide)){
		if (s==symbol::divide){ //деление
		inverse++;
		int check=term(input,inverse);

		if (check==0)//проверка деления на ноль
		{
			cerr<<"Zero division error"<<endl;
			exit(0);
		}
		return (inverse & 1) ? res/check : res*check;
		}

		if (s==symbol::multiply){ //умножение
			return (inverse & 1) ? res/term(input,inverse) : res*term(input,inverse);}

	}
	--input; //могли считать + или -, а не * или / => возвращаем в input
	return res;
	
}

int prim(const char*& input) //считывание числа
{
	char s=next(input);
	int res=0;
	if ((s==symbol::plus)||(s==symbol::divide)||(s==symbol::multiply)){ //проверяем, что подряд не идут операции, напр */
		cerr<<"Two or more operations is a row"<<endl;
		exit(0);
	}
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
		cout<<"Wrong number of arguments"<<endl;
		return 0;
	}

	const char* input=argv[1];

	cout<<expr(input)<<endl;

return 1;
}


