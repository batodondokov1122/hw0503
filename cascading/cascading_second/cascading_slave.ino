#define A  2
#define B  3
#define C  4
#define D  5
#define E  6
#define F  7
#define G  8
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

void loop() {
  delay(100);
  if(Serial.available() > 0){
    char input = Serial.read();
    if (input == '-'){
      led_off();
    }
    else{
      int number = input - '0';
      Serial.println(number);
      led_on(number);
    }
  }
}
