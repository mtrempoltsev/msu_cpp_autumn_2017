#include <iostream>
#include <cstring>
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
    Matrix <double> m(2, 3);
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
	Matrix <double> m(1, 2);
	m[4][0] = 0;
}
//Function for checking the correct work of error, connected with wrong column index
void checkWrongColumnIndex(){
	Matrix <double> m(1, 2);
	m[0][7] = 0;
}
//Function for checking the correct work of error, connected with wrong multiplication on vector
void checkWrongVector(){
	Matrix<double> m (3, 4);
	vector <double> v = { 1 };
	m *= v;
}
//Function for checking the correct work of multiplication
void MultiplicationCheck(){
	const unsigned rows = 5;
	const unsigned cols = 3;
	Matrix <double> m(rows, cols);
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
	Matrix<double> m1(rows, cols);
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
	Matrix<double> m(1, 2), m1(2, 1);
	printequal(m == m1);
	Matrix<double> m2(1, 2);
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
//Function for checking the correct work of copy
void checkCopy(){
	Matrix<int> m1(1, 2);
	Matrix<int> m2(3, 5);
	m2 = m1;
	m2.print_matrix();
	check(m1 == m2);
	cout << "End of matrix" << endl;
	Matrix<int> m3 = m2;
	m3.print_matrix();
	check(m3 == m2);
	cout << "End of matrix" << endl;
}
//Function for checking the correct work of moving
void checkMove(){
	Matrix<int> m1(2, 2);
	m1[0][0] = 3;
	Matrix<int> m2 = move(m1);
	check(m1.checkzero());
	m2.print_matrix();
	check(m2[0][0] == 3);
	Matrix<int> m3(1, 1);
	m3 = move(m2);
	check(m2.checkzero());
	m3.print_matrix();
	check(m3[0][0] == 3);
}
int main(int argc, char **argv){
	//Processing the arguments of the command string
	if(argc >= 2){
		if(!strcmp(argv[1], "-errorrow")){
			checkWrongRowIndex();
		} else if(!strcmp(argv[1], "-errorcolumn")){
			checkWrongColumnIndex();
		} else if(!strcmp(argv[1], "-errorvector")){
			checkWrongVector();
		}
	}
	//Executing the tests
	checkGetSet();
	MultiplicationCheck();
	checkEquality();
	checkCopy();
	checkMove();
	return 0;
}
