#include <iostream>
#include <string>

using namespace std;

int main() {

	string s;

	while(1) {
		getline(cin, s, '\n');
		if (cin.eof()) break;
		cout << s << endl;
	}

	return 0;
}
