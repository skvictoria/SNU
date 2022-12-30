#include <string>

#include "Person.hpp"
#include <cassert>

bool operator==(Point2D lhs, Point2D rhs) {
	return lhs.get_x() == rhs.get_x() &&
		lhs.get_y() == rhs.get_y();
}

bool operator!=(Point2D lhs, Point2D rhs) {
	return !operator==(lhs, rhs);
}

int main() {
	// Test: Default constructor
	{
		Person p;
		Point2D location = p.get_location();
		assert(location.get_x() == Point2D().get_x());
		assert(location.get_y() == Point2D().get_y());
		assert(p.get_name() == std::string());
	}

	// Test: setters
	{
		Person p;
		p.set_name(std::string("Jerry"));
		p.set_location(Point2D(3.0, 3.14));
		assert(p.get_name() == std::string("Jerry"));
		assert(p.get_location() == Point2D(3.0, 3.14));
	}
}
