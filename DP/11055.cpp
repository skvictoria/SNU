#include <iostream>
//#include <vector>
//#include <utility>
#include <algorithm>

using namespace std;

int main() {
	int num;
	int sum = 0;
	int flag = false;
	int temp;

	cin >> num;
	int v[1001];
	int res[1001];
	//vector <int> res;
	//vector <pair<int,int>> res;
	

	for (int i = 0; i < num; i++) {
		cin >> v[i];
	}
	res[0] = v[0];
	temp = res[0];
	
	if (num > 1) {
		if (v[0] > v[1]) {
			res[1] = v[1];
		}
		else {
			res[1] = v[0] + v[1];
			temp = res[1];
		}
	}
	
	if (num > 2) {
		
		for (int i = 2; i < num; i++) {
			for (int j = 0; j < i; j++) {

				if (v[j] < v[i]) {
					sum = max(sum, res[j]+v[i]);
					flag = true;
				}
			}
			if(!flag) res[i] = v[i];
			else res[i] = sum;
			temp = max(res[i], temp);
			sum = 0;
			flag = false;
		}
	}
	cout << temp;
	return 0;
}
