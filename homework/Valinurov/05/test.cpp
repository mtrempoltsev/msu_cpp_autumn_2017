#include "matrix.cpp"

template<class T>
class test
{
	void check(bool value)
	{
		if (!value)
		    std::cout << "error" << std::endl;
	}

	void checkGetSize()
	{
		Matrix<T> m(2, 3);
		m[0][0] = 1;
		m[0][1] = 1;
		check(m.get_ncol() == 3);
		check(m.get_nrow() == 2);
	}

	void checkVectorMul()
	{
		Matrix<T> m(2, 3);
		m[0][0] = 1;
		m[0][1] = 2;
		m[0][2] = 3;
		m[1][0] = 4;
		m[1][1] = 5;
		m[1][2] = 6;
		std::vector<T> v = {1, 2, 3};
		std::vector<T> res = m * v;
		check(res[0] == 14);
		check(res[1] == 32);
	}

	void checkNumMul()
	{
		Matrix<T> m1(2, 3);
		m1[0][0] = 1;
		m1[0][1] = 2;
		m1[0][2] = 3;
		m1[1][0] = 4;
		m1[1][1] = 5;
		m1[1][2] = 6;
		Matrix<T> m2 = m1 * 3;

		for (size_t i = 0; i < 2; i++)
		    for (size_t j = 0; j < 3; j++)
		        check(m1[i][j] * 3 == m2[i][j]);
	}

	void checkGetSet()
	{
		Matrix<T> m(2, 3);
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

	void checkMovesCopies()
	{
		Matrix<T> m(2, 3);
		m[0][0] = 1;
		m[0][1] = 2;
		m[0][2] = 3;
		m[1][0] = 4;
		m[1][1] = 5;
		m[1][2] = 6;

		Matrix<T> m1(m);
		check(m == m1);
		m1 = m;
		check(m == m1);
		Matrix<T> m2(std::move(m));
		check(m1 == m2);
		m = m1;
		m2 = std::move(m);
		check(m1 == m2);
	}
public:
	void do_test()
	{
		checkGetSize();
		checkVectorMul();
		checkNumMul();
		checkGetSet();
		checkMovesCopies();
	}
};


int main(){
    test<double> t1;
    try
    {
        t1.do_test();
    }
    catch (const char* ms){
        std::cout << ms << std::endl;
    }

    test<int> t2;
    try
    {
        t2.do_test();
    }
    catch (const char* ms){
        std::cout << ms << std::endl;
    }
    return 0;
}
