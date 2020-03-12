#include <iostream>

using namespace std;

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int num;
	long long sum;
	cin >> num;

	long long arr[91][2] = { 0 };
	arr[1][0] = 0;
	arr[1][1] = 1;

	for (int i = 2;i <= num;++i) {
		arr[i][0] = arr[i - 1][0]+arr[i-1][1];
		arr[i][1] = arr[i - 1][0];
	}
	sum = arr[num][0] + arr[num][1];
	
	cout << sum;

	return 0;
}
