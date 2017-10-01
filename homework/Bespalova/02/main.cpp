#include <iostream>
#include <string>

using namespace std;
string str;
int counter = 0;

int get_number_without_sign()
{
    int res = 0;
    while (counter < str.length() && str[counter] <= '9' && str[counter] >= '0')
    {
        res = res * 10 + (str[counter] - '0');
        counter++;
    }
    return res;
}

int get_number()
{
    if (isdigit(str[counter]))
        return get_number_without_sign();
    else
        if (str[counter] == '-')
        {
            counter++;
            return get_number_without_sign() * (-1);
        }
        else
            throw "Unexpected symbol";
}

int get_term()
{
    int res = get_number();
    while (counter < str.length() && (str[counter] == '*' || str[counter] == '/'))
    {
        if (str[counter] == '*')
        {
            counter++;
            res *= get_number();
        }
        if (str[counter] == '/')
        {
            counter++;
            res /= get_number();
        }
    }
    return res;
}


int calculate()
{
    int res = get_term();
    while (counter < str.length() && (str[counter] == '+' || str[counter] == '-'))
    {
        if (str[counter] == '+')
        {
            counter++;
            res += get_term();
        }
        if (str[counter] == '-')
        {
            counter++;
            res -= get_term();
        }
    }
    return res;
}

void delete_spaces()
{
    for (int i = 0; i < str.length(); i++)
        if (str[i] == ' ')
            str = str.erase(i, 1);
        else
            if (!isdigit(str[i]))
                if(str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/')
                    throw "Unexpected symbol";
    if (str.length() == 0)
        throw "Empty expression";
}

int main(int argc, const char * argv[])
{
    str = argv[1];
    if (argc < 2)
    {
        cout << "No expression to calculate" << endl;
        return 1;
    }
    if (str.length() == 0)
        throw "Empty expression";
    delete_spaces();
    
    try
    {
        int result = calculate();
        cout << result << endl;
    }
    
    catch (const char* str) {
        cout << str << endl;
    }
    
    return 0;
}
