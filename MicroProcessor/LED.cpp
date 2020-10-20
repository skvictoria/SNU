int led1_Pin=1;
int led2_Pin=2;
int led3_Pin=3;
int button1_Pin=8;
int button2_Pin=9;
int button3_Pin=10;

void setup() {
  pinMode(led1_Pin, OUTPUT);
  pinMode(led2_Pin, OUTPUT);
  pinMode(led3_Pin, OUTPUT);
  pinMode(button1_Pin, INPUT);
  pinMode(button2_Pin, INPUT);
  pinMode(button3_Pin, INPUT);
}

void loop() {
  if(digitalRead(button3_Pin)==LOW){
    digitalWrite(led3_Pin, HIGH);
  }
  else{
    if(digitalRead(button1_Pin)==LOW){
    digitalWrite(led1_Pin, HIGH);
    }
    else digitalWrite(led1_Pin, LOW);

    if(digitalRead(button2_Pin)==LOW){
      digitalWrite(led2_Pin, HIGH);
    }
    else digitalWrite(led2_Pin, LOW);
  }
}
