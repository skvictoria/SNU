#include <iostream>
#define ODD(x) (x==1)||(x==3)||(x==5)||(x==7)||(x==8)||(x==10)||(x==12)
#define EVEN(x) (x==4)||(x==6)||(x==9)||(x==11)

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int num1, num2;
	int sum = 0;
	cin >> num1>>num2;

	for (int i = 1; i < num1; ++i) {
		if (ODD(i)) {
			sum += 31;
		}
		else if (EVEN(i)) {
			sum += 30;
		}
		else {
			sum += 28;
		}
	}
	sum += num2;
	
	switch (sum % 7) {
	case 1:
		cout << "MON" << '\n';
		break;
	case 2:
		cout << "TUE" << '\n';
		break;
	case 3:
		cout << "WED" << '\n';
		break;
	case 4:
		cout << "THU" << '\n';
		break;
	case 5:
		cout << "FRI" << '\n';
		break;
	case 6:
		cout << "SAT" << '\n';
		break;
	case 0:
		cout << "SUN" << '\n';
		break;
	}

	return 0;
}
