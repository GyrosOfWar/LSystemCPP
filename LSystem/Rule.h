#include "stdafx.h"

using std::string;

class Rule {
	char lhs;
	string rhs;
public:
	Rule(char lhs, string rhs);
	Rule();
	char getLHS();
	string getRHS();
	void setLHS(char c);
	void setRHS(string s);
};