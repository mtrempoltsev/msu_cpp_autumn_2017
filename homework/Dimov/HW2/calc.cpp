#include <iostream>

using namespace std;

void getlex(void);
int expr(void);
int add(void);
int mult(void);
void error(void);
int num(void);
int getint(void);
void skipspaces(void);
char *ptr;

void skipspaces(){
	while (*ptr==' ') ptr += 1;
}

void getlex(){ 
	ptr+=1;
  	skipspaces();
}

void error(){
	cout << "ERROR\n";
	throw "Error";
}

int expr(){
	int e=add();
  	while (*ptr=='+'||*ptr=='-'){
    	if (*ptr=='+'){
    		getlex();
    		e+=add();
    	}
    	else if (*ptr=='-'){
    		getlex();
    		e-=add();
    	}
    }
    skipspaces();
 	return e;
}

int add(void){
	int a=mult();
	while (*ptr =='*'||*ptr=='/'){
	    if (*ptr=='*'){
	    	getlex();
	    	a*=mult();
	    }
    	else if (*ptr=='/'){
    		getlex();
    		a=a/mult();
    	}
    }
    skipspaces();
    return a;
}

int mult(void){
	int m=num();
	skipspaces();
  	return m;
}

int num(void){
	int m;
	bool neg_flag = false;
	if (*ptr=='-'){
		ptr+=1;
		neg_flag = true;
	}
	switch(*ptr){
	   case ' ': skipspaces();
	   case '0':
	   case '1':
	   case '2': 
	   case '3': 
	   case '4':
	   case '5':	   
	   case '6': 
	   case '7': 
	   case '8':
	   case '9': m = getint(); break;
	   default : error(); break;
	}
	skipspaces();
	//getlex();
	if (neg_flag)
		return -1*m;
	else
		return m;
}

int getint(void){
	int r = 0;
	while ((*ptr <= '9') && (*ptr >= '0')){
		r = r*10+*ptr - '0';
		ptr += 1;
	}
	skipspaces();
	return r;
}



int main(int argc, char **argv){
	ptr = argv[1];
	if (argc < 2){
		cout << "Please, enter an expression to calculate" << endl;
		return 1;
	}
	int result;
	try{
		result = expr();
		cout << result << endl;
	}
	catch(...){
		return 1;
	}
	return 0;
}