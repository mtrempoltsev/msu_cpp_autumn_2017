#include "Matrix.hpp"
#include <iostream>

bool test_index()
{
	Matrix<int> m(2, 3);
	m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    if (m[0][0] == 1 && m[0][1] == 2 &&  m[0][2] == 3 && m[1][0] == 4 && m[1][1] == 5 && m[1][2] == 6)
    {
    	return true;
    }

    return false;
}


bool test_num_cols()
{
	Matrix<int> m(2, 3);
	m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    if (m.get_n_cols() == 3)
    {
    	return true;
    }

    return false;

}

bool test_num_rows()
{
	Matrix<int> m(2, 3);
	m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    if (m.get_n_rows() == 2)
    {
    	return true;
    }

    return false;

}

bool test_equal()
{
	Matrix<int> m(2, 3);
	m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    Matrix<int> k(2, 3);
	k[0][0] = 1;
    k[0][1] = 2;
    k[0][2] = 3;
    k[1][0] = 4;
    k[1][1] = 5;
    k[1][2] = 6;

    if ((k==m) == true)
    {
    	return true;
    }

    return false;
}

bool test_not_equal()
{
	Matrix<int> m(2, 3);
	m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    Matrix<int> k(2, 3);
	k[0][0] = 4;
    k[0][1] = 5;
    k[0][2] = 6;
    k[1][0] = 1;
    k[1][1] = 2;
    k[1][2] = 3;

    if ((k!=m) == true)
    {
    	return true;
    }

    return false;
}

bool test_mul_value()
{
	Matrix<int> m(2, 3);
	m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    int value = 2;

    Matrix<int> n = m*value;

    if (n[0][0] == 2 && n[0][1] == 4 &&  n[0][2] == 6 && n[1][0] == 8 && n[1][1] == 10 && n[1][2] == 12)
    {
    	return true;
    }

    return false;
}

bool test_mul_vector()
{
	Matrix<double> m(2, 3);
	m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    vector<double> v={1,2,3};

    vector<double> res = m*v;

    if (res[0] == 14 && res[1] == 32)
    {
    	return true;
    }

    return false;
}

bool test_copy()
{
    Matrix<double> m(1, 1);
    m[0][0] = 1;

    Matrix<double> n = m;
    Matrix<double> k(1,2);
    k = m;

    if (k[0][0] == 1 && m[0][0] == 1 && n[0][0] == 1)
    {
        return true;
    }

    return false;
}

bool test_move()
{

    Matrix<double> n = Matrix<double>(1,2);
    Matrix<double> k(1,1);
    k = Matrix<double>(1,2);

    if (k.get_n_rows() == 1 && k.get_n_cols() == 2 && n.get_n_rows() == 1 && n.get_n_cols() == 2)
    {
        return true;
    }

    return false;
}

void Test()
{	

	std::cout << "Index test: ";
	if (test_index()) 
	{
		std::cout << "pass" << endl;
	}
	else
	{
		std::cout << "not pass" << endl;
	}

	std::cout << "Columns test: ";
	if (test_num_cols()) 
	{
		std::cout << "pass" << endl;
	}
	else
	{
		std::cout << "not pass" << endl;
	}

	std::cout << "Rows test: ";
	if (test_num_rows()) 
	{
		std::cout << "pass" << endl;
	}
	else
	{
		std::cout << "not pass" << endl;
	}

	std::cout << "Equal test: ";
	if (test_equal()) 
	{
		std::cout << "pass" << endl;
	}
	else
	{
		std::cout << "not pass" << endl;
	}

	std::cout << "Not equal test: ";
	if (test_not_equal()) 
	{
		std::cout << "pass" << endl;
	}
	else
	{
		std::cout << "not pass" << endl;
	}

	std::cout << "Multiply double test: ";
	if (test_mul_value()) 
	{
		std::cout << "pass" << endl;
	}
	else
	{
		std::cout << "not pass" << endl;
	}

	std::cout << "Multiply vector test: ";
	if (test_mul_vector()) 
	{
		std::cout << "pass" << endl;
	}
	else
	{
		std::cout << "not pass" << endl;
	}

    std::cout << "Copy test: ";
    if (test_copy()) 
    {
        std::cout << "pass" << endl;
    }
    else
    {
        std::cout << "not pass" << endl;
    }

    std::cout << "Move test: ";
    if (test_copy()) 
    {
        std::cout << "pass" << endl;
    }
    else
    {
        std::cout << "not pass" << endl;
    }
}


int main(int argc, char** argv)
{	
	Test();
	return 0;
}