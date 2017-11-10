#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Error
{
    string message;
public:
    Error(string&& message_)
    {
        message = message_;
    }
    const string getMessage() const
    {
        return message;
    }
};

template <class T>
class Calculator
{
public:
    Calculator(string strr)
    {
        str = strr;
        counter = 0;
    }
    
    
    T calculate()
    {
        T res = get_term();
       
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
    
    T result()
    {
        T res = calculate();
        if (counter != str.length())
            throw Error("Invalid expression");
        return res;
    }

private:
    string str;
    int counter;
    
    T get_number_without_sign()
    {
        T res = 0;
        if (counter < str.length() && str[counter] == '(')
        {
            counter++;
            res = calculate();
            if (counter < str.length() && str[counter] == ')')
                counter++;
            else
                throw Error("Invalid braces");
            return res;
        }
        else
           if (counter < str.length() && str[counter] == ')')
                throw Error("Invalid braces");
            else
                if (counter < str.length() && str[counter] == 'e') //если e
                {
                    counter++;
                    return (T)2.7;
                }
                    else
                        if (counter < str.length() && str[counter] == 'P') //если Pi
                        {
                            counter++;
                            if (counter < str.length() && str[counter] == 'i')
                            {
                                counter++;
                                return (T)3.14;
                            }
                        }
                        else
                           if (counter < str.length() && isdigit(str[counter]))
                            {
                                double res2 = 0;
                                long long int res1 = 0;
                                while (counter < str.length() && str[counter] <= '9' && str[counter] >= '0')
                                {
                                    //замена parser
                                    res1 = res1 * 10 + (str[counter] - '0');
                                    counter++;
                                    if (!(res1 >= numeric_limits<T>::lowest() && res1 <= numeric_limits<T>::max()))
                                        throw Error("Out of limits");
                                }
                                if (counter < str.length() && str[counter] == '.')
                                {
                                    counter++;
                                    if (counter < str.length() && !(isdigit(str[counter])))
                                        throw Error("No digits after point");
                                    double temp = 0;
                                    double n = 0.1;
                                    while (counter < str.length() && str[counter] <= '9' && str[counter] >= '0')
                                    {
                                        temp += (str[counter] - '0') * n;
                                        n /= 10;
                                        counter++;
                                    }
                                    res2 = temp + res1;
                                    return res2;
                                }
                                return res1;
                            }
                           else
                               throw Error("Invalid expression");
                               
        
        return 1;
    }

    T get_number()
    {
        T res = 0;
        if (counter < str.length() && str[counter] == '(')
        {
            counter++;
            res = calculate();
            if (counter < str.length() && str[counter] == ')')
                counter++;
            else
                throw Error("Invalid braces");
            return res;
            
        }
        else
           if (counter < str.length() && str[counter] == ')')
                throw Error("Invalid braces");
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

    T get_term() //слагаемое
    {
        T res = 0;
        if (counter < str.length() && str[counter] == '(')
        {
            counter++;
            res = calculate();
            if (counter < str.length() && str[counter] == ')')
                counter++;
            else
                throw Error("Invalid braces");
        }
        else
            if (counter < str.length() && str[counter] == ')')
                 throw Error("Invalid braces");
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
                T n = get_number();
                if (n)
                    res /= n;
                else
                    throw Error("Invalid operation");
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
        throw Error("Empty expression");
}

template <class T>
int check2(T value1, T value2)
{
    if (abs(value1 - value2) > 0.01)
        return 0;
    else
        return 1;
}

template <class T>
void check(string text, T value, bool correct) {
    try
    {
        delete_spaces(text);
        Calculator<T> calc(text);
        if (!check2<T>(calc.result(), value))
            cout << text << " error" << endl;

    }
    catch (const Error& error)
    {
        if (correct)
            cout << text << "error" << endl;
    }
    catch (...)
    {
        
    }
}

void test() {

    check<int>("2", 2, true);
    check<int>("-2", -2, true);
    check<int>("2 +2", 4, true);
    check<int>("(((2 + 2)) * 2)", 8, true);
    check<int>("-Pi", -3, true);
    check<int>("e", 2, true);
    check<int>("1+ - 1", 0, true);
    check<int>("8 - 6 * 2 / 2", 2, true);
    check<int>("8 - 6 / 2 * 2", 2, true);
    check<int>("8 - 6 / 2 * -2", 14, true);
    check<int>("2 + 3 * 4 - -2", 16, true);
    check<int>("(5 + 3 * (9 / Pi) * 4) + (1)", 42, true);
    check<int>("(5 + 3 * (9 / Pi) * 4) + (1 * e)", 43, true);
    
    check<long>("2", 2, true);
    check<long>("-2", -2, true);
    check<long>("2 +2", 4, true);
    check<long>("(((2 + 2)) * 2)", 8, true);
    check<long>("-Pi", -3, true);
    check<long>("e", 2, true);
    check<long>("(1+ - 1)", 0, true);
    check<long>("8 - 6 * 2 / 2", 2, true);
    check<long>("8 - 6 / 2 * 2", 2, true);
    check<long>("8 - 6 / 2 * -2", 14, true);
    check<long>("2 + 3 * 4 - -2", 16, true);
    check<long>("(5 + 3 * (9 / Pi) * 4) + (1)", 42, true);
    check<long>("(5 + 3 * (9 / Pi) * 4) + (1 * e)", 43, true);
    
    check<double>("2", 2, true);
    check<double>("-2", -2, true);
    check<double>("2 +2", 4, true);
    check<double>("(((2 + 2)) * 2)", 8, true);
    check<double>("-Pi", -3.14, true);
    check<double>("e", 2.7, true);
    check<double>("Pi+e", 5.84, true);
    check<double>("(1.3+ - 1.2)", 0.1, true);
    check<double>("8.1 - 6 * 2 / 2", 2.1, true);
    check<double>("8.1 - 6.1 / 2 * 2", 2, true);
    check<double>("8 - 6 / 2 * -2.5", 15.5, true);
    check<double>("(5 + 3 * (9 / Pi) * 4) + (1 * e)", 42.096, true);
    check<double>("2.12344 + 3 * 4 - -2.444", 16.56744, true);
    
    check<int>("2/0", 0, false);
    check<int>("2 -+ 2", 0, false);
    check<int>("2 ++ 2", 0, false);
    check<long>("2 c (2)", 0, false);
    check<double>("(2/1))", 4., false);
    check<int>("100000000000000000000000000000000000000000000000000000000000000000000000000", 0, false);
    check<double>("100000000000000000000000000000000000000000000000000000000000000000000000000", 0, false);
    
}

int main(int argc, const char * argv[])
{
    try
    {
        
        if (argc < 2)
        {
            test();
            return 0;
        }
        string str = argv[1];
        if (str.length() == 0)
            throw Error("Empty expression");
        delete_spaces(str);
        
        Calculator<double> Calc(str);
        double result = Calc.result();
        cout << result << endl;
        return 0;
    }
    
    catch (const Error& error)
    {
        cerr << error.getMessage() << endl;
        return 1;
    }
    catch (...)
    {
        
    }
}
