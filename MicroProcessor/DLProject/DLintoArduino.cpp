#include <SoftwareSerial.h>
#include <AFMotor.h>
#include "math.h"
AF_DCMotor motor_L(2);              // 모터드라이버 L293D  2: M2에 연결,  3: M3에 연결
AF_DCMotor motor_R(3);
double dtime, otime, itime, stime, etime, ttime;
int preval = 0;
int val4 = 1;
int ans;
double tbouf[2];
int tindex = 0;
int flag = 0;
int incomingByte = 0;

double syn01[2][5] = {{1.30740228,  3.40017524, -1.70960076,  2.13129613, -3.73812376},
  { -1.41342062, -2.56871706,  1.59206523, -1.83377314,  2.77514738}
};
double syn11[5][1] = {{ 2.58099665},
  { 5.04310513},
  { -2.24152117},
  { 3.76940551},
  { -5.17743616}
};

double syn02[2][5] = {{7.77234921,  3.8776977,   0.64591663,  1.60161367, -8.59730833},
  { -5.68319677, -1.42479603, -1.77629501 , -0.53125531,  3.34903694}
};
double syn12[5][1] = {{ -10.77010577},
  {  4.32509707},
  { -2.29268377},
  {  2.92713347},
  { -8.05645377}
};

double syn03[2][5] = {{3.08310038 , 3.63921762 , 0.9956962 , -4.35989383,  3.12402668},
  { -1.58543688 , -1.77036677 , -1.00240977,  2.02148986, -1.59901793}
};
double syn13[5][1] = {{ -4.03322744},
  { -4.41485436},
  { -2.58205516},
  { 6.82119589},
  { -4.37191662}
};
double res[5] = {0};
double res1, res2, res3;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);              // PC와의 시리얼 통신속도
  Serial.println("Eduino Smart Car Start!");

  motor_L.setSpeed(170);              // 왼쪽 모터의 속도
  motor_L.run(RELEASE);
  motor_R.setSpeed(170);              // 오른쪽 모터의 속도
  motor_R.run(RELEASE);
}

void loop() {
  stime = micros();
  int val1 = digitalRead(A0);    // 라인센서1
  int val2 = digitalRead(A5);    // 라인센서2
  //int val3 = digitalRead(A1);    // sensor 1
  val4 = digitalRead(A4);    // sensor 2

  if (flag) {
    if (val1 == 0 && val2 == 0) {                   // 직진
      motor_L.run(FORWARD);
      motor_R.run(BACKWARD);
    }
    else if (val1 == 0 && val2 == 1) {              // 우회전
      motor_L.run(FORWARD);
      motor_R.run(RELEASE);
    }
    else if (val1 == 1 && val2 == 0) {              // 좌회전
      motor_L.run(RELEASE);
      motor_R.run(BACKWARD);
    }
    else {             // 정지
      motor_L.run(RELEASE);
      motor_R.run(RELEASE);
    }


    if (preval != val4) { //바뀔 때
      if (val4 == 1) {
        itime = micros();
      }
      if (val4 == 0) { //0으로 바뀔 때 계산한다.
        otime = micros();
        dtime = otime - itime;
        tbouf[tindex] = dtime;
        if (tindex == 1) {
          //Serial.println(tbouf[0]);
          //Serial.println(tbouf[1]);
          tbouf[1] = tbouf[1] * 1.375 / tbouf[0];
          tbouf[0] = 1.375;
          for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 2; j++) {
              res[i] += tbouf[j] * syn01[j][i];
            }
            res[i] = 1 / (1 + exp(-res[i]));
          }
          for (int i = 0; i < 5; i++) {
            res1 += res[i] * syn11[i][0];
          }
          res1 = 1 / (1 + exp(-res1));

          for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 2; j++) {
              res[i] += tbouf[j] * syn02[j][i];
            }
            res[i] = 1 / (1 + exp(-res[i]));
          }
          for (int i = 0; i < 5; i++) {
            res2 += res[i] * syn12[i][0];
          }
          res2 = 1 / (1 + exp(-res2));

          for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 2; j++) {
              res[i] += tbouf[j] * syn03[j][i];
            }
            res[i] = 1 / (1 + exp(-res[i]));
          }
          for (int i = 0; i < 5; i++) {
            res3 += res[i] * syn13[i][0];
          }
          res3 = 1 / (1 + exp(-res3));
          /*
            Serial.print("res1 : ");
            Serial.println(res1);
            Serial.print("res2 : ");
            Serial.println(res2);
            Serial.print("res3 : ");
            Serial.println(res3);
          */
          if (res1 > res2) {
            if (res1 > res3) {
              ans = 5513;
              flag = 0;
            }
            else {
              ans = 5515;

            }
          } else {
            if (res2 > res3) {
              ans = 5511;
            } else {
              ans = 5515;

            }
          }
          Serial.print("now : ");
          Serial.print(ans);
          Serial.println(" Bus Stop");
        }
        tindex++;
        if (tindex >= 2) {
          tindex = 0;
        }
      }
    }
  }
  else if (flag == 0) {
    motor_L.run(RELEASE);   //정지
    motor_R.run(RELEASE);
  }
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    if (incomingByte == 100) {
      motor_L.run(RELEASE);   //정지
      motor_R.run(RELEASE);
      Serial.println("stop!");
      flag = 0;
    }
    if (incomingByte == 103) {
      Serial.println("go!");
      flag = 1;
      tindex = 0;
    }
  }
  preval = val4;
  etime = micros();
  ttime = etime - stime;
  if (ttime > 1000000) {
    tindex = 0;
  }
}
