#include <iostream>

using namespace std;

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int num;
	int sum = 0;
	cin >> num;

	int arr[101][10] = { 0 };
	for (int i = 1;i <= 9;++i) {
		arr[1][i] = 1;
	}
	for (int i = 2;i <= num;++i) {
		arr[i][0] = arr[i - 1][1]% 1000000000;
		arr[i][9] = arr[i - 1][8]% 1000000000;
		for (int j = 1;j <= 8;++j) {
			arr[i][j] += arr[i - 1][j - 1];
			arr[i][j] += arr[i - 1][j + 1];
			arr[i][j] = arr[i][j] % 1000000000;
		}
	}
	
	for (int i = 0;i <= 9;++i) {
		sum += arr[num][i];
		sum = sum % 1000000000;
	}

	cout << sum;

	return 0;
}
