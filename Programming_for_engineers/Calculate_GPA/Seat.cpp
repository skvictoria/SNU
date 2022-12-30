#include "Seat.h"

void Seat::setx(int x)
{
	if (x >= 1)	this->x = x;
}

void Seat::sety(int y)
{
	if (y >= 1) this->y = y;
}

int Seat::getx()
{
	return x;
}

int Seat::gety()
{
	return y;
}