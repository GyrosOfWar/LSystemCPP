#include "stdafx.h"
#include "TurtleDrawing.h"

using std::cout;

TurtleDrawing::TurtleDrawing() {
	position = sf::Vector2f(0, 0);
	angle = 0.0;
	points = sf::VertexArray(sf::PrimitiveType::Lines);
	drawColor = sf::Color(255, 255, 255, 255);
}

TurtleDrawing::TurtleDrawing(int startX, int startY) {
	position = sf::Vector2f(startX, startY);
	angle = 0.0;
	points = sf::VertexArray(sf::PrimitiveType::Lines);
	drawColor = sf::Color(255, 255, 255, 255);
}

void TurtleDrawing::forward(float distance) {
	sf::Vertex oldPos(position, drawColor);
	points.append(oldPos);
	position.x += (cos(angle) * distance);
	position.y += (sin(angle) * distance);
	sf::Vertex newPos(position, drawColor);
	points.append(newPos);
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

// Pushes the current position and angle to the stack
void TurtleDrawing::pushStack() {
	stack.push(angle);
	stack.push(position.x);
	stack.push(position.y);
}

void TurtleDrawing::popStack() { 
	float y = (float) stack.top();
	stack.pop();	
	float x = (float) stack.top();
	stack.pop();
	float angle = stack.top();
	stack.pop();
	moveTo(x, y);
	setAngle(angle);
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
	position = sf::Vector2f(0, 0);
	points.clear();
}

void TurtleDrawing::setColor(sf::Color color) {
	drawColor = color;
}