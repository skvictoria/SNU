//////////////////////TIL/////////////////////////////////////////////////////////////////////////////////////////////////
//
//1. ios_base::sync_with_stdio(false)
//    -> cout, cin과 stdout, stdin이 사용하는 버퍼를 서로 분리
//    -> 즉, cout이 더이상 stdout (printf, puts 등)에, cin이 더이상 stdin (scanf, gets, fgets, getchar 등)에 종속되지 않음.
//    -> 단, 버퍼가 분리되었으므로 cout<->stdout, cin<->stdin을 혼합해서 사용할 수 없음.
//2. endl vs. '\n'
//    -> endl은 단순 개행이 아니라 개행 후 출력버퍼를 비워서 화면 위에 바로 보여줄 수 있도록 하는 역할(온라인저지에서는 '\n'쓸것)
//3. cin.tie(NULL)
//    -> cin은 cout과 기본적으로 묶여 있는데, 그래서 cin을 하는 순간 cout의 버퍼를 비워줌.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int num;
	cin >> num;

	for (int i = 1;i <= num;++i) {
		cout << i << '\n';
	}

	return 0;
}
