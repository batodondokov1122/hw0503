int led_pin = 3;
int pushButton = 2;
int status = 0;
int last_buttonState = 0;
int brightness = 255;
int step = 15;

void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(pushButton);
  Serial.println(buttonState);
  if(buttonState == 1 & last_buttonState != 1){
    if (status == 0){
      digitalWrite(led_pin, HIGH);
      status = 1;
    }
    else{
      digitalWrite(led_pin, LOW);
      status = 0;
    }
  }
  if(buttonState == 1 & last_buttonState == 1 & status == 1){
    if (brightness == 0 || brightness == 255){
      step = step * -1;
    }
    brightness = brightness + step;
    analogWrite(led_pin,brightness);
  }
  delay(100);
  last_buttonState = buttonState;
}
