#include <stdio.h>
#include <math.h>

double putxy(int x, int y) {
	double cen;
	cen = (3.0 - x) * (3.0 - x) + (2.333 - y)*(2.333 - y);
	
	return sqrt(cen);
}

int main(void){

	double sum = 0;

	int arr[12][2] = {
		{2,2},
	{3,3},
	{4,2},
	{4,9},
	{4,10},
	{6,8},
	{5,11},
	{9,3},
	{10,5},
	{11,4},
	{12,3},
	{12,6}
	};
	for (int i = 0; i < 12; ++i) {
		sum += putxy(arr[i][0], arr[i][1]);
	}
	printf("%f\n",sum);
	return 0;
}
