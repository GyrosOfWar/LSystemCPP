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
	string name;
	sf::Color colorList[3];
public:
	explicit LSystem(string name, vector<Rule> rules, string axiom, double angle, int iterations, int distance, int xSize, int ySize);
	void step();
	sf::VertexArray draw();
	void clear();

	TurtleDrawing getDrawing();
	void setIterations(int);
	int getIterations();
	string getName();
	string getCurrent();
private: 
	string apply_rules(string state, vector<Rule> rules);
};