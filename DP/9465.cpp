#include <iostream>

using namespace std;

int max(int a, int b) {
	if (a < b) return b;
	else return a;
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int num, nums;
	int arr[2][100001] = { 0 };
	cin >> nums;

	for (int i = 0;i < nums;++i) {
		cin >> num;
		
		for (int j = 1;j <= num;++j) {
			cin >> arr[0][j];
		}
		for (int j = 1;j <= num;++j) {
			cin >> arr[1][j];
		}
		for (int j = 2;j <= num;++j) {
			arr[0][j] = max(arr[1][j-2]+arr[0][j], arr[1][j-1]+arr[0][j]);

			arr[1][j] = max(arr[0][j - 2] + arr[1][j], arr[0][j - 1] + arr[1][j]);
		}
		cout << max(arr[0][num], arr[1][num])<<'\n';
	}

	

	return 0;
}
