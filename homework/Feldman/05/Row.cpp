#include <vector>
#pragma once
template <class T>
class Row {
public:
	std::vector<T> row;
	unsigned int cols;
	Row(int cols_, T val) :cols(cols_){
		for (size_t i = 0; i < cols; ++i)
			row.push_back(val);
	}
	T& operator [] (size_t col) {
		if (col >= cols) {
			std::cout << "OUT OF RANGE!" << std::endl;
			exit(1);
		}
		return row[col];
	}
};
