int PWR = 3;  // Controller power (5V)
int CLK = 4;  // Clock
int LTC = 5;  // Latch
int DAT = 6;  // Data

// Button masks
const int B      = 1 << 0;
const int Y      = 1 << 1;
const int SELECT = 1 << 2;
const int START  = 1 << 3;
const int UP     = 1 << 4;
const int DOWN   = 1 << 5;
const int LEFT   = 1 << 6;
const int RIGHT  = 1 << 7;
const int A      = 1 << 8;
const int X      = 1 << 9;
const int L      = 1 << 10;
const int R      = 1 << 11;

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
  int buttons = pollButtons();
}

int pollButtons() {
  int pressed = 0;
  
  digitalWrite(LTC, HIGH);
  delayMicroseconds(12);
  digitalWrite(LTC, LOW);
  delayMicroseconds(6);
  
  for (unsigned i=0; i<16; i++) {
    digitalWrite(CLK, LOW);
    delayMicroseconds(6);
   
    if (i <= 11) {
      int signal = digitalRead(DAT);
      if (!signal) {
        pressed |= (1 << i);
      }
    }
   
    digitalWrite(CLK, HIGH);
    delayMicroseconds(6);
  }
  
  delay(16.46);  // The sleeps above take 0.21 ms, so this delay gives us a total duration of 16.67ms -> 60Hz
  return pressed;
}

void communicateButtons(int pressed) {
  // TODO: implementation
}
