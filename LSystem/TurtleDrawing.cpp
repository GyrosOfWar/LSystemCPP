#include "stdafx.h"
#include "TurtleDrawing.h"

using std::cout;

TurtleDrawing::TurtleDrawing(int xs, int ys): xSize(xs), ySize(ys) {
	position = sf::Vector2f(0, 0);
	angle = 0.0;
	points = sf::VertexArray(sf::PrimitiveType::Lines);
}

TurtleDrawing::TurtleDrawing() {
	xSize = 800;
	ySize = 600;
	position = sf::Vector2f(0, 0);
	angle = 0.0;
	points = sf::VertexArray(sf::PrimitiveType::Lines);
}

TurtleDrawing::TurtleDrawing(int xSize, int ySize, int startX, int startY): xSize(xSize), ySize(ySize) {
	position = sf::Vector2f(startX, startY);
	angle = 0.0;
	points = sf::VertexArray(sf::PrimitiveType::Lines);
}

void TurtleDrawing::forward(float distance) {
	points.append(position);
	position.x += (cos(angle) * distance);
	position.y += (sin(angle) * distance);
	points.append(position);
}

void TurtleDrawing::anglePlus(double d) {
	angle += d;
}

void TurtleDrawing::angleMinus(double d) {
	angle -= d;
}

void TurtleDrawing::moveTo(float x, float y) {
	position.x = x;
	position.y = y;
}

void TurtleDrawing::pushStack(double d) {
	stack.push(d);
}

double TurtleDrawing::popStack() { 
	double value = stack.top();
	stack.pop();	
	return value;
}

sf::VertexArray TurtleDrawing::getVertices() {
	return points;
}

sf::Vector2f TurtleDrawing::getPosition() {
	return position;
}

double TurtleDrawing::getAngle() {
	return angle;
}

void TurtleDrawing::setAngle(double d) {
	angle = d;
}

void TurtleDrawing::clear() {
	angle = 0.0;
	stack = std::stack<double>();
	points.clear();
}