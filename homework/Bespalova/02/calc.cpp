#include <iostream>
#include <string>

using namespace std;
//string str;
//int counter = 0;

int get_number_without_sign(int& counter, string& str)
{
    int res = 0;
    while (counter < str.length() && str[counter] <= '9' && str[counter] >= '0')
    {
        res = res * 10 + (str[counter] - '0');
        counter++;
    }
    return res;
}

int get_number(int& counter, string& str)
{
    if (isdigit(str[counter]))
        return get_number_without_sign(counter, str);
    else
        if (str[counter] == '-')
        {
            counter++;
            return get_number_without_sign(counter, str) * (-1);
        }
        else
            throw "Unexpected symbol";
}

int get_term(int& counter, string& str)
{
    int res = get_number(counter, str);
    while (counter < str.length() && (str[counter] == '*' || str[counter] == '/'))
    {
        if (str[counter] == '*')
        {
            counter++;
            res *= get_number(counter, str);
        }
        if (str[counter] == '/')
        {
            counter++;
            res /= get_number(counter, str);
        }
    }
    return res;
}


int calculate(int& counter, string& str)
{
    int res = get_term(counter, str);
    while (counter < str.length() && (str[counter] == '+' || str[counter] == '-'))
    {
        if (str[counter] == '+')
        {
            counter++;
            res += get_term(counter, str);
        }
        if (str[counter] == '-')
        {
            counter++;
            res -= get_term(counter, str);
        }
    }
    return res;
}

void delete_spaces(string& str)
{
    for (int i = 0; i < str.length(); i++)
        if (str[i] == ' ')
        {
            str = str.erase(i, 1);
            i--;
        }
        else
        {
            
            if (!isdigit(str[i]))
                if(str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/')
                    throw "Unexpected symbol";
            if(isalpha(str[i]))
                throw "Unexpected symbol";
        }
    if (str.length() == 0)
        throw "Empty expression";
}

int main(int argc, const char * argv[])
{
    try
    {
        string str = argv[1];
        if (argc < 2)
        {
            cout << "No expression to calculate" << endl;
            return 1;
        }
        if (str.length() == 0)
            throw "Empty expression";
        delete_spaces(str);
        
        int counter = 0;
        int result = calculate(counter, str);
        cout << result << endl;
        return 0;
    }
    
    catch (const char* str) {
        cout << str << endl;
        return 1;
    }
    
    
}
