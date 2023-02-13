const int d3Pin = 3;
const int d4Pin = 4;
const int d5Pin = 5;
const int d6Pin = 6;

void setup() {
  pinMode(d3Pin, INPUT);
  pinMode(d4Pin, INPUT);
  pinMode(d5Pin, OUTPUT);
  pinMode(d6Pin, OUTPUT);
  Serial.begin(9600);
}
long currentMillis = 0;
long previousMillis = 0;
int currentValue = 0;
int previousValue = 0;
String currentSeq = "";
String previousSeq = "";

void loop() {
  digitalWrite(d5Pin, HIGH);
  digitalWrite(d6Pin, LOW);
  currentSeq = currentSeq + String(ReadWithDelay(d3Pin));
  currentSeq = currentSeq + String(ReadWithDelay(d4Pin));
  digitalWrite(d6Pin, HIGH);
  digitalWrite(d5Pin, LOW);
  currentSeq = currentSeq + String(ReadWithDelay(d3Pin));
  currentSeq = currentSeq + String(ReadWithDelay(d4Pin));
  if (currentSeq != previousSeq){
    PrintButtonNums(currentSeq);    
  }
  previousSeq = currentSeq;
  currentSeq = "";
}

int ReadWithDelay(int pin){
  currentValue = digitalRead(pin);
  if (currentValue != previousValue)  {
    delay(50);
    currentMillis = millis();
    previousMillis = currentMillis;
    while (currentMillis - previousMillis < 50){
      currentMillis = millis();
    }
    currentValue = digitalRead(pin);
  }
  previousValue = currentValue;
  return currentValue;
}

void PrintButtonNums(String seq) {
  int count = 0;
  for (int i = 0; i < 4; i++) {
    if (seq[i] == '1') {
      count += 1;
    }
  }
  if (count  == 1){
    for (int i = 0; i < 4; i++) {
      if (seq[i] == '1') {
        Serial.print("Number of button pressed ");
        Serial.print(i+1);
        Serial.println(";");
      }
    }
  }
  else if(count == 0){
    
  }
  else{
    int buttonNums[count];
    int index = 0;
    for (int i = 0; i < 4; i++) {
      if (seq[i] == '1') {
        buttonNums[index] = i+1;
        index += 1;
      }
    }
    Serial.print("Numbers of buttons pressed: ");
    for (int i = 0; i < count; i++){
      if (i == count - 1){
        Serial.print(buttonNums[i]);
        Serial.println(";");
      }else{
        Serial.print(buttonNums[i]);
        Serial.print(", ");
      }
    }    
  }
}
