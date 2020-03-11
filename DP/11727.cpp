#include <iostream>

using namespace std;
int arr[1001];

int SOL(int n) {
	if (n==1) arr[1] = 1;
	else if (n == 2) arr[2] = 3;
	if (arr[n] > 0) return arr[n];
	if (n > 2) {
		arr[n] = (SOL(n-1) + 2*SOL(n-2))%10007;
		return arr[n];
	}
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	cout << SOL(n);

	return 0;
}
