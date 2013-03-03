#define IR_LED 2
#define BUTTON_PIN 7
#define PULSE_TIME 13
#define FREQUENCY 26
#define NUM_ACTIONS 4

int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int nextPress = 0;

void onOff(unsigned int on_time, unsigned int off_time);
void sendIR(unsigned int microseconds);

void setup() {
  pinMode(IR_LED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
// read the pushbutton input pin:
  buttonState = digitalRead(BUTTON_PIN);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // The button is pressed
    if (buttonState == HIGH) {
      if (nextPress == 0) {
        //powerCode();
        channelUp();
        //channelUp();
      } else if (nextPress == 1) {
        //channelDown();
        channelDown();
      }  else if (nextPress == 2) {
        volumeUp();
      }  else if (nextPress == 3) {
        volumeDown();
      }
      nextPress += 1;
      nextPress %= NUM_ACTIONS;
    }
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState = buttonState;
}

void powerCode() {
  sendCode(B11100000,
           B11100000,
           B01000000,
           B10111111);

}

void channelUp() {
  sendCode(B11100000,
           B11100000,
           B01001000,
           B10110111);
}

void channelDown() {
  sendCode(B11100000,
           B11100000,
           B00001000,
           B11110111);

}

void volumeUp() {
  sendCode(B11100000,
           B11100000,
           B11100000,
           B00011111);
}

void volumeDown() {
  sendCode(B11100000,
           B11100000,
           B11010000,
           B00101111);

}

void sendByte(byte b) {
  for (int i = 7; i >= 0; i -= 1) {
    if (b & (1 << i)) {
      onOff(600, 1600);
    } else {
      onOff(600, 500);
   }
  }
}

/* Reads the bits in each of the bytes interpreting 1 as 
 * a long off and 0 as a short off
 */
void sendCode(byte hi1, byte hi2, byte lo1, byte lo2) {
  // the start of all the codes
  onOff(4500, 4400);

  sendByte(hi1);
  sendByte(hi2);
  sendByte(lo1);
  sendByte(lo2);

  // The final pulse
  onOff(600, 0);
}

/* Turns IR on for on_time microseconds, then stays off
 * for off_time microseconds and returns
 */
void onOff(unsigned int on_time, unsigned int off_time) {
  sendIR(on_time);
  delayMicroseconds(off_time);
}

/*
 * Sends a 38kHz signal for on, then shuts off
 */
void sendIR(unsigned int microseconds) {
  // Interrups off
  cli();

  for (int i = 0; i < microseconds; i += FREQUENCY) {
    // Turn on
    PORTD |= (1 << IR_LED);
    delayMicroseconds(PULSE_TIME);

    // Turn off
    PORTD &= ~(1 << IR_LED);
    delayMicroseconds(PULSE_TIME);
  }

  // Interrupts back on
  sei();
}