#define A  3
#define B  2
#define C  7
#define D  6
#define E  8
#define F  4
#define G  5
#define DP  9
#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 10); // RX, TX

void setup() {
  Serial.begin(9600);
  while (!Serial) { }
  Serial.println("Enter number");
  mySerial.begin(9600);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
}

void loop() {
  if (Serial.available() == 2){
    int first_num = Serial.read() - '0';
    char second_num = Serial.read();
    Serial.println(first_num);
    Serial.println(second_num);
    mySerial.write(second_num);
    if (first_num == 0){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
    }else if(first_num == 1){
      digitalWrite(A, LOW); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
    }else if(first_num == 2){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
    }else if(first_num == 3){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
    }else if(first_num == 4){
      digitalWrite(A, LOW); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
    }else if(first_num == 5){
      digitalWrite(A, HIGH); 
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
    }else if(first_num == 6){
      digitalWrite(A, HIGH); 
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, HIGH);
    }else if(first_num == 7){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
    }else if(first_num == 8){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
    }else if(first_num == 9){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, HIGH);
    }
  }
  if (Serial.available() == 1){
    char second_num = Serial.read();
    Serial.println(second_num);
    mySerial.write(second_num);
    digitalWrite(A, HIGH); 
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, LOW);
    digitalWrite(DP, LOW);
  }
}