#include "stdafx.h"
#include "Rule.h"

Rule::Rule(char lhs, string rhs, double weight): lhs(lhs), rhs(rhs), weight(weight) {
}

Rule::Rule() {
	lhs = '\0';
	rhs = "\0";
	weight = -1.0;
}

Rule::Rule(char lhs, string rhs): lhs(lhs), rhs(rhs) {
	weight = -1.0;
}

char Rule::getLHS() const {
	return lhs;
}

string Rule::getRHS() const {
	return rhs;
}

double Rule::getWeight() const {
	return weight;
}

void Rule::setLHS(const char c) {
	lhs = c;
}

void Rule::setRHS(const string s) {
	rhs = s;
}