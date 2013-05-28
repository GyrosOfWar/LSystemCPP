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
public:
	TurtleDrawing(int xSize, int ySize, int startX, int startY);
	TurtleDrawing(int xSize, int ySize);
	TurtleDrawing();

	void forward(float distance);
	void anglePlus(double);
	void angleMinus(double);
	void moveTo(float, float);
	void pushStack(double);
	double popStack();

	sf::VertexArray getVertices();
	sf::Vector2f getPosition();
	double getAngle();
	void setAngle(double d);
	void clear();

};