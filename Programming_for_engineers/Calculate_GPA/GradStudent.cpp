#include "GradStudent.h"

bool GradStudent::getisOnProbation()
{
	return isOnProbation;
}

void GradStudent::setisOnProbation(float gpa)
{
	if (gpa >= 3.0) {
		isOnProbation = true;
	}
	else { isOnProbation = false; }
}

