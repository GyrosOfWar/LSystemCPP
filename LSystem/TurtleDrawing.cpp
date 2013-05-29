#include "stdafx.h"
#include "TurtleDrawing.h"

using std::cout;

TurtleDrawing::TurtleDrawing(int xs, int ys): xSize(xs), ySize(ys) {
	position = sf::Vector2f(0, 0);
	angle = 0.0;
	points = sf::VertexArray(sf::PrimitiveType::Lines);
	drawColor = sf::Color(255, 255, 255, 255);
}

TurtleDrawing::TurtleDrawing() {
	xSize = 800;
	ySize = 600;
	position = sf::Vector2f(0, 0);
	angle = 0.0;
	points = sf::VertexArray(sf::PrimitiveType::Lines);
	drawColor = sf::Color(255, 255, 255, 255);
}

TurtleDrawing::TurtleDrawing(int xSize, int ySize, int startX, int startY): xSize(xSize), ySize(ySize) {
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
	position = sf::Vector2f(0, 0);
	points.clear();
}

void TurtleDrawing::setColor(sf::Color color) {
	drawColor = color;
}