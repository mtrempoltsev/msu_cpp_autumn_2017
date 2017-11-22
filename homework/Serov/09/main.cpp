#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <map>
#include <vector>

class Error
{
public:
	int value_;
	std::string message_;

	Error(int value, std::string message): value_(value), message_(message) {}
	
	void print_message() const
	{
		printf("Exit code: %d, Error message: %s\n", this->value_, this->message_.c_str());
	}
};

void make_count_dict(std::string input, std::string output)
{
	std::string s;
	std::ifstream input_file(input);
	std::ofstream output_file(output);

	if (!input_file)
	{
    		throw Error(2, "Can't open input file");
	}

	std::map<std::string, int> dict;

	while (!input_file.eof())
	{
		if (!input_file.good())
			throw Error(4, "Error while reading input file");
		input_file >> s;
                auto iter = dict.find(s);
                if (iter == dict.end()) 
			dict[s] = 1;
		else 
                iter->second++;
	}

	std::vector<std::pair<std::string, int> > vec(dict.begin(), dict.end());

	std::sort(vec.begin(), vec.end(), [](const std::pair<std::string, int> x, const std::pair<std::string, int> y) { return x.second > 																y.second; });

	if (!output_file)
	{
    		throw Error(3, "Can't open output file");
	}

	for (size_t i = 0; i < vec.size(); i++)
		output_file << vec[i].second << " " << vec[i].first << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc!=3)
	{
		std::cout << "Wrong number of arguments" << std::endl;
		return 1;
	}

	std::string input = argv[1];
	std::string output = argv[2];

	try
	{	
		make_count_dict(input, output);
	}
	
	catch(const Error& error)
	{
		error.print_message();
		return error.value_;
	}
	catch(...)
	{
		std::cout << "Some error" << std::endl;
		return 5;
	}
	
	return 0;
}
