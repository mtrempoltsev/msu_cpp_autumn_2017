#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
using namespace std;

template <class T>
class Vect{
public:

	~Vect(){
		free(v);
	}

	Vect(int s, T init=0){
		if (s<=0) throw 'V';
		v= (T*)malloc(sizeof(T)*s);
		size =s;
		for (int i=0; i<s; i++)
			v[i]=init;
	}

	Vect<T>(const Vect<T>& copy){
		size=copy.size;
		v=(T*)malloc(sizeof(T)*copy.size);
		for(int i=0; i<size; i++){
			v[i]=copy.v[i];
		}
	}


	double* v;
	int size;




	int get_Vsize();
	Vect<T>& operator*=(T x);
	T& operator[](int x);
	bool operator==(const Vect& x) const;
	bool operator!=(const Vect& x) const;
		
	friend ostream& operator<<(ostream& out, Vect<T>& vect){
	    	for (int i=0; i<vect.size; i++){
	    		out<<vect.v[i];
	    		out<<'	';
	    	}
	    	out<< endl;
	    	return out;
		}
};





template <class T>
class Matr{
public:
	
	Matr(int n, int m, T elems=0){ //N x M
		if((n<=0)||(m<=0)) throw 'M';

		matr= (Vect<T>*)malloc(sizeof(Vect<T>)*n);
		AmountOfVect=n;


		for (int i=0; i<n; i++){
			matr[i]=Vect<T>(m,elems);
		}
	}
	Matr(const Matr<T>& copy){
		AmountOfVect=copy.AmountOfVect;
		matr=(Vect<T>*)malloc(AmountOfVect*(sizeof(Vect<T>)));
		for(int i=0; i<AmountOfVect; i++){
			matr[i]=copy.matr[i];
		}
	}

	~Matr(){
		free(matr);
	}


	Vect<T>* matr;
	int AmountOfVect;



	Vect<T>& operator[](int x);
	int get_str_count();
	int get_column_count();
	Matr<T>& operator*=(T x);
	Matr<T>& operator*=( Vect<T>& x);
	bool operator==(const Matr<T>& x) const;
	bool operator!=(const Matr<T>& x) const;

	friend ostream& operator<<(ostream& out, Matr<T>& q){
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
void checkCopy();





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

		void checkCopy();//Проверка конструктора копирования
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

void checkCopy(){
	Matr<double> m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    Matr<double> m1(2,3);
    m1=m;
    check(m1==m);
}

void check(bool value)
{
    if (!value)
        std::cout << "error" << std::endl;
}

void checkGetSet(){

    Matr<double> m(2, 3);
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
	Matr <double> m(2,3);
	check(m.get_str_count()==2);
	check(m.get_column_count()==3);
}


void checkVectMul(){
	Matr<double> m(2,3);
	m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

//   M:	1 2 3
//		4 5 6
  

    Vect<double> v(2);
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
	Matr<double> m(2,3);
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
	Matr<double> m(2,3);
	m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    Matr<double> m2(2,3);
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
template <class T>
int Vect<T>::get_Vsize(){
	return size;
}

template <class T>
Vect<T>& Vect<T>::operator*=(T x){
	for (int i=0; i<this->size; i++){
		this->v[i]*=x;
	}
	return *this;
}

template <class T>
T& Vect<T>::operator[](int x){
		if ((x> this->size)||(x<0)){
			cout<<"index out of range\n";
			throw '1';
		}
		return this->v[x];
}

template <class T>
bool Vect<T>::operator==(const Vect<T>& x) const{
	if(x.size!=this->size){
		return false;
	}

	for (int i=0; i<size; i++){
		if (this->v[i]!= x.v[i])
			return false;
	}
	return true;
}

template <class T>
bool Vect<T>::operator!=(const Vect<T>& x) const{
	return !(x==*this);
}





//*************************************************
//Matr methods definitions:
//*************************************************

template <class T>
Vect<T>& Matr<T>::operator[](int x){
	if ((x> this->AmountOfVect)||(x<0)){
		cout<<"index out of range\n";
		throw '1';
	}
	return this->matr[x];

}

template <class T>
int Matr<T>::get_str_count(){
	return AmountOfVect;
}

template <class T>
int Matr<T>::get_column_count(){
	return this->matr[0].get_Vsize();
}

template <class T>
Matr<T>& Matr<T>::operator*=(T x){
	for (int i=0; i<this->AmountOfVect; i++)
		this->matr[i]*=x;
	return *this;
}

template <class T>
Matr<T>& Matr<T>::operator*=( Vect<T>& x){
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

	for (i=0; i<cols; i++){
		this->matr[0][i]=tmp[0][i];
	}	
	this->AmountOfVect=1;
	return *this;
}


template <class T>
bool Matr<T>::operator==(const Matr<T>& x) const{
	if (this->AmountOfVect!= x.AmountOfVect){
		return false;
	}

	for (int i=0; i<x.AmountOfVect; i++){
		if (this->matr[i]!= x.matr[i])
			return false;
	}
	return true;
}

template <class T>
bool Matr<T>::operator!=(const Matr<T>& x) const{
	return !(*this==x);
}

