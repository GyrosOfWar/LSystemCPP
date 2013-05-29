//
// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "TurtleDrawing.h"
#include "LSystem.h"
#include <iostream>

using std::endl;
using std::cout;

// Constants
const static int xSize = 1280;
const static int ySize = 800;
const static double Pi = 3.141592653589793;
const static int NumLSystems = 5;

// Globals
sf::Transform transform;
sf::Vector2i oldMousePos(0, 0);
bool mouseDrag = false;
float scale = 1.0f;
std::vector<LSystem> lsystems;
int selectedLSystem = 0;
vector<sf::VertexArray> verts;

double toRadians(double deg) {
	return deg * (Pi / 180.0);
}

double toDegrees(double rad) {
	return rad * (180.0 / Pi);
}

void createLSystems() {
	vector<Rule> dragon_curve_rules;
	dragon_curve_rules.push_back(Rule('X', "X+YF"));
	dragon_curve_rules.push_back(Rule('Y', "FX-Y"));
	lsystems.push_back(LSystem("Dragon Curve", dragon_curve_rules, "FX", Pi / 2.0, 11, 10, xSize, ySize));
	lsystems[0].step();

	vector<Rule> koch_rules;
	koch_rules.push_back(Rule('F', "F+F-F-F+F"));
	lsystems.push_back(LSystem("Koch Curve", koch_rules, "F", Pi / 2.0, 4, 15, xSize, ySize));
	lsystems[1].step();

	vector<Rule> plant_rules;
	plant_rules.push_back(Rule('F', "C0FF-[C1-F+F+F]+[C2+F-F-F]"));
	lsystems.push_back(LSystem("Fractal Plant", plant_rules, "F", toRadians(22), 4, 5, xSize, ySize));
	lsystems[2].step();

	vector<Rule> sierpinski_rules;
	sierpinski_rules.push_back(Rule('F', "F-G+F+G-F"));
	sierpinski_rules.push_back(Rule('G', "GG"));
	lsystems.push_back(LSystem("Sierpinski Triangle", sierpinski_rules, "F-G-G", toRadians(120), 6, 5, xSize, ySize));
	lsystems[3].step();

	vector<Rule> screen_filling_curve_rules;
	screen_filling_curve_rules.push_back(Rule('X', "-YF+XFX+FY-"));
	screen_filling_curve_rules.push_back(Rule('Y', "+XF-YFY-FX+"));
	lsystems.push_back(LSystem("Screen Filling Curve", screen_filling_curve_rules, "X", toRadians(90), 6, 5, xSize, ySize));
	lsystems[4].step();
}

void redraw(int selected) {
	lsystems[selected].clear();
	lsystems[selected].step();
	verts[selected] = lsystems[selected].draw();
}

void handleEvents(sf::Event& event, sf::RenderWindow& window) {
	switch(event.type) {
	case sf::Event::Closed: 
		window.close();
		break;
	case sf::Event::MouseButtonPressed:
		mouseDrag = true;
		break;
	case sf::Event::MouseButtonReleased:
		mouseDrag = false;
		break;
	case sf::Event::MouseMoved:
		if(mouseDrag) {
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			sf::Vector2i delta = pos - oldMousePos;
			oldMousePos = pos;
			transform.translate(sf::Vector2f(delta.x / scale, delta.y / scale));
		}
	case sf::Event::KeyPressed:
		int newIterCount;
		switch(event.key.code) {

		case sf::Keyboard::W:
			selectedLSystem = (selectedLSystem + 1) % NumLSystems;
			break;
		case sf::Keyboard::S:
			selectedLSystem--;
			if(selectedLSystem < 0)
				selectedLSystem = NumLSystems - 1;
			break;
		case sf::Keyboard::O:
			newIterCount = lsystems[selectedLSystem].getIterations() - 1;
			lsystems[selectedLSystem].setIterations(newIterCount > 0 ? newIterCount : 1);
			redraw(selectedLSystem);
			break;
		case sf::Keyboard::P:
			newIterCount = lsystems[selectedLSystem].getIterations() + 1;
			lsystems[selectedLSystem].setIterations(newIterCount);
			redraw(selectedLSystem);
			break;
		}
		break;
	case sf::Event::MouseWheelMoved:
		int mouseWheel = event.mouseWheel.delta;
		if(mouseWheel == -1) {
			transform.scale(1.1f, 1.1f);
			scale *= 1.1f;
		}
		if(mouseWheel == 1) {
			transform.scale(0.9f, 0.9f);
			scale *= 0.9f;
		}
		break;
	}
}

int main() {
	createLSystems();
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(xSize, ySize), "Window");
	for(unsigned int i = 0; i < lsystems.size(); i++) {
		verts.push_back(lsystems[i].draw());
	}	

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			handleEvents(event, window);
		}
		window.clear();
		window.draw(verts[selectedLSystem], transform);
		window.display();
	}
	return 0;
}
