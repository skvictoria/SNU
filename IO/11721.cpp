#include <iostream>
#include <string>

using namespace std;

int main() {

	string s;
	cin >> s;

	for (int i = 0;i < s.length()/10; ++i) {
		cout<<s.substr(i*10, 10)<<endl;
	}

	cout << s.substr((s.length()/10)*10, s.length()) << endl;

	return 0;
}
