const int pushBtn = 12;
const int myPins[] = {2, 3, 4, 5, 6, 7};

long int prevMill = 0;
int currState = 1;

char* wind[] = {"Still", "Breezy", "Windy", "Gusty", "Stormy"};
char* brightness[] = {"Dark", "Overcast", "Bright", "Sunny"};
char* temp[] = {"Below Freezing", "Cool", "Warm", "Hot"};

const int tempState = 1;
const int lightState = 2;
const int windState = 3;
const int allState = 4;

void setup() {
  Serial.begin(9600);

  pinMode(pushBtn, INPUT);

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

 if (pushValue == HIGH) {
    if (currState < 4) {
      currState++;
    }
    else {
      currState = 1;
    }
    Serial.println(currState);
  }
  else
  pushValue = false;

  if (currentMill - prevMill > 1000) {
    prevMill = currentMill;
    if (currState = tempState) {
      Serial.println("Temperature");
      Serial.println("");
    }
    else if (currState = lightState) {
      Serial.println("Light:");
      Serial.println("");
    }
    else if (currState = windState) {
      Serial.println("Light:");
      Serial.println("");
    }
    else if (currState = allState) {
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
