#include <iostream>

using namespace std;
int arr[1001];

int SOL(int n) {
	if (n == 1) arr[1] = 1;
	else if (n == 2) arr[2] = 2;
	else if (n == 3) arr[3] = 4;
	if (arr[n] > 0) return arr[n];
	if (n > 3) {
		arr[n] = SOL(n-3) + SOL(n-2)+SOL(n-1);
		return arr[n];
	}
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int num, n;
	cin >> num;

	for (int i = 0; i < num; ++i) {
		cin >> n;
		cout << SOL(n)<<'\n';
	}

	return 0;
}
