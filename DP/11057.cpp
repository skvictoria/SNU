#include <iostream>

using namespace std;


int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int num;
	int sum = 0;
	cin >> num;

	int arr[1001][10] = { 0 };
	for (int i = 0;i <= 9;++i) {
		arr[1][i] = 1;
	}
	for (int i = 2;i <= num;++i) {
		for (int j = 0;j <= 9;++j) {
			for (int k = 0;k <= j;++k) {
				arr[i][j] += arr[i-1][k]%10007;
			}
		}
	}
	
	for (int i = 0;i <= 9;++i) {
		sum += arr[num][i];
		sum = sum % 10007;
	}

	cout << sum;

	return 0;
}
