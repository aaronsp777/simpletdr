
const uint8_t PORTS[] = {
  2, 3, 4, 5, 6, 7, 8, 9,  // Left RJ45 port (A)
  A0, A1, A2, A3, A4, A5, A6, A7 // Right RJ45 port (B)
};

const char* PORTNAMES[] = {
  "A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8",
  "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8",
};

const char TESTVALUES[] = { LOW, HIGH, LOW, HIGH };

void AllInput() {
  for (int i = 0; i < 16; i++) {
    pinMode(PORTS[i], INPUT_PULLUP);
  }
}

bool IsConnected(uint8_t a, uint8_t b) {
  bool match = true;
  pinMode(a, OUTPUT);
  
  for (int i = 0; i < sizeof(TESTVALUES); i++) {
    digitalWrite(a, TESTVALUES[i]);
    delay(1);
    if (digitalRead(b) != TESTVALUES[i]) {
      match = false;    
    }
  }

  pinMode(a, INPUT_PULLUP);
  return match;
}

void setup() {
  Serial.begin(57600);
}

void loop() {
  Serial.print("\nFinding Connections\n");
  int connections = 0;
  bool found[16];
  for (int i = 0; i < sizeof(PORTS); i++) {
    found[i] = false;
  }
  for (int i = 0; i < sizeof(PORTS); i++) {
    if (found[i]) {
      continue;
    }
    for (int j = i+1; j < sizeof(PORTS); j++) {
      AllInput();
      if (IsConnected(PORTS[i], PORTS[j])) {
        if (!found[i]) {
          Serial.print(PORTNAMES[i]);
          found[i] = true;
        }
        Serial.print(" - ");
        Serial.print(PORTNAMES[j]);
        found[j] = true;
        if (j != i + 8) {
          Serial.print("*");
        }
      }
    }
    if (found[i]) {
      connections++;
      Serial.print("\n");
    }
  }
  Serial.print("Found ");
  Serial.print(connections);
  Serial.print(" Connection(s)\n");
  delay(1000);
}
