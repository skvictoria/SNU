#pragma once
#ifndef POINT2D_HPP
#define POINT2D_HPP

// You'll need to turn this into a class.
// Make sure you use the concept of encapsulation,
// and hide the class's internal data.
class Point2D {
private:
	float x;
	float y;
public:
	Point2D();
	Point2D(float, float);

	float get_x();
	float get_y();
	void set_x(float f);
	void set_y(float f);
};

// lhs = "left hand side"
// rhs = "right hand side"
Point2D operator+(Point2D lhs, Point2D rhs);
Point2D operator-(Point2D lhs, Point2D rhs);
Point2D operator*(Point2D lhs, Point2D rhs);
Point2D operator/(Point2D lhs, Point2D rhs);

#endif // POINT2D_HPP
