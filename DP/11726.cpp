#include <iostream>

using namespace std;

//also use memoization

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	int arr[1001];
	arr[1] = 1;
	arr[2] = 2;

	for (int i = 3;i <= n;++i) {
		arr[n] = (arr[n - 1] + arr[n - 2])%10007;
	}

	cout << arr[n];

	return 0;
}
