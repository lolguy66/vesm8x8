const int row[8] = {
  0, 1, 2, 3, 4, 5, 6, 7
};

// 2-dimensional array of column pin numbers:
const int col[8] = {
  8, 9, 10, 11, 12, 13, A5, A4
};

// 2-dimensional array of pixels:
int pixels[8][8];

// cursor position:
int x = 5;
int y = 5;

// BUTTON
const int buttonPin = A2;
// const int buttonPin2 = 0;
int buttonState = 0;
// int buttonState2 = 0;

// Stýripinnar
int vrx = A0; // Stýripinni X
int vry = A1; // Stýripinni Y

// Staðsetning
int bendill = 0; // staðsetning í fylkinu

void setup() {
  pinMode(buttonPin, INPUT);
  // pinMode(buttonPin2, INPUT);
  // initialize the I/O pins as outputs iterate over the pins:
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that the LEDS are off:
    digitalWrite(col[thisPin], LOW);
  }

  // initialize the pixel matrix:
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = LOW;
    }
  }
}

void loop() {
  // Les hvort takkinn sé high eða low
  buttonState = digitalRead(buttonPin);
  // buttonState2 = digitalRead(buttonPin2);
  
  // read input:
  readSensors();

  // draw the screen:
  refreshScreen();

  // Cleara skjáinn ef takkinn er high
  if (buttonState == HIGH) {
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        pixels[x][y] = LOW;
      }
    }
  }
}

void readSensors() {
   // turn off the last position:
   pixels[x][y] == LOW;
   // read the sensors for X and Y values:
   x = 7 - map(analogRead(A0), 0, 1023, 0, 7);
   y = map(analogRead(A1), 0, 1023, 0, 7);
   // set the new pixel position high so that the LED will turn on in the next
   // screen refresh:
   pixels[x][y] = HIGH;
}

void refreshScreen() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], LOW);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];
      // when the row is HIGH and the col is LOW,
      // the LED where they meet turns on:
      digitalWrite(col[thisCol], thisPixel);
      // turn the pixel off:
      if (thisPixel == HIGH) {
        digitalWrite(col[thisCol], LOW);
      }
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], HIGH);
  }
}
