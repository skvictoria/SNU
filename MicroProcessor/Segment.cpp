/* FND에 표현할 숫자 값을 2진수 배열 형태로 선언 함 */

#define Fnd_a 8   // FND "a" 자리 핀(Pin)
#define Fnd_b 9   // FND "b" 자리 핀(Pin)
#define Fnd_c 2   // FND "c" 자리 핀(Pin)
#define Fnd_d 3   // FND "d" 자리 핀(Pin)
#define Fnd_e 4   // FND "e" 자리 핀(Pin)
#define Fnd_f 6   // FND "f" 자리 핀(Pin)
#define Fnd_g 5   // FND "g" 자리 핀(Pin)

byte seven_seg_digits[10][8] = {
// a, b, c, d, e, f, g, h
{1, 1, 1, 1, 1, 1, 0, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1, 0},  // 2
  {1, 1, 1, 1, 0, 0, 1, 0},  // 3
  {0, 1, 1, 0, 0, 1, 1, 0},  // 4
  {1, 0, 1, 1, 0, 1, 1, 0},  // 5
  {1, 0, 1, 1, 1, 1, 1, 0},  // 6
  {1, 1, 1, 0, 0, 1, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1, 0},  // 8
  {1, 1, 1, 1, 0, 1, 1, 0}  // 9
};

/* 각 핀(Pin) 정의 */

//int Fnd_dot = 8;  // FND "dot" 자리 핀(Pin)

void setup()
{
  pinMode(Fnd_a, OUTPUT);
  pinMode(Fnd_b, OUTPUT);  
  pinMode(Fnd_c, OUTPUT); 
  pinMode(Fnd_d, OUTPUT);  
  pinMode(Fnd_e, OUTPUT);   
  pinMode(Fnd_f, OUTPUT);    
  pinMode(Fnd_g, OUTPUT);  
  //pinMode(Fnd_dot, OUTPUT); 
  //writeDot(0);
}

void writeDot(byte dot)  // 도트(Dot) Led On/Off 함수
{
  //digitalWrite(Fnd_dot, dot);
}

void NumberDisplay(byte num)  // FND 디스플레이 함수
{
  digitalWrite(Fnd_a, seven_seg_digits[num][0]);
  digitalWrite(Fnd_b, seven_seg_digits[num][1]);
  digitalWrite(Fnd_c, seven_seg_digits[num][2]);
  digitalWrite(Fnd_d, seven_seg_digits[num][3]);
  digitalWrite(Fnd_e, seven_seg_digits[num][4]);
  digitalWrite(Fnd_f, seven_seg_digits[num][5]);
  digitalWrite(Fnd_g, seven_seg_digits[num][6]);
}

void loop()
{
  for (int k = 0; k <= 9; k++)
  {
    NumberDisplay(k);
    delay(2000);
  }
  delay(200);
}
