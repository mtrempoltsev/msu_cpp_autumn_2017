#ifndef RDPARSER_H_
#define RDPARSER_H_

#include <unordered_map>
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <string>

/*
 *  Singlton pattern. 
 */
class RDParser{

public:

	// The type in which the conversion is performed.
	typedef double RType;

	// The only way to create an instance
	static RDParser& Instance(){
		static RDParser parser;
		return parser;
	}

	RType 	calculateExprFromStr(char * str);

private:

	// Associative array of named constants. The names are in lowercase.
	std::unordered_map<std::string, RType> NamedConstants;

private:

	// The prefix _ means that the method is private

	bool 	_isbinop(const char & c);
	void 	_checkbrackets(const char*);
	char * 	_skipspace(char * str);

	RType 	_prim(const char*& str);
	RType 	_term(const char*& str);
	RType	_expr(const char*& str);


	// Constructor and Destructor are private. Object can be created only 1 time.
	RDParser(){
		NamedConstants = {
			{"pi", 3.14},
			{"e", 2.7},
		};
	};
	~RDParser(){};

	// Singleton dont need copyconstructor and assignment operation.
	RDParser(RDParser const&)=delete;
	RDParser& operator=(RDParser const&)=delete;
	
};


#endif









