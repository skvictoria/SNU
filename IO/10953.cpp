#include <iostream>
#include <string> //getline()

using namespace std;

int main() {

	int num;
	string num1, num2;
	cin >> num;

	for (int i = 0; i < num; ++i) {
		getline(cin,num1, ','); // '': char &delim 이기 때문
    getline(cin, num2);
    cout<<stoi(num1)+stoi(num2)<<endl;
  }

	return 0;
}

///////////////TODO/////////////////////
/*이외에도 char*, strtok_s 사용해서 구현*/
////////////////////////////////////////

////////////////비슷하게 string으로 구현//////////////////
/*
#include <iostream>
#include <string>
using namespace std;
 
int main(int argc, char *argv[]) 
{
	int n;
	int a, b;
	string s;
 
	cin >> n;
 
	for (int i = 0; i < n; ++i) {
		cin >> s;
 
		a = s[0] - '0';
		b = s[2] - '0';
 
		cout << a + b << endl;
	}
 
	return 0;
}
*/
///////////////////////////////////////////////////////////////
