#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int num;
	int flag = 0;
	cin >> num;

	for (int i = 1;i < num; ++i) {
		for (int j = num;j > i;--j) {
			cout << " ";
		}
		cout << "*";
		for (int j = 1;j < 2*(i-1);++j) {
			cout << " ";
			flag = 1;
		}
		if (flag) {
			cout << "*";
		}
		
		cout << '\n';
	}
	for (int i = 1; i <= 2 * num - 1;++i) {
		cout << "*";
	}
	return 0;
}
