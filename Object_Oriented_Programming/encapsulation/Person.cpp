#include <iostream>
#include "Point2D.hpp"
#include "Person.hpp"


Person::Person() {
	name = "";
	point2d.set_x(0);
	point2d.set_y(0);
}
Person::Person(string n, Point2D p) {
	name = n;
	point2d = p;
}
string Person::get_name() {
	return this->name;
}
void Person::set_name(string name) {
	this->name = name;
}
Point2D Person::get_location() {
	return point2d;
}
void Person::set_location(Point2D p) {
	point2d = p;
}
