#include "Rule.h"
#include "TurtleDrawing.h"
#include "stdafx.h"

using std::string;
using std::vector;

class LSystem {
	vector<Rule> rules;
	string axiom;
	string current;
	double angle;
	int iterations;
	int distance;
	TurtleDrawing td;
	int xSize;
	int ySize;
public:
	LSystem(vector<Rule> rules, string axiom, double angle, int iterations, int distance, int xSize, int ySize);
	void step();
	sf::VertexArray draw();
	TurtleDrawing getDrawing();
	void setIterations(int);
	int getIterations();
private: 
	string apply_rules(string state, vector<Rule> rules);
};