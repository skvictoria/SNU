#include <iostream>

using namespace std;
int arr[10001] = { -1 };
int brr[10001] = { -1 };

int max(int a, int b) {
	return a > b ? a : b;
}

int SOL(int n) {
	if (n == 1) brr[1]= arr[1];
	if (n == 2) brr[2]= arr[1] + arr[2];
	if (n == 3) brr[3]= max(SOL(n - 1), SOL(n - 2) + arr[n]);
	if (brr[n] >= 0) return brr[n];
	else {
		brr[n]= max(max(SOL(n - 1), SOL(n - 3) + arr[n - 1] + arr[n]), SOL(n - 2) + arr[n]);
		return brr[n];
	}
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int num, num1;
	cin >> num;
	
	for (int i = 1; i <= num; ++i) {
		cin >> num1;
		arr[i] = num1;
	}
	
	cout << SOL(num);

	return 0;
}
