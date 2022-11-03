#define A  4
#define B  5
#define C  8
#define D  7
#define E  6
#define F  3
#define G  2
#define DP  9

void setup() {
  Serial.begin(9600);
  while (!Serial) { }
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
}

void loop() {
  if(Serial.available() > 0){
    int second_num = Serial.read() - '0';
    if (second_num == 0){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
    }else if(second_num == 1){
      digitalWrite(A, LOW); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
    }else if(second_num == 2){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
    }else if(second_num == 3){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
    }else if(second_num == 4){
      digitalWrite(A, LOW); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
    }else if(second_num == 5){
      digitalWrite(A, HIGH); 
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
    }else if(second_num == 6){
      digitalWrite(A, HIGH); 
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, HIGH);
    }else if(second_num == 7){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
    }else if(second_num == 8){
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
    }else if(second_num == 9){
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
}