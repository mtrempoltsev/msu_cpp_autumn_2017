#ifndef ERROR_H
#define ERROR_H

using namespace std;

class Error {

public:
	virtual std::string err_msg() const = 0;
};

// ----------------------------------------------

class ArgumentError : public Error {

public:
	ArgumentError(string&& _msg) : msg(_msg) {}

	std::string err_msg() const {
		return "Argument error" + msg;
	}

private:
	std::string msg;
};

// ----------------------------------------------

class RuntimeError : public Error {

public:
	RuntimeError(string&& _msg) : msg(_msg) {}

	std::string err_msg() const {
		return "RuntimeError: " + msg;
	}

private:
	std::string msg;
};

// ----------------------------------------------

class RangeError : public Error {

public:
	RangeError(string&& _msg) : msg(_msg) {}

	std::string err_msg() const {
		return "RangeError: " + msg;
	}

private:
	std::string msg;
};

// ----------------------------------------------

class LogicError : public Error {

public:
	LogicError(string&& _msg) : msg(_msg) {}

	std::string err_msg() const {
		return "Logic error:" + msg;
	}

private:
	std::string msg;
};

// ----------------------------------------------

#endif
