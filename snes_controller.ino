#include <HID-Project.h>

int PWR = 3;  // Controller power (5V)
int CLK = 2;  // Clock
int LTC = 1;  // Latch
int DAT = 0;  // Data

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

  Gamepad.begin();
}

void loop() {
  int buttons = pollButtons();
  communicateButtons(buttons);
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
  if (pressed & A) {
    Gamepad.press(0);
  }
  if (pressed & B) {
    Gamepad.press(1);
  }
  if (pressed & X) {
    Gamepad.press(2);
  }
  if (pressed & Y) {
    Gamepad.press(3);
  }
  if (pressed & L) {
    Gamepad.press(4);
  }
  if (pressed & R) {
    Gamepad.press(5);
  }
  if (pressed & START) {
    Gamepad.press(6);
  }
  if (pressed & SELECT) {
    Gamepad.press(7);
  }

  int padState = GAMEPAD_DPAD_CENTERED;
  if (pressed & LEFT) {
    padState = GAMEPAD_DPAD_LEFT;
    if (pressed & UP) {
      padState = GAMEPAD_DPAD_UP_LEFT;
    }
    else if (pressed & DOWN) {
      padState = GAMEPAD_DPAD_DOWN_LEFT;
    }
  }
  else if (pressed & RIGHT) {
    padState = GAMEPAD_DPAD_RIGHT;
    if (pressed & UP) {
      padState = GAMEPAD_DPAD_UP_RIGHT;
    }
    else if (pressed & DOWN) {
      padState = GAMEPAD_DPAD_DOWN_RIGHT;
    }
  }

  Gamepad.dPad1(padState);

  Gamepad.write();
}

