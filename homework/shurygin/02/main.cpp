#include <iostream>
#include <string>

enum class Token
{
	Invalid, 
	Minus,
	Plus,
	Mul,
	Div,
	UnarMinus,
	Number,
	None
};

Token getToken(const std::string& s, int& value)
{
	value = -1;
	int i = 0;
	char c;
	c = s[i];
	switch(c)
	{
		case '-': return Token::Minus;
		case '+': return Token::Plus;
		case '*': return Token::Mul;
		case '/': return Token::Div;
	}
	if(c >= '0' && c <= '9')
	{
		value = (c - '0');
		for(int j = i+1; j < s.size(); ++j)
		{
			if(s[j] > '9' || s[j] < '0')
				return Token::Number;
			value *= 10;
			value += (s[j] - '0');
		}
		return Token::Number;
	}
	return Token::Invalid;
}



int calc(const std::string& s)
{
	Token last = Token::None; //for detect unar Minus
	Token min_priority = Token::None; //sorage the operatrion with minimum priority
	std::string str_for_min_priority[2]; //left and right part of experience relatively operation with minimum priority
	int val; //if we detect Token::Number, then value of this number will write in this variable
	for(size_t i = 0; i < s.size(); ++i)
	{
		Token cur = getToken(s.substr(i), val);
		if(cur == Token::Invalid) 
			throw 1;
		if(cur == Token::None)
			continue;
		if(cur == Token::Plus) 
			return calc(s.substr(0, i)) + calc(s.substr(i + 1));
		if(cur == Token::Minus)
			if(last == Token::Number)
				return calc(s.substr(0, i)) - calc(s.substr(i + 1));
			else
			{
				if(min_priority == Token::None || min_priority == Token::Number)
				{
					min_priority = Token::UnarMinus;
					str_for_min_priority[1] = s.substr(i + 1);
				}
			}
		else if(cur == Token::Mul || cur == Token::Div)
		{
			if(min_priority != Token::Mul && min_priority != Token::Div)
			{
				min_priority = cur ;
				str_for_min_priority[0] = s.substr(0, i);
				str_for_min_priority[1] = s.substr(i + 1);
			}
		}
		else if(cur == Token::Number)
			if(min_priority == Token::None)
			{
				min_priority = Token::Number;
				while((i + 1) < s.size() && s[i + 1] >= '0' && s[i + 1] <= '9')
					i++;
			}
		last = cur;
	}
	if(min_priority == Token::Mul)
		return calc(str_for_min_priority[0]) * calc(str_for_min_priority[1]);
	if(min_priority == Token::Div)
	{
		int denominator = calc(str_for_min_priority[1]);
		if(denominator == 0)
			throw 'a';
		return calc(str_for_min_priority[0]) / denominator;
	}
	if(min_priority == Token::UnarMinus)
		return -calc(str_for_min_priority[1]);
	if(min_priority == Token::Number)
		return val;
}

void delSpace(std::string& s)
{
	for(int i = 0; i < s.size(); ++i)
		if(s[i] == ' ')
			s = s.erase(i, 1);
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cout << "Error: a few arguments" << std::endl;
		return 1;
	}

	std::string expr = std::string(argv[1]);
	delSpace(expr);

	try
	{
		int res = calc(expr);
		std::cout << res << std::endl;
	}
	catch(int a)
	{
		std::cout << "Error: invalid experience" << std::endl;
		return 1;
	}
	catch(char a)
	{
		std::cout << "Error: devid by zero" << std::endl;
		return 1;
	}

	return 0;
}
