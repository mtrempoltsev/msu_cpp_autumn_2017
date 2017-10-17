#pragma once
#include <vector>
class Row
{
public:
	Row(std::size_t);
	double& operator[](std::size_t);
	const double& operator[](std::size_t) const;
	~Row();
private:
	std::vector<double> vector_;
	std::size_t size_;
};

