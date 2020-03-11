#include <iostream>

using namespace std;

///////////////////메모이제이션//////////////////

int min(int a, int b) {
	if (a <= b) {
		return a;
	}
	else return b;
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int x;
	cin >> x;

	//DP table 생성
	int* arr = new int[sizeof(int)*x];
	arr[1] = 0;
	//DP[i-1]+1, DP[i/2]+1, DP[i/3]+1 중 최소값을 DP[i]에 대입
	for (int i = 2; i <= x; ++i) {
		arr[i] = arr[i - 1] + 1;
		if (i % 2 ==0) {
			arr[i] = min(arr[i / 2] + 1, arr[i]);
		}
		if (i % 3==0) {
			arr[i] = min(arr[i / 3] + 1, arr[i]);
		}
	}
	//결국 DP[N] 값을 알아냄
	cout << arr[x];

	return 0;
}
