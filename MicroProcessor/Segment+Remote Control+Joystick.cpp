/* FND에 표현할 숫자 값을 2진수 배열 형태로 선언 함 */
#include <IRremote.h>

#define Fnd_a 8   // FND "a" 자리 핀(Pin)
#define Fnd_b 9   // FND "b" 자리 핀(Pin)
#define Fnd_c 2   // FND "c" 자리 핀(Pin)
#define Fnd_d 3   // FND "d" 자리 핀(Pin)
#define Fnd_e 4   // FND "e" 자리 핀(Pin)
#define Fnd_f 6   // FND "f" 자리 핀(Pin)
#define Fnd_g 5   // FND "g" 자리 핀(Pin)

const int Y_pin=1;
int temp=5;
int RECV_PIN=10; //IR 수신센서 
IRrecv irrecv(RECV_PIN);
decode_results results;

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
  irrecv.enableIRIn(); //수신센서 감지 시작
  Serial.begin(115200);
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
  NumberDisplay(5);
  if(analogRead(Y_pin) > 520){
    Serial.print("Y pin : ");
    Serial.println(analogRead(Y_pin));
    temp++;
    NumberDisplay(temp);
    delay(3000);
  }
  if(analogRead(Y_pin) < 500){
    Serial.print("Y pin : ");
    Serial.println(analogRead(Y_pin));
    temp--;
    NumberDisplay(temp);
    delay(3000);
  }
  if(irrecv.decode(&results)){
        if(results.decode_type == NEC){
          switch(results.value){
            case 0x00FF6897: // Key 0
                NumberDisplay(0);
                temp = 0;
                delay(2000);
                break;
            case 0x00FF30CF: // Key 1
                NumberDisplay(1);
                temp = 1;
                delay(2000);
                break;
            case 0x00FF18E7: // Key 2
                NumberDisplay(2);
                temp = 2;
                delay(2000);
                break;
            case 0x00FF7A85: // Key 3
                NumberDisplay(3);
                temp = 3;
                delay(2000);
                break;
            case 0x00FF10EF: // Key 4
                NumberDisplay(4);
                temp = 4;
                delay(2000);
                break;
            case 0x00FF38C7: // Key 5
                NumberDisplay(5);
                temp = 5;
                delay(2000);
                break;
            case 0x00FF5AA5: // Key 6
                NumberDisplay(6);
                temp = 6;
                delay(2000);
                break;
            case 0x00FF42BD: // Key 7
                NumberDisplay(7);
                temp = 7;
                delay(2000);
                break;
            case 0x00FF4AB5: // Key 8
                NumberDisplay(8);
                temp = 8;
                delay(2000);
                break;
            case 0x00FF52AD: // Key 9
                NumberDisplay(9);
                temp = 9;
                delay(2000);
                break;
            case 0x00FFA857:
                temp++;
                NumberDisplay(temp);
                delay(2000);
                break;
            case 0x00FFe01F:
                temp--;
                NumberDisplay(temp);
                delay(2000);
                break;
            default:
                break;
          }           
        }
        irrecv.resume();  // 다음 값 수신
  }
  delay(200);
}
