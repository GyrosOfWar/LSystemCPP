#pragma once

#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include <stack>
#include <iostream>

using std::stack;

class TurtleDrawing { 
	sf::Vector2f position;
	int xSize;
	int ySize;
	double angle;
	sf::VertexArray points;
	stack<double> stack;
	sf::Color drawColor;
public:
	explicit TurtleDrawing(int xSize, int ySize, int startX, int startY);
	explicit TurtleDrawing(int xSize, int ySize);
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