#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
std::string ExecAndGetResult(const string& cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = _popen(cmd.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    }
    catch (...) {
        _pclose(pipe);
        throw;
    }
    _pclose(pipe);
    return result;
}
#else
std::string ExecAndGetResult(const string& cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    }
    catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}
#endif

string response_invalid_argument = "invalid_argument exception\n";
string response_runtime_error = "runtime_error exception\n";
string response_exception = "Unknown exception\n";
string response_division_by_zero = "Division by zero";
string response_invalid_token = "The expression contains an incorrect sequence of tokens";
string response_invalid_symbol = "The expression contains an incorrect symbol";
string response_invalid_brackets = "The expression contains an incorrect sequence of brackets";
string response_presentation_error = "Number in the expression cant`t be represented";

struct Test {
    enum TYPE
    {
        CORRECT,
        INCORRECT
    };
    Test(const string& req, const string& res, TYPE t) : request(req), response(res), type(t) {};
    string request;
    string response;
    TYPE type;

};

vector<Test> int_tests = { 
{"2+2", "4", Test::CORRECT},
{"2+ 2", "4", Test::CORRECT},
{"2 +2", "4", Test::CORRECT},
{"2 + 2", "4", Test::CORRECT},
{"2 +   2", "4", Test::CORRECT},
{"2", "2", Test::CORRECT},
{"-2", "-2", Test::CORRECT},
{"-2 - 2", "-4", Test::CORRECT},
{"2 -2", "0", Test::CORRECT},
{"2 - -2", "4", Test::CORRECT},
{"100 + 1", "101", Test::CORRECT},
{"101 + 1", "102", Test::CORRECT},
{"8 - 6 * 2 / 2", "2", Test::CORRECT},
{"8 - 6 / 2 * 2", "2", Test::CORRECT},
{"8 - 6 / 2 * -2", "14", Test::CORRECT},
{"2 + 3 * 4 - -2", "16", Test::CORRECT},
{ "(2 + 4 / Pi * (12))", "14", Test::CORRECT },
{ " ((((8 - 1) + 3) * 6) - ((3 + 7) * 2))", "40", Test::CORRECT},
{ " ((((8 - 1) + 3) * 6) * ((3 + 7) * 2)) + (((5)) + 1) + 1 * 6 / 3", "1208", Test::CORRECT },
{"2 + 2 /(6 - 2*3)", response_runtime_error + response_division_by_zero, Test::INCORRECT},
{"7 + 12 * Pi + E", response_invalid_argument + response_invalid_symbol, Test::INCORRECT},
{"7 * ((4 + 5) * 2 + 1 / 5", response_invalid_argument + response_invalid_brackets, Test::INCORRECT},
{ "151 * 11 ++ 2" , response_invalid_argument + response_invalid_token, Test::INCORRECT},
{ "1000000000 + 1000000000 + 20000000000", response_invalid_argument + response_presentation_error, Test::INCORRECT},
{ "-1000000000 + 1000000000 + -20000000000", response_invalid_argument + response_presentation_error, Test::INCORRECT },
{"1.5 + 1.5", response_invalid_argument + response_invalid_symbol, Test::INCORRECT } };

vector<Test> double_tests = {
{ "431.14132141 + 6.525341", "437.66666241", Test::CORRECT },
{ "2.0506 * 77.003", "157.9023518", Test::CORRECT },
{ "(((35.2 + 42/3) - 23.1) * 100) + 111.1 * 333.3 - (4.1 + 6.9) / 0.011", "38639.63", Test::CORRECT },
{ "284.5 * 123.0", "34993.5", Test::CORRECT },
{ "(569.449 / 146.2  + 7.105)* ( 1924.5 + 47.3 / 11)", "21216.8", Test::CORRECT },
{ "284.5 * 123.0 + (569.449 / 146.2  + 7.105)* ( 1924.5 + 47.3 / 11)", "56210.3", Test::CORRECT },
{ "284.5 * 123.0 + (569.449 / 146.2  + 7.105)* ( 1924.5 + 47.3 / 11) + 374.5", "56584.8", Test::CORRECT },
{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\
000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\
000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\
00000000000000000000000000000000000000000000000000000000000000000000000", response_invalid_argument + response_presentation_error, Test::INCORRECT}
};


void prepare_tests(const string& prog_name, const vector<Test>& tests) {
    string response, request, append;
    cout << endl << "##################################" << endl << endl;
    for (unsigned int i = 0; i < tests.size(); ++i) {
        cout << "Expression: " << "\"" << tests[i].request << "\"" << endl;
        cout << "Correct result: " << tests[i].response << endl;
        if (tests[i].type == Test::CORRECT) {
            append = "";
        }
        else if (tests[i].type == Test::INCORRECT)
        {
            append = " 2>&1 ";
        }
        append = " 2>&1 ";
        response = ExecAndGetResult(prog_name + append + " \"" + tests[i].request + "\"");
        response.resize(response.length() - 1);
        cout << "Answer: " << response << endl;
        bool checker_res;
        if (tests[i].type == Test::CORRECT) {
            checker_res = response == tests[i].response;
        }
        else if (tests[i].type == Test::INCORRECT) {
            checker_res = strncmp(tests[i].response.c_str(), 
                                   response.c_str(),
                                   tests[i].response.length()) == 0 ? true : false;
        }
        else
        {
            cerr << "Undefined error in prepare_tests function" << endl;
            exit(1);
        }
        cout << "Checker result: " << (checker_res ? "OK" : "ERROR") << endl;
        cout << endl << "##################################" << endl << endl;
    }
}


int main()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    string prog_name_int = "calc_test_int.exe";
    string prog_name_double = "calc_test_double.exe";
    cout << "Compiling INT version..." << endl;
    ExecAndGetResult("g++ -O2 -Wall -Wextra ./CalculatorV5.cpp -DINT= -o calc_test_int.exe");
    cout << "Compiling LONG version..." << endl;
    ExecAndGetResult("g++ -O2 -Wall -Wextra ./CalculatorV5.cpp -DLONG= -o calc_test_long.exe");
    cout << "Compiling DOUBLE version..." << endl;
    ExecAndGetResult("g++ -O2 -Wall -Wextra ./CalculatorV5.cpp -DDOUBLE= -o calc_test_double.exe");
#else
    string prog_name_int = "./calc_test_int";
    string prog_name_double = "./calc_test_double";
    cout << "Compiling INT version..." << endl;
    ExecAndGetResult("g++ -O2 -Wall -Wextra ./CalculatorV5.cpp -DINT= -o calc_test_int");
    cout << "Compiling LONG version..." << endl;
    ExecAndGetResult("g++ -O2 -Wall -Wextra ./CalculatorV5.cpp -DLONG= -o calc_test_long");
    cout << "Compiling DOUBLE version..." << endl;
    ExecAndGetResult("g++ -O2 -Wall -Wextra ./CalculatorV5.cpp -DDOUBLE= -o calc_test_double");
#endif

    cout << endl << "Prepare int tests" << endl;
    prepare_tests(prog_name_int, int_tests);

    cout << endl << "Prepare double tests" << endl;
    prepare_tests(prog_name_double, double_tests);

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    cout << "Delete temporary files..." << endl;
    ExecAndGetResult("del calc_test_int.exe calc_test_long.exe calc_test_double.exe");
#else
    cout << "Delete temporary files..." << endl;
    ExecAndGetResult("rm calc_test_int calc_test_long calc_test_double");
#endif
    return 0;
}

