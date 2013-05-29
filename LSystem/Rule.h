#include "stdafx.h"

using std::string;

class Rule {
	char lhs;
	string rhs;
public:
	Rule(char lhs, string rhs);
	Rule();
	char getLHS() const;
	string getRHS() const;
	void setLHS(const char c);
	void setRHS(const string s);
};