#include "Rule.h"
#include "TurtleDrawing.h"
#include "stdafx.h"

using std::string;
using std::vector;

class LSystem {
	vector<Rule> rules;
	string axiom;
	double angle;
	int iterations;
	int distance;
	string name;
	sf::Color colorList[3];
public:
	explicit LSystem(string name, vector<Rule> rules, string axiom, double angle, int iterations, int distance, int startX, int startY);
	void draw(TurtleDrawing& td);
	void clear();

	void setIterations(int);
	int getIterations();
	string getName();
	string getCurrent();
private: 
	string step();
	string apply_rules(const string state, const vector<Rule>& rules);
};