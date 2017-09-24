#include <cstdint>
#include <cstdlib>

class Matrix
{
public:
	int32_t** mas;

	Matrix(int32_t a)
		: Size(a)
	{
		mas = new int32_t* [Size];
		for (int32_t i = 0; i < Size; i++)
			mas[i] = new int32_t [Size];
	}

	~Matrix()
	{
		for (int32_t i = 0; i < Size; i++)
			delete [] mas[i];
		delete [] mas;
	}

	void Randomize()
	{
		for (int32_t i = 0; i < Size; i++)
				for (int32_t j = 0; j < Size; j++)
					mas[i][j] = rand() % 100;
	}

private:
	int32_t Size = 10000;
};
