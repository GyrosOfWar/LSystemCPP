#pragma once

#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <stack>
#include <iostream>

class TurtleDrawing { 
	sf::Vector2f position;
	double angle;
	sf::VertexArray points;
	std::stack<double> stack;
	sf::Color drawColor;
public:
	explicit TurtleDrawing(int startX, int startY);
	TurtleDrawing();

	void forward(float distance);
	void anglePlus(double);
	void angleMinus(double);
	void moveTo(float, float);
	void pushStack();
	void popStack();

	sf::VertexArray getVertices();
	sf::Vector2f getPosition();
	double getAngle();
	void setAngle(double d);
	void clear();
	void setColor(sf::Color);
};