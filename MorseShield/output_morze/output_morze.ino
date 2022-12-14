#define DATA_PIN 9
#define DASH_DURATION 3
#define DOT_DURATION 1
#define END_WORD_DURATION 7
#define END_MESSAGE_DURATION 9
#define DATA_LEVEL LOW
#define SPACE_LEVEL HIGH
#define TU 100

String CODES[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",  "-..-", "-.--", "--.."};
char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int NLETTERS = 26;
bool is_sent = false;
long last_letter_time, current_time;
int end_duration;

void setup() {
  Serial.begin(9600);
  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, SPACE_LEVEL);
}

void loop() {
  delay(100);
  if(Serial.available() >= 1){
    char letter = Serial.read();
    if(letter == ' '){
      String code = " ";
      send_letter(code);
    }else{
      for(int iletter = 0; iletter < NLETTERS; iletter++){
        if(letter == LETTERS[iletter]){
          String code = CODES[iletter];
          send_letter(code);
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
      }
    }
  }
}

void end_message(){
  digitalWrite(DATA_PIN, DATA_LEVEL); // Отправляю сигнал после задержки, чтобы приемник мог определить конец сообщения
  delay(4 * TU); 
  digitalWrite(DATA_PIN, SPACE_LEVEL); // Здесь я отправляю пустой сигнал после задержки в 4TU (выбрал 4 потому, что такая длительность больше нигде не используется), чтобы можно было коректно считать длительность первого символа при следующей отправке
}

void send_letter(String code){
  Serial.println(code);
  if (code == " "){
    digitalWrite(DATA_PIN, SPACE_LEVEL);
    delay((END_WORD_DURATION - 4)*TU);
  }else{
    int code_len = code.length();
    for (int i = 0; i < code_len; i++){
      char symbol = code[i];
      if(symbol == '.'){
        digitalWrite(DATA_PIN, DATA_LEVEL);
        delay(DOT_DURATION * TU);
      }
      if(symbol == '-'){
        digitalWrite(DATA_PIN, DATA_LEVEL);
        delay(DASH_DURATION * TU);
      }
      digitalWrite(DATA_PIN, SPACE_LEVEL);
      delay(DOT_DURATION * TU);
    }
    delay((DASH_DURATION - 2) * TU);    
  }
  last_letter_time = millis();
}
