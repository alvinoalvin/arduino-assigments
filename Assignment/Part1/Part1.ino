//OUTPUTS
int LED_G = 2; boolean G_state = true;
int LED_R = 3; boolean R_state = false;

//INPUTS
int PUSHBTN = 4;

//VARIABLES
int currMill, pushBtnMill;
int SECOND = 1000;

int btnState = 0, prevBtnState = 0, state;

void setup() {
  Serial.begin(9600);

  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);

  pinMode(PUSHBTN, INPUT_PULLUP);

}

void loop() {
  unsigned long currentMill = millis();
  boolean pushValue = digitalRead(PUSHBTN);
  incrState();

  if (state % 2 == 1) {
    digitalWrite(LED_R, HIGH);
    R_state = false;
  }
  else {
    digitalWrite(LED_R, LOW);
    R_state = true;
  }

  if (millis() > currMill + 5 * SECOND) {
    currMill = millis();
    if (G_state == true) {
      digitalWrite(LED_G, HIGH);
      G_state = false;
    }
    else {
      digitalWrite(LED_G, LOW);
      G_state = true;
    }
  }
}
void incrState() {
  btnState = digitalRead(PUSHBTN);
  if (btnState != prevBtnState) {
    if (btnState == 1) {
      state++;
      if (state > 2) {
        state = 1;
      }
    }
    prevBtnState = btnState;
  }
  delay(50);
}
