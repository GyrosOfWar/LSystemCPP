#include "stdafx.h"
#include "LSystem.h"

LSystem::LSystem(string name, vector<Rule> rules, string axiom, double angle, int iterations, int distance, int xSize, int ySize):
	name(name), rules(rules), axiom(axiom), angle(angle), iterations(iterations), distance(distance), xSize(xSize), ySize(ySize) {
		current = axiom;
		td = TurtleDrawing(xSize, ySize);
		colorList[4];
		colorList[0] = sf::Color(140, 80, 60, (int) (0.75 * 255.0));
		colorList[1] = sf::Color(24, 180, 24, (int) (0.75 * 255.0));
		colorList[2] = sf::Color(64, 255, 64, 128);
}

void LSystem::step() {
	for(int i = 0; i < iterations; i++) {
		current = apply_rules(current, rules);
	}
}

string LSystem::apply_rules(string state, const vector<Rule> rules) {
	string result;
	// Iterate over the state string
	for(auto it = state.begin(); it != state.end(); ++it) {
		char current = (char) *it;
		Rule match;
		// Check for matching rule
		for(auto jt = rules.begin(); jt != rules.end(); ++jt) {
			Rule r = (Rule) *jt;
			if(r.getLHS() == current) {
				match = r;
			}
		}
		if(match.getLHS() == '\0') {
			result += current;
		} else {
			result += match.getRHS();
		}
	}
	return result;
}

sf::VertexArray LSystem::draw() {
	for(auto it = current.begin(); it != current.end(); ++it) {
		float x, y, stackAngle = 0.0f;
		char c = (char) *it;
		int color;
		switch(c) {
		case 'F':
			td.forward(distance);
			break;
		case 'G':
			td.forward(distance);
			break;
		case '+':
			td.anglePlus(angle);
			break;
		case '-':
			td.angleMinus(angle);
			break;
		case '[':
			td.pushStack(td.getAngle());
			td.pushStack(td.getPosition().x);
			td.pushStack(td.getPosition().y);
			break;
		case ']':
			y = td.popStack();
			x = td.popStack();
			stackAngle = td.popStack();
			td.moveTo(x, y);
			td.setAngle(stackAngle);
			break;
		case 'C':
			color = *(++it) - '0';
			td.setColor(colorList[color]);
			std::cout << (int) colorList[color].r << ", " << (int) colorList[color].g << ", " << (int) colorList[color].b << (int) colorList[color].a << std::endl;
			break;
		case 'X':
			break;
		case 'Y':
			break;
		case '0':
			break;
		case '1':
			break;
		case '2':
			break;
		case '3':
			break;

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
