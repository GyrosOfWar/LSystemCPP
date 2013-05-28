#include "stdafx.h"
#include "Rule.h"

Rule::Rule(char lhs, string rhs): lhs(lhs), rhs(rhs) {
}

Rule::Rule() {
	lhs = '\0';
	rhs = "\0";
}

char Rule::getLHS() {
	return lhs;
}

string Rule::getRHS() {
	return rhs;
}

void Rule::setLHS(char c) {
	lhs = c;
}

void Rule::setRHS(string s) {
	rhs = s;
}