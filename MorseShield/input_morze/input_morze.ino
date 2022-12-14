#include <SoftwareSerial.h>
#define DATA_PIN 2
#define DATA_LEVEL LOW
#define SPACE_LEVEL HIGH
#define SPACE false
#define DATA true
#define DASH_DURATION 3
#define DOT_DURATION 1
#define END_WORD_DURATION 7
#define END_MESSAGE_DURATION 9
#define TU 100

long start_data, start_space;
long duration[20];
bool color[20];
int index = 0;
int previous = SPACE_LEVEL;
String CODES[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",  "-..-", "-.--", "--.."};
char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int NLETTERS = 26;
String letter;
bool is_message_end = false;
bool is_space = false;
String message = "";

void setup() {
  pinMode(DATA_PIN, INPUT);
  Serial.begin(9600);
}

void loop(){
  fill_arrays();
  decode_letter();
  if (is_message_end == true){ // Вывожу сообщение если оно закончилось
    Serial.println(message);
    is_message_end = false;
    message = "";
  }
}

void decode_letter() {
  for(int i=0; i<index; i++) {
    if((duration[i] == DASH_DURATION and color[i] == SPACE) or (duration[i] == 9 and color[i] == SPACE)or (duration[i] == 7 and color[i] == SPACE)){
      if (duration[i] == END_MESSAGE_DURATION and color[i] == SPACE){ // Определяю, что сообщение закончилось
        is_message_end = true;
      }
      if (duration[i] == END_WORD_DURATION and color[i] == SPACE){ // Определяю, что слово закончилось
        is_space = true;
      }
      String code = "";

      for(int j=0; j<i; j++){
        if (duration[j] == DOT_DURATION and color[j] == DATA){
          code += ".";
        }
        else if(duration[j] == DASH_DURATION and color[j] == DATA){
          code += "-";
        }
        duration[j] = 0;
      }
      duration[i] = 0;
      for(int iletter=0; iletter < NLETTERS; iletter++){
        if(code == CODES[iletter]){
          letter = LETTERS[iletter];
          message += letter;
          start_space = 0;
        }
      }
      if (is_space == true){ // Добавляю пробел в сообщение если слово закончилось
        message += " "; 
        is_space = false;
      }
      index = 0; 
    }
  }
}

void fill_arrays() {
  int current =  digitalRead(DATA_PIN);
  if(current == DATA_LEVEL and previous == SPACE_LEVEL){
    start_data = millis();
    duration[index] = int((start_data - start_space + 0.5 * TU) / TU);
    color[index] = SPACE;
    index++;
  }
  if(current == SPACE_LEVEL and previous == DATA_LEVEL){
    start_space = millis();
    duration[index] = int((start_space - start_data + 0.5 * TU) / TU);
    color[index] = DATA;
    index++;
  }
  previous = current;
}
