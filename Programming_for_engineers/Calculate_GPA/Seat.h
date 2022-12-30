#pragma once
#include <iostream>

using namespace std;

class Seat {
private:
	int x;
	int y;

public:
	void setx(int x);
	void sety(int y);
	int getx();
	int gety();
};