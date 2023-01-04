const int C1 = 2;
const int D = 3;
const int E = 4;
const int F = 5;
const int G = 6;
const int A = 7;
const int B = 8;
const int C2 = 9;

void setup() {
  Serial.begin(115200);
  pinMode(C1, INPUT);
  pinMode(D, INPUT);
  pinMode(E, INPUT);
  pinMode(F, INPUT);
  pinMode(G, INPUT);
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(C2, INPUT);
}

void loop() {
  int C1State = digitalRead(C1);
  int DState = digitalRead(D);
  int EState = digitalRead(E);
  int FState = digitalRead(F);
  int GState = digitalRead(G);
  int AState = digitalRead(A);
  int BState = digitalRead(B);
  int C2State = digitalRead(C2);

  if (C1State == HIGH) {
    Serial.println("0");
    delay(100);
  } else if (DState == HIGH) {
    Serial.println("1");
    delay(100);
  } else if (EState == HIGH) {
    Serial.println("2");
    delay(100);
  } else if (FState) {
    Serial.println("3");
    delay(100);
  } else if (GState) {
    Serial.println("4");
    delay(100);
  } else if (AState) {
    Serial.println("5");
    delay(100);
  } else if (BState) {
    Serial.println("6");
    delay(100);
  } else if (C2State) {
    Serial.println("7");
    delay(100);
  } else {
    delay(100);
  }
}
