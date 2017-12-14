#include "ping_pong.h"


int main(int argc, char const *argv[])
{
	unsigned int max_cores = std::thread::hardware_concurrency();
	std::vector<std::string> v;
	int iter = 0;
	
	if (argc > 1)
	{
		for (int arg = 1; arg < argc; arg++){
			if (std::string(argv[arg]) == "-n"){
				if (arg + 1 < argc){
					iter = std::stoi(std::string(argv[++arg]));
					break;
				} else {
					std::cout << "Invalid argument";
					return 1;
				}
			}
			v.push_back(std::string(argv[arg]) + ' ');
			
			if (v.size() > max_cores)
			{
				std::cout << "Too many threads";
				return 1;
			}
		}
	}

	if (v.size() == 0)
	{
		v.push_back("ping ");
		v.push_back("pong ");
	}
	
	ConcurentSuccessiveMessages Messages(v, iter);

	return 0;
}