#include "stdafx.h"

using std::string;

class Rule {
	char lhs;
	string rhs;
	double weight;
public:
	Rule(char lhs, string rhs, double weight);
	Rule(char lhs, string rhs);
	Rule();
	char getLHS() const;
	string getRHS() const;
	double getWeight() const;
	void setLHS(const char c);
	void setRHS(const string s);
	bool equals(const Rule& other) const;
};