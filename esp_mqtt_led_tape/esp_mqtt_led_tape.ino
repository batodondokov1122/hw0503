#include <FastLED.h>
#define NUM_LEDS 15
#define led_pin 13
#define DATA_PIN 2
#define CLOCK_PIN 15

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600); 
  pinMode(led_pin,OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 
}

void loop() { 
  if (Serial.available() > 0){
    char message = Serial.read();
    if(message == 'u'){
      digitalWrite(led_pin, HIGH);
      for (int i = 0; i < 15; i++){
        leds[i] = CRGB::Purple;
      }
      FastLED.show();
      delay(500); 
    }
    else if(message == 'd'){
      digitalWrite(led_pin, LOW);
      for (int i = 0; i < 15; i++){
        leds[i] = CRGB::Black;
      }
      FastLED.show();
      delay(500);
    }
    else{
      digitalWrite(led_pin, LOW);
      for (int i = 0; i < 15; i++){
        leds[i] = CRGB::Black;
      }
      FastLED.show();
      delay(500);
    }
  }
}
