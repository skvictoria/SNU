#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  double prev[5];
  double vec[5] = {0.2, 0.2, 0.2, 0.2, 0.2};
  
  do{
    for (int i=0;i<5;++i){
      prev[i] = vec[i];
    }
    vec[0] = prev[2] *0.8/3;
    vec[1] = prev[0] * 0.4 + prev[3] * 0.8 + prev[4] * 0.4;
    vec[2] = prev[1] * 0.8;
    vec[3] = prev[2] * 0.8 / 3;
    vec[4] = prev[0] * 0.4 + prev[2] * 0.8 / 3 + prev[4] * 0.4;
    
    for (int i = 0; i < 5; i++) {
      vec[i] += 0.2 / 5;
      vec[i] = round(vec[i] * 100) / 100;
    }
  } while ((prev[1] - vec[1] > 0.01) || (vec[1] - prev[1] > 0.01));

  for (int i = 0; i < 5; i++) {
    cout << "r" << i + 1 << " = " << vec[i] << '\n';
  }
}
