#include <iostream>
#include <string>

using namespace std;

class Calculator
{
public:
    Calculator(string strr)
    {
        str = strr;
        counter = 0;
    }
    
    double result()
    {
        double res = calculate();
        if (counter != str.length())
            throw "Invalid expression";
        return res;
    }

private:
    string str;
    int counter;
    
    double get_number_without_sign()
    {
        double res = 0;
        if (counter < str.length() && str[counter] == '(')
        {
            counter++;
            res = calculate();
            if (counter < str.length() && str[counter] == ')')
                counter++;
            else
                throw "Invalid braces";
            return res;
        }
        else
           if (counter < str.length() && str[counter] == ')')
                throw "Invalid braces";
            else
                if (counter < str.length() && str[counter] == 'e') //если e
                {
                    counter++;
                    return 2.7;
                }
                    else
                        if (counter < str.length() && str[counter] == 'P') //если Pi
                        {
                            counter++;
                            if (counter < str.length() && str[counter] == 'i')
                            {
                                counter++;
                                return 3.14;
                            }
                        }
                        else //если число
                        {
                            while (counter < str.length() && str[counter] <= '9' && str[counter] >= '0')
                            {
                                res = res * 10 + (str[counter] - '0');
                                counter++;
                            }
                            return res;
                        }
        return 1;
    }

    double get_number()
    {
        
        double res = 0;
        if (counter < str.length() && str[counter] == '(')
        {
            counter++;
            res = calculate();
            if (counter < str.length() && str[counter] == ')')
                counter++;
            else
                throw "Invalid braces";
            return res;
            
        }
        else
           if (counter < str.length() && str[counter] == ')')
                throw "Invalid braces";
            else
                    if (str[counter] == '-')
                    {
                        counter++;
                        return get_number_without_sign() * (-1);
                    }
                    else
                        return get_number_without_sign();
        return 1;
    }

    double get_term() //слагаемое
    {
        
        double res = 0;
        if (counter < str.length() && str[counter] == '(')
        {
            counter++;
            res = calculate();
            if (counter < str.length() && str[counter] == ')')
                counter++;
            else
                throw "Invalid braces";
        }
        else
            if (counter < str.length() && str[counter] == ')')
                 throw "Invalid braces";
            else
                res = get_number();
        
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
                int n = get_number();
                if (n)
                    res /= n;
                else
                    throw "Invalid operation";
            }
        }
         return res;
    }
    
    double calculate()
    {
        
        double res = get_term();
        
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
    
};
    
void delete_spaces(string& str)
{
    for (int i = 0; i < str.length(); i++)
        if (str[i] == ' ')
        {
            str = str.erase(i, 1);
            i--;
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
        Calculator Calc(str);
        double result = Calc.result();
        cout << result << endl;
        return 0;
    }
    
    catch (const char* str)
    {
        cout << str << endl;
        return 1;
    }
}
