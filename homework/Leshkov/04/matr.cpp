#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
using namespace std;


class Vect{
public:
	Vect(int s, double init=0){
		if (s<=0) throw 'V';
		v= (double*)malloc(sizeof(double)*s);
		size =s;
		for (int i=0; i<s; i++)
			v[i]=init;
	}

	double* v;
	int size;


	int get_Vsize();
	Vect& operator*=(double x);
	double& operator[](int x);
	bool operator==(const Vect& x) const;
	bool operator!=(const Vect& x) const;
		
	friend ostream& operator<<(ostream& out, Vect& vect){
	    	for (int i=0; i<vect.size; i++){
	    		out<<vect.v[i];
	    		out<<'	';
	    	}
	    	out<< endl;
	    	return out;
		}
};






class Matr{
public:
	
	Matr(int n, int m, double elems=0){ //N x M
		if((n<=0)||(m<=0)) throw 'M';

		matr= (Vect*)malloc(sizeof(Vect)*n);
		AmountOfVect=n;


		for (int i=0; i<n; i++){
			matr[i]=Vect(m,elems);
			//cout<<matr[j];
		}
	}

	~Matr(){
		free(matr);
	}


	Vect* matr;
	int AmountOfVect;



	Vect& operator[](int x);
	int get_str_count();
	int get_column_count();
	Matr& operator*=(double x);
	Matr& operator*=( Vect& x);
	bool operator==(const Matr& x) const;
	bool operator!=(const Matr& x) const;

	friend ostream& operator<<(ostream& out, Matr& q){
		for (int i=0; i<q.AmountOfVect; i++){
			out<<q[i];
			out<<endl;
		}
	return out;
	}


};



void check(bool value);
void checkGetSet();
void checkGetMethods();
void checkVectMul();
void checkMul();
void checkEqNeq();





/*******************************************************
		$$___$$__$$$$___$$$$$$__$$__$$
		$$$_$$$_$$__$$____$$____$$$_$$
		$$_$_$$_$$$$$$____$$____$$_$$$
		$$___$$_$$__$$____$$____$$__$$
		$$___$$_$$__$$__$$$$$$__$$__$$
*******************************************************/

int main(){

	//Matr(int n, int m, double defvalue)
	try{
		checkGetSet();//Проверка работы конструктора и оператора[][]
		checkGetMethods();//Проверка Get-методов
		checkVectMul();//Проверка умножения на вектор
		checkMul();//Проверка умножения на число
		checkEqNeq();//Проверка работы == и != для матриц
	}
	catch(char c){
		cout<<"Exit char is "<<c<<endl;
		return 1;
	}

	return 0;
}

//*************************************************
//Check functions
//*************************************************


void check(bool value)
{
    if (!value)
        std::cout << "error" << std::endl;
}

void checkGetSet(){

    Matr m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    
    check(m[0][0] == 1);
    check(m[0][1] == 2);
    check(m[0][2] == 3);
    check(m[1][0] == 4);
    check(m[1][1] == 5);
    check(m[1][2] == 6);
    
    m[1][2] = 100;
    check(m[1][2] == 100);
}


void checkGetMethods(){
	Matr m(2,3);
	check(m.get_str_count()==2);
	check(m.get_column_count()==3);
}


void checkVectMul(){
	Matr m(2,3);
	m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

//   M:	1 2 3
//		4 5 6
  

    Vect v(2);
    v[0]=11;
    v[1]=21;
    //V: 11   21

    m*=v;
    //V*M= 95  127  159
	
	check(m[0][0] == 95);
    check(m[0][1] == 127);
    check(m[0][2] == 159);
}

void checkMul(){
	Matr m(2,3);
	m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

//   M:	1 2 3
//		4 5 6
  

	double d=3;
    m*=d;
    //V*M= 95  127  159
	
	check(m[0][0] == 3);
    check(m[0][1] == 6);
    check(m[0][2] == 9);
    check(m[1][0] == 12);
    check(m[1][1] == 15);
    check(m[1][2] == 18);
}


void checkEqNeq(){
	Matr m(2,3);
	m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    Matr m2(2,3);
	m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 300000;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    check(m!=m2);
    check(m==m);
}







//*************************************************
//Vect methods definition
//*************************************************

int Vect::get_Vsize(){
	return size;
}

Vect& Vect::operator*=(double x){
	for (int i=0; i<this->size; i++){
		this->v[i]*=x;
	}
	return *this;
}

double& Vect::operator[](int x){
		if ((x> this->size)||(x<0)){
			cout<<"index out of range\n";
			throw '1';
		}
		return this->v[x];
}

bool Vect::operator==(const Vect& x) const{
	if(x.size!=this->size){
		return false;
	}

	for (int i=0; i<size; i++){
		if (this->v[i]!= x.v[i])
			return false;
	}
	return true;
}

bool Vect::operator!=(const Vect& x) const{
	return !(x==*this);
}





//*************************************************
//Matr methods definitions:
//*************************************************


Vect& Matr::operator[](int x){
	if ((x> this->AmountOfVect)||(x<0)){
		cout<<"index out of range\n";
		throw '1';
	}
	return this->matr[x];

}

int Matr::get_str_count(){
	return AmountOfVect;
}

int Matr::get_column_count(){
	return this->matr[0].get_Vsize();
}

Matr& Matr::operator*=(double x){
	for (int i=0; i<this->AmountOfVect; i++)
		this->matr[i]*=x;
	return *this;
}

Matr& Matr::operator*=( Vect& x){
	//1x5 ** 5x10= 1x10
	if(x.size!=this->AmountOfVect){
		cout<<"check sizes\n";
		throw '*';
	}

	int cols=this->get_column_count();
	Matr tmp(1,cols,0);
	int i,j;

	for (i=0; i<cols; i++){
		for(j=0; j<x.size; j++)
			tmp[0][i]=tmp[0][i]+x[j]*(this->matr[j][i]);
	}
	/*
	for (i=1; i<this->AmountOfVect; i++){
		free((void*)matr[i].v);
	}
	*/
	for (i=0; i<cols; i++){
		this->matr[0][i]=tmp[0][i];
	}	
	this->AmountOfVect=1;

	return *this;
}


bool Matr::operator==(const Matr& x) const{
	if (this->AmountOfVect!= x.AmountOfVect){
		return false;
	}

	for (int i=0; i<x.AmountOfVect; i++){
		if (this->matr[i]!= x.matr[i])
			return false;
	}
	return true;
}

bool Matr::operator!=(const Matr& x) const{
	return !(*this==x);
}

