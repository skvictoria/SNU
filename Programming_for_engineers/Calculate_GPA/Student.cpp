#include "Student.h"
#include "Seat.h"

Student::Student() {
	name = ' ';
	ID = 0;
	GPA = 0;
	seat.setx(1);
	seat.sety(1);
}

Student::Student(string name, int id, float gpa, Seat seat1) {
	/* 컴파일러에서 차단할 수 없으므로, 전혀 엉뚱한 값을 넣어 걸러주는 수 밖에!!
	*/
	if (gpa > 4.0f) {
		this->name = "";
		this->ID = -99;
		this->GPA = -99;
		this->seat.setx(0);
		this->seat.sety(0);
	}
	else {
		this->name = name;
		this->ID = id;
		this->GPA = gpa;
		this->seat.setx(seat1.getx());
		this->seat.sety(seat1.gety());
	}

}

void Student::DisplayInfo() {
	cout << "student name : " << name.c_str() << endl;
	cout << "ID number : " << ID << endl;
	cout << "GPA : " << GPA << endl;
	cout << "current location : " << "Seat" << seat.getx() << seat.gety() << endl;
}

void Student::setGPA(float gpa) {
	/*  0 <gpa<4   --- 이런건 없는데???  아래 처럼 && 연산 해야 함!
	if (0 < gpa < 4) {
		GPA = gpa;
	}
	*/
	if (0 < gpa && gpa < 4) {
		GPA = gpa;
	}
	else {
		GPA = -99;
	}
}

float Student::getGPA() {
	return GPA;
}

Student& Student:: operator-(Student& rhs) {
	Student* student = new Student();
	student->seat.setx(this->seat.getx() - rhs.seat.getx());
	student->seat.sety(this->seat.gety() - rhs.seat.gety());

	return *student;
}
