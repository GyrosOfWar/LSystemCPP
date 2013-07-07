//
// main.cpp : Defines the entry point for the application.
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
const static float ZoomInFactor = 1.2f;
const static float ZoomOutFactor = 0.8f;

// Globals
sf::Vector2i oldMousePos(0, 0);
bool mouseDrag = false;
float scale = 1.0f;
std::vector<LSystem> lsystems;
int selectedLSystem = 0;
vector<TurtleDrawing> drawings;
float grayscale = 0;

double toRadians(double deg) {
	return deg * (Pi / 180.0);
}

double toDegrees(double rad) {
	return rad * (180.0 / Pi);
}

// Fills the lsystems-Vector with some L-Systems.
void createLSystems() {
    vector<Rule> dragon_curve_rules;
    dragon_curve_rules.push_back(Rule('X', "X+YF"));
    dragon_curve_rules.push_back(Rule('Y', "FX-Y"));

    vector<Rule> koch_rules;
    koch_rules.push_back(Rule('F', "F+F-F-F+F"));
    lsystems.push_back(LSystem("Koch Curve", koch_rules, "F", Pi / 2.0, 4, 10, 0, 0));

    vector<Rule> plant_rules;
    plant_rules.push_back(Rule('F', "C0FF-[C1-F+F+F]+[C2+F-F-F]"));
    lsystems.push_back(LSystem("Fractal Plant", plant_rules, "F", toRadians(22), 4, 10, 0, 0));

    vector<Rule> sierpinski_rules;
    sierpinski_rules.push_back(Rule('F', "F-G+F+G-F"));
    sierpinski_rules.push_back(Rule('G', "GG"));
    lsystems.push_back(LSystem("Sierpinski Triangle", sierpinski_rules, "F-G-G", toRadians(120), 6, 10, 0, 0));

    vector<Rule> screen_filling_curve_rules;
    screen_filling_curve_rules.push_back(Rule('X', "-YF+XFX+FY-"));
    screen_filling_curve_rules.push_back(Rule('Y', "+XF-YFY-FX+"));
    lsystems.push_back(LSystem("Screen Filling Curve", screen_filling_curve_rules, "X", toRadians(90), 6, 10, 0, 0));

	vector<Rule> stochastic_plant_rules;
	stochastic_plant_rules.push_back(Rule('F', "F[+F]F[-F]F", 1.0 / 3.0));
	stochastic_plant_rules.push_back(Rule('F', "F[+F]F", 1.0 / 3.0));
	stochastic_plant_rules.push_back(Rule('F', "F[-F]F", 1.0 / 3.0));
	lsystems.push_back(LSystem("Stochastic Plant", stochastic_plant_rules, "F", toRadians(27), 6, 10, 0, 0));
}
int calcSize() {
	int vecSize = sizeof(sf::Vertex);
	int size = 0;
	for(auto it = drawings.begin(); it != drawings.end(); ++it) {
		sf::VertexArray v = it->getVertices();
		for(int i = 0; i < v.getVertexCount(); ++i) {
			size += sizeof(v[i]);
		}
	}
	return size;
}

void redraw(int selected) {
	drawings[selected].clear();
	lsystems[selected].draw(drawings[selected]);
	cout << "vecSize = " << calcSize() << endl;
}

void handleKeyboard(sf::Keyboard::Key keycode, sf::View& view) {
	int newIterCount;
	switch(keycode) {
		// W and S cycle through all available L-Systems
	case sf::Keyboard::W:
		selectedLSystem = (selectedLSystem + 1) % NumLSystems;
		break;
	case sf::Keyboard::S:
		selectedLSystem--;
		if(selectedLSystem < 0)
			selectedLSystem = NumLSystems - 1;
		break;
		// O increaases the iteration counter and issues a redraw
	case sf::Keyboard::O:
		newIterCount = lsystems[selectedLSystem].getIterations() - 1;
		// Make sure the iteration count doesn't go below 1
		lsystems[selectedLSystem].setIterations(newIterCount > 0 ? newIterCount : 1);
		redraw(selectedLSystem);
		break;
	// P decreases the iteration counter and issues a redraw as well
	case sf::Keyboard::P:
		newIterCount = lsystems[selectedLSystem].getIterations() + 1;
		lsystems[selectedLSystem].setIterations(newIterCount);
		redraw(selectedLSystem);
		break;
	case sf::Keyboard::G:
		if(grayscale == 0)
			grayscale = 1;
		else
			grayscale = 0;
		break;
	case sf::Keyboard::Up:
		view.move(0, 8.0f);
		break;
	case sf::Keyboard::Down:
		view.move(0, -8.0f);
		break;
	case sf::Keyboard::Left:
		view.move(8.0f, 0);
		break;
	case sf::Keyboard::Right:
		view.move(-8.0f, 0);
		break;
	default:
		break;
	}
}

// Handles inputs from mouse and keyboard
void handleEvents(sf::Event& event, sf::RenderWindow& window, sf::View& view) {
	sf::Vector2i mousePos;
	int mouseWheel = 0;
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
			sf::Vector2f delta(oldMousePos.x - pos.x, oldMousePos.y - pos.y);
			delta *= scale;
			oldMousePos = pos;
			view.move(delta); 
		}
		break;
	case sf::Event::KeyPressed:
		handleKeyboard(event.key.code, view);
		break;
	// Mouse wheel is used for zooming in and out
	case sf::Event::MouseWheelMoved:
		mouseWheel = event.mouseWheel.delta;
		mousePos = sf::Mouse::getPosition(window);
		// -1 delta means scrolling upwards = zooming in
		if(mouseWheel == -1) {
			view.zoom(ZoomInFactor);
			scale *= ZoomInFactor;
		}
		// 1 delta is scrolling downwards = zooming out
		if(mouseWheel == 1) {
			view.zoom(ZoomOutFactor);
			scale *= ZoomOutFactor;
		}
		break;
	default:
		break;
	}
}

int main() {
	createLSystems();
	sf::RenderWindow window(sf::VideoMode(xSize, ySize), "Window");
	window.setFramerateLimit(60);
	sf::View fixed = window.getView();
	sf::View standard(fixed.getCenter(), fixed.getSize());
	standard.setCenter(xSize / 2.0f, ySize / 2.0f);

	// Build vector of VertexArrays that hold the vertices for every L-System
	for(unsigned int i = 0; i < lsystems.size(); i++) {
		//verts.push_back(lsystems[i].draw());
		drawings.push_back(TurtleDrawing(0, 0));
		lsystems[i].draw(drawings[i]);
	}
	// Load shader.
	sf::Shader shader;
	if(sf::Shader::isAvailable()) {
		if(!shader.loadFromFile("vertex_shader.glsl", "fragment_shader.glsl")) {
			perror("Error loading shader!");
			return EXIT_FAILURE;
		}
		sf::Shader::bind(&shader);
	}

	// Load font
	sf::Font arial;
#ifdef WIN32
	if(!arial.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf")) {
		perror("Error loading the font: ");
		return EXIT_FAILURE;
	}
#else
	if(!arial.loadFromFile("/usr/share/fonts/truetype/freefont/FreeSans.ttf")) {
		perror("Error loading the font: ");
		return EXIT_FAILURE;
	}
#endif
	const float textHeight = 30.0f;
	const float offset = 20.0f;
	sf::Text lSystemName(lsystems[selectedLSystem].getName(), arial, (unsigned int) textHeight);
	float textWidth = lSystemName.getGlobalBounds().width;
	lSystemName.setPosition(xSize - textWidth - offset, ySize - (textHeight + offset));
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			handleEvents(event, window, standard);
		}
		lSystemName.setString(lsystems[selectedLSystem].getName());
		textWidth = lSystemName.getGlobalBounds().width;
		lSystemName.setPosition(xSize - textWidth - offset, ySize - (textHeight + offset));
		window.clear();
		shader.setParameter("grayscale", grayscale);
		window.draw(drawings[selectedLSystem].getVertices(), &shader);
		window.draw(lSystemName);
		window.setView(standard);
		window.display();
	}
	return EXIT_SUCCESS;
}