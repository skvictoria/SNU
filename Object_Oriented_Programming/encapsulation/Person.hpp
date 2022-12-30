#pragma once
#pragma once
#ifndef PERSON_HPP
#define PERSON_HPP

#include "Point2d.hpp"

// std::string is a class from the C++ standard
// library that can be default-constructed
// and constructed from a C-style string (string
// literal like "Hello world")
#include <string>

using namespace std;

// Make sure to use both Point2D and std::string
// as member variables in the class below.
class Person {
private:
	string name;
	Point2D point2d;

	//Point2D location(float, float);
public:
	Person();
	Person(string, Point2D point2d);

	string get_name();
	void set_name(string);
	Point2D get_location();
	void set_location(Point2D point2d);

};

#endif // PERSON_HPP
