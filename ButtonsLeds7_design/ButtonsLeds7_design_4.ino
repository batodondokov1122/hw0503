#define A  4
#define B  5
#define C  8
#define D  7
#define E  6
#define F  3
#define G  2
#define DP 9
int sensorPin = A3;
int sensorValue = 0;
int treshold = 0;
int num = 0;
int min = 1023;
int max = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  while(millis() < 10000){
    digitalWrite(A, LOW); 
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
    int val = analogRead(sensorPin);
    if (val < min){
      min = val;
    }
    if (val > max){
      max = val;
    }
    treshold = min + (max-min)/2;
  }
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if (sensorValue < treshold){
    if (num == 0){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      num++;
      delay(3000);
    }else if(num == 1){
      digitalWrite(A, LOW); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      num++;
      delay(3000);
    }else if(num == 2){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      num++;
      delay(3000);
    }else if(num == 3){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      num++;
      delay(3000);
    }else if(num == 4){
      digitalWrite(A, LOW); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      num++;
      delay(3000);
    }else if(num == 5){
      digitalWrite(A, HIGH); 
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      num++;
      delay(3000);
    }else if(num == 6){
      digitalWrite(A, HIGH); 
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, HIGH);
      num++;
      delay(3000);
    }else if(num == 7){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      num++;
      delay(3000);
    }else if(num == 8){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      num++;
      delay(3000);
    }else if(num == 9){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, HIGH);
      num=0;
      delay(3000);
    }
  }else{
    digitalWrite(A, LOW); 
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
    digitalWrite(DP, LOW);
    num = 0;
  }
}
