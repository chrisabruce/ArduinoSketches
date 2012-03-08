/*
  Blink on Motiion
  Makes a LED blink when motion is detected.
  Chris Bruce
 
  This example code is in the public domain.
 */

int ledPin = 13; // LED to blink
int safePin = 12;
int pirPin = 10; // Motion Sensor

boolean gTimerRunning = false;
unsigned long gElapsedTime = 0;
unsigned long gLastTimestamp = 0;
boolean gLedOn = false;
int gLastPirState;

void setup() {    
  pinMode(ledPin, OUTPUT);
  pinMode(safePin, OUTPUT);
  pinMode(pirPin, INPUT);
  gLastPirState = digitalRead(pirPin);
  timerStart();
}

void loop() {
  timerUpdate();
  
  int pirVal = digitalRead(pirPin);
  
  digitalWrite(safePin, !pirVal);
  
  if (pirVal != gLastPirState) {
    gLastPirState = pirVal;
    setLedValue(pirVal);
    timerReset();
  } else if (pirVal == HIGH) {
    blink();
  } else {
    turnLedOff();
    timerReset();
  }
}

void blink() {
  if (gElapsedTime > 100) {
    toggleLed();
    timerReset();
  }
}

// Updates the Timer if timer is running
void timerUpdate() {
  if (gTimerRunning && millis() > gLastTimestamp) {
    unsigned long difference = millis() - gLastTimestamp;
    gElapsedTime = gElapsedTime + difference;
  }
  gLastTimestamp = millis();
}

// Starts running the timer, does not reset value on start
void timerStart() {
  gTimerRunning = true;
}

// Stops the Timer, does not reset value on stop
void timerStop() {
  gTimerRunning = false;
}

// Resets the elapsed time to 0
void timerReset() {
  gElapsedTime = 0;
  gLastTimestamp = millis();
}

// Turns led on (and tracks state)
void turnLedOn() {
  gLedOn = true;
  digitalWrite(ledPin, HIGH);
}

// Turns led off (and tracks state)
void turnLedOff() {
  gLedOn = false;
  digitalWrite(ledPin, LOW);
}

// Sets the led to specific val (HIGH or LOW)
void setLedValue(int val) {
  if (val == HIGH) {
    turnLedOn();
  } else {
    turnLedOff();
  }
}

void toggleLed() {
  gLedOn = !gLedOn;
  digitalWrite(ledPin, gLedOn);
}
