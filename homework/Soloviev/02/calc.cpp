#include <iostream>
#include <string.h>
#include <stdio.h>

// S -> D{+ D} | D{- D}
// D -> T{* T} | T{/ T}
// T -> -N | N
// N -> [0-9]{[0-9]}

//n - iterator of the expression

int S(char* str, int n);
int D(char* str, int& n);
int T(char* str, int& n);
int N(char* str, int& n);

int S(char* str, int n){

	int res = D(str, n);

	while(str[n] == '+' || str[n] == '-'){

		n++;
		
		if(str[n - 1] == '+')
			res += D(str, n);
		else
			res -= D(str, n);
	}

	return res;
}

int D(char* str, int& n){

	int res = T(str, n);

	while(str[n] == '*' || str[n] == '/'){

		n++;
		
		if(str[n - 1] == '*')
			res *= T(str, n);
		else{
			int tmp = T(str, n);
			//Check for zero division
			if(tmp == 0)
				throw 1;
			res /= tmp;
		}
	}

	return res;
}

int T(char* str, int& n){

	if(str[n] == '-'){
		n++;
		return -N(str, n);
	}else
		return N(str, n);

}

int N(char* str, int& n){

	int res;

	//Check if a number
	if(str[n] < '0' || str[n] > '9')
		throw 0;

	//Reading a number from the string
	sscanf(str + n, "%d", &res);

	while(str[n] >= '0' && str[n] <= '9')
		n++;

	return res;
}

int main(int argc, char* argv[]){

	//Check if there is enough args
	if(argc != 2){
		std::cout << "Wrong number of arguments\n";
		return 1;
	}

	char* str = new char[strlen(argv[1]) + 1]; //Expression without spaces
	int counter = 0;                           //Iterator
	int result = 0;                            //Result of the expression
	char c = 0;                                //Additional var

	//Deleting spaces and checking for wrong symbols
	for(uint i = 0; i < strlen(argv[1]); i++){
		//Skip spaces
		if(argv[1][i] != ' ')
			c = argv[1][i];
		else
			continue;

		//Check for wrong symbols
		if((c >= '0' && c <= '9') ||
		   c == '+' || c == '-' ||
		   c == '*' || c == '/')
			str[counter++] = c;
		else
		{
			std::cout << "Wrong symbols\n";
			delete [] str;
			return 1;
		}
	}

	//Adding null terminator
	str[counter] = '\0';

	//Computing the expression
	//Catching wrong format and zero division
	try
	{
		result = S(str, 0);
	}
	catch(int er_code)
	{	
		if(er_code == 0)
			std::cout << "Wrong format\n";
		else
			std::cout << "Zero division\n";
		delete [] str;
		return 1;
	}

	std::cout << result << std::endl;

	//Freeing up memory
	delete [] str;

	return 0;
}