#include <iostream>

using namespace std;

class Student {

protected:
	string name;
	int ID;
	float GPA;
	Seat seat;

public:
	Student();
	Student(string name, int id, float gpa, Seat seat);

	void DisplayInfo();
	void setGPA(float gpa);
	float getGPA();

	Student& operator-(Student& rhs);
};
