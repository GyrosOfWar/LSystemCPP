#include "stdafx.h"
#include "LSystem.h"

LSystem::LSystem(string name, vector<Rule> rules, string axiom,
				 double angle, int iterations, int distance, int startX, int startY):
	name(name),
	rules(rules),
	axiom(axiom),
	angle(angle),
	iterations(iterations),
	distance(distance) {
		current = axiom;
		td = TurtleDrawing(startX, startY);
		colorList[0] = sf::Color(140, 80, 60, (int) (0.75 * 255.0));
		colorList[1] = sf::Color(24, 180, 24, (int) (0.75 * 255.0));
		colorList[2] = sf::Color(64, 255, 64, 128);
}

void LSystem::step() {
	for(int i = 0; i < iterations; i++) {
		current = apply_rules(current, rules);
	}
}
// Applies a set of rules to a given state string and returns the new state.
string LSystem::apply_rules(const string state, const vector<Rule>& rules) {
	string result;
	// Iterate over the state string
	for(auto it = state.begin(); it != state.end(); ++it) {
		char current = (char) *it;
		Rule match;
		// Check for a matching rule by iterating over all rules
		for(auto jt = rules.begin(); jt != rules.end(); ++jt) {
			if(jt->getLHS() == current) {
				match = *jt;
			}
		}
		// If there was no match, append the current character
		if(match.getLHS() == '\0') {
			result += current;
		// Else append the RHS of the rule
		} else {
			result += match.getRHS();
		}
	}
	return result;
}
// Takes the current state string (current) and draws it to a VertexArray,
// which it returns.
sf::VertexArray LSystem::draw() {
	// Iterate over the state string and perform an action based
	// on the current character
	for(auto it = current.begin(); it != current.end(); ++it) {
		int color;
		switch(*it) {
		// F and G move the turtle forward
		case 'F':
			td.forward(distance);
			break;
		case 'G':
			td.forward(distance);
			break;
		case '+':
		// + increases, - decreases the angle
			td.anglePlus(angle);
			break;
		case '-':
			td.angleMinus(angle);
			break;
		// [ pushes the current position and angle to the stack
		case '[':
			td.pushStack();
			break;
		// ] gets the position and angle from the stack and delets it (pop())
		case ']':
			td.popStack();
			break;
		// Colors are of the form
		// C{0, 2}
		// Look ahead one character, extract the integer value
		// and use it as an index for the color array.
		// Concept inspired by/stolen from http://www.kevs3d.co.uk/dev/lsystems/
		case 'C':
			color = *(++it) - '0';
			td.setColor(colorList[color]);
			break;
		case 'X':
		case 'Y':
		case '0':
		case '1':
		case '2':
		case '3':
			break;
		// TODO throw an actual exception
		default:
			throw "Not a valid character!";
		}
	}
	return td.getVertices();
}

TurtleDrawing LSystem::getDrawing() {
	return td;
}

void LSystem::setIterations(int i) {
	iterations = i;
}

int LSystem::getIterations() {
	return iterations;
}

void LSystem::clear() {
	td.clear();
	current = axiom;
}

string LSystem::getName() {
	return name;
}

string LSystem::getCurrent() {
	return current;
}
