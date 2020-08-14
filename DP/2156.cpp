#include <iostream>
#include <algorithm>

using namespace std;

int arr[10001] = { -1 };
int dp[10001] = { -1 };

int detminmax(int a, int b, int c) {
	return max(max(a, b), c);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int num;
	cin >> num;	
	for (int i = 0; i < num; i++) {
		cin >> arr[i];
	}
	dp[0] = arr[0];
	dp[1] = arr[0] + arr[1];
	
	for (int i = 2; i < num; i++) {
		if (i == 2) dp[2] = detminmax(arr[0] + arr[1], arr[1] + arr[2], arr[0] + arr[2]);
		else dp[i] = detminmax(dp[i - 1], dp[i - 2] + arr[i], dp[i-3]+arr[i-1]+arr[i]);
		
	}

	
	cout << dp[num-1];
	
	
}
