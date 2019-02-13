const int pushBtn = 12;
const int potent = A0;
const int photocell = A1;
const int tempSensor = A2;

const int myPins[] = {2, 3, 4};

long int prevMill = 0;
int btnState = 0;
int prevBtnState = 0;
int state;

String wind[] = {"Still", "Breezy", "Windy", "Gusty", "Stormy"};
String brightness[] = {"Dark", "Overcast", "Bright", "Sunny"};
String temp[] = {"Below Freezing", "Cool", "Warm", "Hot"};

const int tempState = 1;
const int lightState = 2;
const int windState = 3;
const int allState = 4;

void setup() {
  Serial.begin(9600);

  pinMode(pushBtn, INPUT);
  pinMode(potent, INPUT);
  pinMode(tempSensor, INPUT);
  pinMode(photocell, INPUT);

  for (int ledPin : myPins) {
    pinMode(ledPin, OUTPUT);
  }
}
void loop() {
  unsigned long currentMill = millis();
  boolean pushValue = digitalRead(pushBtn);;

  for (int ledPin : myPins) {
    digitalWrite(ledPin, HIGH);
  }
  incrState();  if (currentMill - prevMill > 950) {
    prevMill = currentMill;
    if (state == tempState) {
      Serial.println("Temperature");
      double c = (int)round(analogRead(tempSensor) * 0.48828125);
      Serial.print(c);
      Serial.print(" C ");
      Serial.print((int)round(1.8*c+32));
      Serial.println(" F ");
    }
    else if (state == lightState) {
      Serial.println("Light:");
      Serial.println(analogRead(photocell));
    }
    else if (state == windState) {
      Serial.println("Wind:");
      Serial.println(analogRead(potent));
    }
    else if (state == allState) {
      Serial.println("----------------------------------------------------------- ");
      Serial.println("Count Lake Resort Date: ");
      Serial.println("Location:");
      Serial.println("----------------------------------------------------------- ");
      Serial.println("Wind:");
      Serial.println("Location:");
      Serial.println("Outside Ambient Light: ");;
    }
  }
}
void incrState() {
  btnState = digitalRead(pushBtn);
  if (btnState != prevBtnState) {
    if (btnState == 1) {
      state++;
      if (state > 4) {
        state = 1;
      }
//      Serial.println(state);
    }
    prevBtnState = btnState;
    delay(50);
  }
}
