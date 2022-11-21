#define A  2
#define B  3
#define C  4
#define D  5
#define E  6
#define F  7
#define G  8
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
  pinMode(DP, OUTPUT);
}

void led_on(int number){
  if (number == 0){
    digitalWrite(A, HIGH); 
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, LOW);
    digitalWrite(DP, LOW);
  }else if(number == 1){
    digitalWrite(A, LOW); 
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
    digitalWrite(DP, LOW);
  }else if(number == 2){
    digitalWrite(A, HIGH); 
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, LOW);
    digitalWrite(G, HIGH);
    digitalWrite(DP, LOW);
  }else if(number == 3){
    digitalWrite(A, HIGH); 
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, HIGH);
    digitalWrite(DP, LOW);
  }else if(number == 4){
    digitalWrite(A, LOW); 
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
    digitalWrite(DP, LOW);
  }else if(number == 5){
    digitalWrite(A, HIGH); 
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, LOW);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
    digitalWrite(DP, LOW);
  }else if(number == 6){
    digitalWrite(A, HIGH); 
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
    digitalWrite(DP, HIGH);
  }else if(number == 7){
    digitalWrite(A, HIGH); 
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
    digitalWrite(DP, LOW);
  }else if(number == 8){
    digitalWrite(A, HIGH); 
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
    digitalWrite(DP, LOW);
  }else if(number == 9){
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

void led_off(){
  digitalWrite(A, LOW); 
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(DP, LOW);
}

int k = 0;
void loop() {
  delay(100);
  k = Serial.available();
  if (k > 0){
    char *numbers = new char[k];
    for(int i = 0; i < k; i++){
      numbers[i] = Serial.read();
      delay(100);
    }
    for(int i = 0; i < k; i++){
      Serial.println(numbers[i] - '0');
    }
    if (k == 1){
      mySerial.write(numbers[0]);
      led_on(0);
    }
    else if (k == 2){
      mySerial.write(numbers[1]);
      led_on(numbers[0] - '0');
    }
    else{
      while(true){
        for(int i = 0; i <= k + 1; i++){
          if (i == 0){
            mySerial.write(numbers[i]);
            led_off();
          }
          else if(i == k){
            mySerial.write('-');
            led_on(numbers[i-1] - '0');
          }
          else if(i == k+1){
            mySerial.write('-');
            led_off();
          }
          else{
            mySerial.write(numbers[i]);
            led_on(numbers[i-1] - '0');
          }
          delay(500);
        }
      }
    }
  }
}
