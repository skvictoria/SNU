#pragma once
#include "Student.h"

class GradStudent : Student {
private:
	bool isOnProbation;

public:
	bool getisOnProbation();
	void setisOnProbation(float gpa);

};
