#include "stdafx.h"
#include "Rule.h"

Rule::Rule(char lhs, string rhs): lhs(lhs), rhs(rhs) {
}

Rule::Rule() {
	lhs = '\0';
	rhs = "\0";
}

char Rule::getLHS() const {
	return lhs;
}

string Rule::getRHS() const {
	return rhs;
}

void Rule::setLHS(const char c) {
	lhs = c;
}

void Rule::setRHS(const string s) {
	rhs = s;
}