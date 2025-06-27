// Define pins for columns and rows
const uint8_t columnPins[9] = {4, 2, 3, 5, 6, 7, 8, 9, 10}; // Output pins
const uint8_t rowPins[5]    = {11, 12, 13, A0, A1};          // Input pins with pullups

// Store previous state to detect key changes
bool keyState[9][5] = {false};

void setup() {
  Serial.begin(9600);

  // Setup column pins as outputs
  for (int c = 0; c < 9; c++) {
    pinMode(columnPins[c], OUTPUT);
    digitalWrite(columnPins[c], HIGH); // Set columns HIGH initially
  }

  // Setup row pins as inputs with pullup resistors
  for (int r = 0; r < 5; r++) {
    pinMode(rowPins[r], INPUT_PULLUP);
  }

  Serial.println("Keyboard scanner ready...");
}

void loop() {
  for (int c = 0; c < 9; c++) {
    // Drive one column LOW
    digitalWrite(columnPins[c], LOW);

    // Check all rows
    for (int r = 0; r < 5; r++) {
      bool pressed = (digitalRead(rowPins[r]) == LOW); // LOW means key is pressed

      if (pressed != keyState[c][r]) {
        keyState[c][r] = pressed;

        if (pressed) {
          Serial.print("Key pressed at C");
          Serial.print(c);
          Serial.print(", R");
          Serial.println(r);
        } else {
          Serial.print("Key released at C");
          Serial.print(c);
          Serial.print(", R");
          Serial.println(r);
        }
      }
    }

    // Set column back to HIGH
    digitalWrite(columnPins[c], HIGH);
  }

  delay(10); // Debounce delay
}
