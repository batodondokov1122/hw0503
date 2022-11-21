const char lth = 12; //ST_CP to pin 12
const char clk = 13; //SH_CP to pin 13
const char dat = 11; //DS to pin 11
int bit[11] = { B11111100, B01100000, B11011010, B11110010,
 B01100110, B10110110, B10111110, B11100000, B11111110,  B11110110, B0000000};

void setup() {
  Serial.begin(9600);
  pinMode(lth, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(dat, OUTPUT);
  digitalWrite(lth, 0);
  shiftOut(dat, clk, LSBFIRST, bit[11]);
  shiftOut(dat, clk, LSBFIRST, bit[11]);
  digitalWrite(lth, 1);
}

int k = 0;
void loop() {
  delay(100);
  k = Serial.available();
  if (k > 0){
    int *numbers = new int[k];
    for(int i = 0; i < k; i++){
      numbers[i] = Serial.read() - '0';
      delay(100);
    }
    for(int i = 0; i < k; i++){
      Serial.println(numbers[i]);
    }
    if (k == 1){
      digitalWrite(lth, 0);
      shiftOut(dat, clk, LSBFIRST, bit[numbers[0]]);
      shiftOut(dat, clk, LSBFIRST, bit[0]);
      digitalWrite(lth, 1);

    }
    else if (k == 2){
      digitalWrite(lth, 0);
      shiftOut(dat, clk, LSBFIRST, bit[numbers[1]]);
      shiftOut(dat, clk, LSBFIRST, bit[numbers[0]]);
      digitalWrite(lth, 1);
    }
    else{
      while(true){
        for(int i = 0; i <= k + 1; i++){
          if (i == 0){
            digitalWrite(lth, 0);
            shiftOut(dat, clk, LSBFIRST, bit[numbers[i]]);
            shiftOut(dat, clk, LSBFIRST, bit[11]);
            digitalWrite(lth, 1);
          }
          else if(i == k){
            digitalWrite(lth, 0);
            shiftOut(dat, clk, LSBFIRST, bit[11]);
            shiftOut(dat, clk, LSBFIRST, bit[numbers[i-1]]);
            digitalWrite(lth, 1);
          }
          else if(i == k+1){
            digitalWrite(lth, 0);
            shiftOut(dat, clk, LSBFIRST, bit[11]);
            shiftOut(dat, clk, LSBFIRST, bit[11]);
            digitalWrite(lth, 1);
          }
          else{
            digitalWrite(lth, 0);
            shiftOut(dat, clk, LSBFIRST, bit[numbers[i]]);
            shiftOut(dat, clk, LSBFIRST, bit[numbers[i-1]]);
            digitalWrite(lth, 1);
          }
          delay(500);
        }
      }
    }
  }
}
