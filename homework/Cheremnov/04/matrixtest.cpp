#include <iostream>
#include "matrix.h"
using namespace std;
enum { NUMBER_OF_FUNCTIONS = 6};
void check(bool value)
{
    if (!value)
        std::cout << "error" << std::endl;
}
//This test used for basic check of matrix operators
void checkGetSet(){
    Matrix m(2, 3);
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
    m.print_matrix();
    cout << "End of matrix" << endl;
}
//Function for checking the correct work of error, connected with wrong row index
void checkWrongRowIndex(){
	Matrix m(1, 2);
	m[4][0] = 0;
}
//Function for checking the correct work of error, connected with wrong column index
void checkWrongColumnIndex(){
	Matrix m(1, 2);
	m[0][7] = 0;
}
//Function for checking the correct work of error, connected with wrong multiplication on vector
void checkWrongVector(){
	Matrix m(3, 4);
	vector<double> v = { 1 };
	m *= v;
}
//Function for checking the correct work of multiplication
void MultiplicationCheck(){
	const unsigned rows = 5;
	const unsigned cols = 3;
	Matrix m(rows, cols);
	m[1][2] = 5;
	m[1][1] = 3;
	m[0][1] = 2;
	m.print_matrix();
	cout << "End of matrix" << endl;
	m *= 3; // multiplication on number
	//Check if multiplication on number is right
	check(m[1][2] == 15);
	check(m[1][1] == 9);
	check(m[0][1] == 6);
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 3; j++){
			if((i == 1 && j == 0) || (i == 0 && j != 1) || i > 1){
				check(m[i][j] == 0);
			}
		}
	}
	m.print_matrix();
	cout << "End of matrix" << endl;
	std::vector<double> v = { 1, 2, 3 }; 
	m *= v;
	//Check if multiplication on vector is right
	check(m[0][0] == 12);
	check(m[1][0] == 63);
	for(int i = 2; i < 5; i++){
		check(m[i][0] == 0);
	}
	m.print_matrix();
	cout << "End of matrix" << endl;
	Matrix m1(rows, cols);
	m1[1][2] = 5;
	m1[1][1] = 3;
	m1[0][1] = 2;
	m1.print_matrix();
	cout << "End of matrix" << endl;
	std::vector<double> v1 = { 1, 2, 3, 4, 5};
	m1 *= v1;
	//Check if multiplication on vector is right
	check(m1[0][0] == 0);
	check(m1[0][1] == 10);
	check(m1[0][2] == 15);
	m1.print_matrix();
	cout << "End of matrix" << endl;
}
//Function for printing Equal, if x is true, and Unequal in another case
void printequal(bool x){
	if(x){
		cout << "Equal" << endl;
	} else{
		cout << "Unequal" << endl;
	}
}
//Function for testing operators == and !=
void checkEquality(){
	Matrix m(1, 2), m1(2, 1);
	printequal(m == m1);
	Matrix m2(1, 2);
	m[0][1] = 1;
	m2[0][1] = 1;
	printequal(m == m2);
	m2[0][1] = 2;
	printequal(m == m2);
	m2[0][0] = 3;
	if(m != m2){
		cout << "Unequal";
	}
}
int main(){
	//Array of pointers of functions
	void (*functarr[NUMBER_OF_FUNCTIONS])() = { 
		checkGetSet, 
		checkWrongRowIndex, 
		checkWrongColumnIndex, 
		checkWrongVector,
		checkEquality,
		MultiplicationCheck
	};
	//Number of function, which we want to execute
	int num;
	cin >> num;
	//Check if the number is correct
	if(num < NUMBER_OF_FUNCTIONS && num >= 0){
		functarr[num]();
	}
	return 0;
}
