#define IR_LED 2
#define BUTTON_PIN 7
#define PULSE_TIME 13
#define FREQUENCY 26

int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

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
      powerCode();      
    }
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState = buttonState;
}

void powerCode() {
  onOff(4480, 4372);
  onOff(588, 1600);
  onOff(596, 1600);
  onOff(592, 1600);
  onOff(588, 508);
  onOff(588, 508);
  onOff(584, 508);
  onOff(588, 504);
  onOff(588, 508);
  onOff(584, 1608);
  onOff(588, 1600);
  onOff(596, 1604);
  onOff(584, 504);
  onOff(592, 504);
  onOff(588, 508);
  onOff(584, 512);
  onOff(584, 500);
  onOff(600, 500);
  onOff(588, 1604);
  onOff(592, 500);
  onOff(592, 504);
  onOff(584, 508);
  onOff(588, 508);
  onOff(588, 504);
  onOff(592, 508);
  onOff(580, 1604);
  onOff(596, 500);
  onOff(588, 1604);
  onOff(592, 1600);
  onOff(592, 1604);
  onOff(588, 1604);
  onOff(588, 1600);
  onOff(592, 1604);
  onOff(588, 0);
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