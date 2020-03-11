#include <iostream>

using namespace std;
int arr[101];

int SOL(int n) {
	if (n == 1) arr[1] = 9;
	if (arr[n] > 0) return arr[n];
	if (n > 1) {
		arr[n] = (2*SOL(n-1)-1)% 1000000000;
		return arr[n];
	}
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int num;
	cin >> num;

	cout << SOL(num);

	return 0;
}
