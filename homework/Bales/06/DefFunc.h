#pragma once
#include <iostream>
#include <utility>
#include <unordered_map>
#include <string>
#include <cstring>
#include <sstream>

enum class TExitCode {
    OK,
    INCORRECT_PARAMS, // Ошибка: некорректное кол-во аргументов
    INCORRECT_INPUT, // Ошибка: некорректное арифметическое выражение
    ZERO_DIVISION, // Ошибка: деление на 0
    FAILED_TO_PARSE // Не удалось распарсить токен
};

class ExitCodeException: public std::exception {
public:    
    ExitCodeException(TExitCode exitCode); 
    virtual const char* what() const throw(); 
    const TExitCode& GetExitCode() const;
private:
    TExitCode _exitCode;
};