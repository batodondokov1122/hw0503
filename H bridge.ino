#define motor_pin_5 5
#define motor_pin_6 6
#define motor_pin_3 3
#define motor_pin_4 4

void setup() {
  pinMode(motor_pin_5, OUTPUT);
  pinMode(motor_pin_6, OUTPUT);
  pinMode(motor_pin_4, OUTPUT);
  pinMode(motor_pin_3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  spinBySpeedAndDirection("clockwise", 150);
  delay(3000);
  spinBySpeedAndDirection("counterclockwise", 255);
  delay(3000);
}

void spinBySpeedAndDirection(String direction, int speed){
  if (speed <= 255 && speed >= 0 && direction == "clockwise"){
    Serial.println("left");
    analogWrite(motor_pin_5, speed);
    analogWrite(motor_pin_3, speed);
    analogWrite(motor_pin_6, 0);
    analogWrite(motor_pin_4, 0);
  }
  else if (speed <= 255 && speed >= 0 && direction == "counterclockwise"){
    analogWrite(motor_pin_5, 0);
    analogWrite(motor_pin_3, 0);
    analogWrite(motor_pin_6, speed);
    analogWrite(motor_pin_4, speed);
  }
  else {
    Serial.println("Wrong arguments");
  }
}
