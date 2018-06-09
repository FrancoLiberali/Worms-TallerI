#include "Shape.h"

Shape::Shape(){

}

Shape::Shape(int x, int y,
	int width, int height){
	this->x = x; this->y = y;
	this->width = width;
	this->height = height;
}

Shape::~Shape(){}

std::pair<int, int> Shape::getPosition(){
	return std::pair<int, int>(x, y);
}

std::pair<int, int> Shape::getDimension(){
	return std::pair<int, int>(width, height);
}
