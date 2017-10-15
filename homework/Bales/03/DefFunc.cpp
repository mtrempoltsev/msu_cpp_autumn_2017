#include "DefFunc.h"

std::unordered_map<std::string, double> Constants = {
    { "e", 2.7 },
    { "Pi", 3.14 }
};

ExitCodeException::ExitCodeException(TExitCode exitCode) {
    this->_exitCode = exitCode;
}

const char* ExitCodeException::what() const throw() {    
    return "Error: look exit code";
}

const TExitCode& ExitCodeException::GetExitCode() const {
    return this->_exitCode;
}
