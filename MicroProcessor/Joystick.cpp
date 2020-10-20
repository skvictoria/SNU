const int SW_pin=2;
const int X_pin =0;
const int Y_pin=1;

void setup() {
  // put your setup code here, to run once:

  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Switch: ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis : ");
  Serial.print(analogRead(Y_pin));
  Serial.print("\n\n");
  delay(500);
}
