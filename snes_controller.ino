int PWR = 3;
int CLK = 4;
int LTC = 5;
int DAT = 6;

char text[17] = "0000000000000000";
int dispCounter = 0;

void setup() {
  pinMode(PWR, OUTPUT);
  digitalWrite(PWR, HIGH);
  
  pinMode(CLK, OUTPUT);
  pinMode(LTC, OUTPUT);
  pinMode(DAT, OUTPUT);
  
  digitalWrite(CLK, HIGH);
  digitalWrite(LTC, HIGH);
  digitalWrite(DAT, HIGH);

  pinMode(DAT, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  pollButtons();
}

void pollButtons() {
  digitalWrite(LTC, HIGH);
  delayMicroseconds(12);
  digitalWrite(LTC, LOW);
  delayMicroseconds(6);
  
  for (unsigned i=0; i<16; i++) {
    digitalWrite(CLK, LOW);
    delayMicroseconds(6);
   
    if (i <= 11) {
      int pressed = digitalRead(DAT);
      if (pressed) {
        text[15-i] = '1';
      }
      else {
        text[15-i] = '0';
      }
    }
   
    digitalWrite(CLK, HIGH);
    delayMicroseconds(6);
  }
  
  if (dispCounter == 60) {
    Serial.println(text);
    dispCounter = 0;
  }
  dispCounter += 1;
  
  delay(16.4);
}
