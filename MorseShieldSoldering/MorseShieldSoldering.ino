#define DATA_PIN 2
#define STATUS_PIN 6
#define SOUND_PIN 7
#define POT_PIN A0
#define LED_PIN A1
#define DASH_DURATION 3
#define DOT_DURATION 1
#define END_WORD_DURATION 7
#define END_MESSAGE_DURATION 9
#define DATA_LEVEL LOW
#define SPACE_LEVEL HIGH
#define SPACE false
#define DATA true
int TU = 100;

const char lth = 4;
const char clk = 5; 
const char dat = 3;
int bit[] = { B11101110, B11111110, B10011100, B11111000, B10011110, B10001110, B10111100, B01101110, B00001100, B01110000, B10101110, B00011100, 
B11010100, B11101100, B11111100, B11001110, B11010110, B11011110, B10110110, B10001100, B01111100, B01110100, B10111000, B10010010, B01010110, B11011010, B00000000};

String CODES[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",  "-..-", "-.--", "--.."};
char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int NLETTERS = 26;
bool is_sent = false;
long last_letter_time, current_time;
int end_duration;
int status;

long start_data, start_space;
long duration[20];
bool color[20];
int index = 0;
int previous = SPACE_LEVEL;
String letter_string;
bool is_message_end = false;
bool is_space = false;
String message = "";

void setup() {
  Serial.begin(9600);
  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, SPACE_LEVEL);

  pinMode(LED_PIN, OUTPUT);

  pinMode(lth, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(dat, OUTPUT);
  digitalWrite(lth, 0);
  shiftOut(dat, clk, LSBFIRST, bit[NLETTERS]);
  digitalWrite(lth, 1);

  pinMode(POT_PIN, INPUT);

  pinMode(STATUS_PIN, INPUT);
}

void loop() {
  pinMode(DATA_PIN, OUTPUT);

  status = digitalRead(STATUS_PIN);
  if (status == 1){ // Работа в режиме передатчика сигнала
    TU = analogRead(POT_PIN);
    delay(100);
    if(Serial.available() >= 1){
      char letter_char = Serial.read();
      if(letter_char == ' '){
        String code = " ";
        send_letter(code);
        showLetter(NLETTERS);
      }else{
        for(int iletter = 0; iletter < NLETTERS; iletter++){
          if(letter_char == LETTERS[iletter]){
            String code = CODES[iletter];
            send_letter(code);
            showLetter(iletter);
          }
        }
      }
    }
    if(Serial.available() == 0){ // Проверка на конец сообщения
      current_time = millis();
      if (last_letter_time > 0 and current_time > 0){
        end_duration = int((current_time - last_letter_time + 0.5 * TU) / TU);
        if (end_duration == END_MESSAGE_DURATION - 2){
          end_message();
          showLetter(NLETTERS);
        }
      }
    }
  }
  else{ // Работа в режиме применика сигнала
    pinMode(DATA_PIN, INPUT);

    fill_arrays();
    decode_letter();
    if (is_message_end == true){ // Вывожу сообщение если оно закончилось
      Serial.println(message);
      for (int i = 0; i < message.length(); i++){
        if(message[i] == ' '){
          showLetter(NLETTERS);
          delay(END_WORD_DURATION * TU);
        }else{
          for(int iletter = 0; iletter < NLETTERS; iletter++){
            if(message[i] == LETTERS[iletter]){
              showLetter(iletter);
              makeSound(iletter);
            }
          }
        }
        delay(DASH_DURATION * TU);
      }
      is_message_end = false;
      message = "";
      showLetter(NLETTERS);
    }
  }
}

void showLetter(int index){ // Отобрадение букв на семисегментном индикаторе
  digitalWrite(lth, 0);
  shiftOut(dat, clk, LSBFIRST, bit[index]);
  digitalWrite(lth, 1);
}

void makeSound(int index){ // Издание звука с помощъю пъезодинамика
  String buffer_code = CODES[index];
  for (int i = 0; i < buffer_code.length(); i++){
    if (buffer_code == "."){
      tone(SOUND_PIN, 2000); 
      delay(DOT_DURATION * TU);
      noTone(SOUND_PIN); 
    }else{
      tone(SOUND_PIN, 2000); 
      delay(DASH_DURATION * TU);
      noTone(SOUND_PIN); 
    }
    delay(DOT_DURATION * TU);
  }
}

void end_message(){
  digitalWrite(DATA_PIN, DATA_LEVEL); // Отправляю сигнал после задержки, чтобы приемник мог определить конец сообщения
  delay(4 * TU); 
  digitalWrite(DATA_PIN, SPACE_LEVEL); // Здесь я отправляю пустой сигнал после задержки в 4TU (выбрал 4 потому, что такая длительность больше нигде не используется), чтобы можно было коректно считать длительность первого символа при следующей отправке
}

void send_letter(String code){ // Отправка сигнала
  Serial.println(code);
  if (code == " "){
    digitalWrite(LED_PIN, LOW);
    digitalWrite(DATA_PIN, SPACE_LEVEL);
    delay((END_WORD_DURATION - 4)*TU);
  }else{
    int code_len = code.length();
    for (int i = 0; i < code_len; i++){
      char symbol = code[i];
      if(symbol == '.'){
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(DATA_PIN, DATA_LEVEL);
        delay(DOT_DURATION * TU);
      }
      if(symbol == '-'){
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(DATA_PIN, DATA_LEVEL);
        delay(DASH_DURATION * TU);
      }
      digitalWrite(LED_PIN, LOW);
      digitalWrite(DATA_PIN, SPACE_LEVEL);
      delay(DOT_DURATION * TU);
    }
    delay((DASH_DURATION - 2) * TU);    
  }
  last_letter_time = millis();
}

void decode_letter() { // Расшифровка сигнала
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
          letter_string = LETTERS[iletter];
          message += letter_string;
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

void fill_arrays() { // Прием сигнала
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
