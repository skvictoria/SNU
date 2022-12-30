#include "Point2d.hpp"


Point2D::Point2D() {
	this->x = 0;
	this->y = 0;
}

Point2D::Point2D(float x, float y) {
	this->x = x;
	this->y = y;
}

float Point2D::get_x() {
	return this->x;
}

float Point2D::get_y() {
	return this->y;
}

void Point2D::set_x(float f) {
	this->x = f;
}

void Point2D::set_y(float f) {
	this->y = f;
}
