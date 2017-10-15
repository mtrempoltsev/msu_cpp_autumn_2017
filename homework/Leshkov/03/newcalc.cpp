#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
using namespace std;


/*
	New Grammar:
 S -> D{+D} | D{-D} | (P)
 D -> M{*M} | M{/M} |
 M -> T | (P)
 P -> S
 T -> -N | N | -(P)
 N -> [0-9] {[0-9]}
*/

void strperform(char* arg, char* str);

class Calc{
public:
	Calc(char* str){
		s=str;
		i=0;
	}
	~Calc(){
		free(s);
	}

	char* s;	//our string
	int i;		//string iterator

	int S();
	int M();
	int P();
	int D();
	double T();
	double N();
};

int main(int argc, char* argv[]){


	if (argc!=2){
		cout<<"Incorrect amount of args\n";
		return 1;
	}
	char* str=(char*)malloc(3*strlen(argv[1])+1);
	
	try{
		strperform(argv[1],str);
		//Проверяет корректность символов и баланс скобок
		Calc C(str);
		cout<<C.S()<<endl;
	}
	catch(char c){
		return 1;
	}

	return 0;
}















void strperform(char* arg, char* str){
	
	int parens=0;
	int j=0;
	for(int i=0;i<strlen(arg); i++){
		
		if (arg[i]=='e'){
			str[j++]='e';
		}
		else if ((arg[i]=='P')&&(arg[i+1]=='i')){
			
			str[j++]='P';
			str[j++]='i';
			i++;
		}
		else if (arg[i]==' ') continue;
		else if (
				((arg[i]>='0')&&(arg[i]<='9'))||
				(arg[i]=='+') || (arg[i]=='-')||
				(arg[i]=='*') || (arg[i]=='/')||
				(arg[i]=='(') || (arg[i]==')')){
			if (arg[i]=='(') parens++;
			if (arg[i]==')') parens--;
			str[j++]=arg[i];
		}
		else{
			cout<< "Check input line: symbol "<<arg[i]<<endl;
			throw arg[i];
		}
	}	

	str[j]='\0';
	if (parens!=0){
		cout<<"Check parens\n";
		throw '1';
	}
	return;
}


//*********************-------------------************************
//Далее реализация грамматики с соответствующими проверками на 
//допустимые цепочки грамматики и деление на 0


int Calc::P(){
	if (s[i]=='(')
		i++;

	int tmp=S();
	if (s[i]!=')'){
		cout<<"Check paren balnce\n";
		throw s[i];
	}
	i++;
	return tmp;
}

int Calc::M(){
	if (s[i]=='('){
		return P();
	}
	else{
		return T();
	}
}


double Calc::N(){
	double num=0;
	if (((s[i]<'0')||(s[i]>'9'))
		&&(s[i]!='P')&&(s[i]!='e')){
		
		cout<< "Invalid Syntax N: "<<s[i]<<endl;
		throw s[i];
		//Исключает тройные минусы
	}
	
	if ((s[i]=='P')&&(s[i+1]=='i')){
		i+=2;
		return 3.14;
	}
	else if (s[i]=='e'){
		i++;
		return 2.7;
	}
	else if (s[i]==')'){
		cout<<"check Paren Balance\n";
		throw s[i];
	}

	while((s[i]>='0')&&(s[i]<='9')){
		num=num*10+s[i]-'0';
		i++;
	}
	
	return num;
}

double Calc::T(){

	if ((s[i]=='-')&&(s[i+1]=='(')){
		i++;
		return -P();
	}
	if (s[i]=='-'){
		i++;
		return -N();
	}

	return N();
}

int Calc::D(){
	int tmp=M();
	int d;

	//Высчитываем * и /
	while((s[i]=='*')||(s[i]=='/')){

		if (s[i]=='/'){
			i++;
			d=M();
			if(d!=0)
				tmp/=d;
			else{
				cout<<"Error: zero division\n";
				throw '0';
				//Проверка деления на 0
			}
		}
		if (s[i]=='*'){
			i++;
			tmp*=M();
		}

	}
	return tmp;
}

int Calc::S(){
	int res=D();

	//Суммируем + и -
	while(s[i]!='\0'){
 
	
		if(s[i]=='+'){
			i++;
			res+=D();
		}
		else if(s[i]=='-'){
			i++;
			res-=D();
		}
		else if(s[i]==')')
			return res;
		else if((s[i]!='\0')&&(s[i]!='-')&&
			(s[i]!='+')){
			cout<<"S: unexpectible Lexem: "<<s[i]<<endl;
			throw s[i];
			//Проверка на символы, не являющиеся терминалными
		}

	}
	return res;
}

