#include <iostream>
#include "Seat.h"
#include "Student.h"

using namespace std;

int main() {

	string str1 = "girl";
	string str2 = "boy";
	string str3 = "boygirl";

	Seat s11;
	s11.setx(4);
	s11.sety(5);

	Seat s22;
	s22.setx(6);
	s22.sety(7);

	Seat s33;
	s33.setx(1);
	s33.sety(1);

	/*  GPA >4를 컴파일러에서 못 거르므로 엉뚱한 값을 넣어서 프로그램에서 차단!
	Student s1(str1,2,3.0,s11);
	Student s2(str2,3,2.9,s22);
	Student s3(str3,4,2.8,s33);
	*/
	Student s1(str1, 2, 3.0f, s11);
	if (s1.getGPA() < 0) { cout << "Fatal Error, GPA greater than 4 or negative" << endl; return -1; }
	Student s2(str2, 3, 3.9f, s22);
	if (s2.getGPA() < 0) { cout << "Fatal Error, GPA greater than 4 or negative" << endl; return -1; }
	Student s3(str3, 4, 2.8f, s33);
	if (s3.getGPA() < 0) { cout << "Fatal Error, GPA greater than 4 or negative" << endl; return -1; }



	s3 = s2 - s1;
	s3.DisplayInfo();

	return 0;
}
