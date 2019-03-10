//Sensors and pushbtn
const int pushBtn = 12;
const int potent = A0;
const int photocell = A1;
const int tempSensor = A2;

//LEDS
const int myPins[] = {2, 3, 4};

//Globals
const bool TEST = false;
long int minMill , currMill , constMill, blinkMill;
int MINUTE = 6000, blinkTime = 300;
int Vout, lux;
int btnState = 0, prevBtnState = 0;
int state = 4;
int prevWind = 512, currWind = 512;
bool storm = false, blinkRed = true;
double  tempC, tempF;
int sumC = 0, sumLight = 0;
int avgC = 0, avgF = 0, avgLight = 0;
int counter = 0;

//Array for variables
String wind[] = {"Still", "Breezy", "Windy", "Gusty", "Stormy"};
String brightness[] = {"Dark", "Overcast", "Bright", "Sunny"};
String temp[] = {"Below Freezing", "Cool", "Warm", "Hot"};

//State
const int tempState = 1;
const int lightState = 2;
const int windState = 3;
const int allState = 4;

//Function Prototypes
void incrState();
void bckGrdRefresh();
String windSwitch(int n);
void redBlink();
String lightSwitch(int n);
String tempSwitch();
void avgValue();

//SETUP
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
//LOOP
void loop() {
  unsigned long currentMill = millis();
  boolean pushValue = digitalRead(pushBtn);

  avgValue();
  incrState();
  bckGrdRefresh();
  redBlink();
  if (TEST == true) {
    MINUTE = 60000;
  }
  if (millis() > currMill + (MINUTE)) {
    currMill = millis();

    if (state == tempState) {
      Serial.println("Temperature");
      Serial.println(String((int)round(tempC)) + " C " + String((int)round(tempF)) + " F \n");
    }
    else if (state == lightState) {
      Serial.println("Light:\t" + String(lightSwitch(lux)) + "\n");
    }
    else if (state == windState) {
      Serial.println("Wind:\t" + windSwitch(currWind));
      Serial.println("Potentiometer Reading: " + String(currWind) + "\n");
    }
    else if (state == allState) {
      Serial.println("----------------------------------------------------------- ");
      Serial.println("Mount Lake Resort Date: 31 Feb 0000 Time: 25:00" );
      Serial.println("Location: Peak Lake");
      Serial.println("----------------------------------------------------------- ");
      Serial.println("Wind: \t\t" + windSwitch(currWind));
      Serial.println("Outside Ambient Light: \t" + String(avgLight) + " Lux\t" + lightSwitch(avgLight));
      Serial.println("Outside Air Temperature:\t" + String(avgC) + " C " + String(avgF) + " F " + "\t" + String(tempSwitch(avgC)) + "\n");
    }
  }
}
void avgValue() {
  if (millis() > minMill + MINUTE / 6) {
    counter++;
    sumC += ((analogRead(tempSensor) * 5.00) / 1024.00 - 0.5) * 100;
    sumLight += constrain(analogRead(photocell), 0, 1023);
    //    Serial.println("COUNTER:"+String(counter));

    if (counter == 6) {
      avgC = sumC / 6;
      avgF = 1.8 * avgC + 32;
      avgLight =  sumLight / 6;
      sumC = 0;
      sumLight = 0;
      counter = 0;
    }
  }
}
void bckGrdRefresh() {
  if (millis() > constMill + 50) {
    constMill = millis();
    prevWind = currWind;
    currWind = analogRead(potent);
    lux = constrain(analogRead(photocell), 0, 1023);

    tempC = ((analogRead(tempSensor) * 5.00) / 1024.00 - 0.5) * 100;
    tempF = 1.8 * tempC + 32;

    if (currWind == 1023 || currWind == 0)
      storm = true;
    if (windSwitch(currWind) == wind[0])
      digitalWrite(4, LOW);
    else if (windSwitch(currWind) == wind[1] || windSwitch(currWind) == wind[2] || windSwitch(currWind) == wind[3] ) {
      digitalWrite(4, LOW);
      redBlink();
    }
    else if (windSwitch(currWind) == wind[4])
      digitalWrite(4, HIGH);

    if (lightSwitch(lux) == brightness[3]) {
      digitalWrite(3, HIGH);
    } else {
      digitalWrite(3, LOW);
    }

    if (tempC > 15) {
      digitalWrite(2, HIGH);
    } else {
      digitalWrite(2, LOW);
    }

  }
}
void redBlink() {
  if (millis() > blinkMill + blinkTime) {
    blinkMill = millis();

    if  (blinkRed == true) {
      if (digitalRead(4) == LOW) {
        digitalWrite(4, HIGH);
      } else {
        digitalWrite(4, LOW);
      }
    }
  }
}
String tempSwitch(int n) {
  String rtnValue;
  if (n <= 0) {
    rtnValue = temp[0];
  }
  if (n > 0 && n <= 15) {
    rtnValue = temp[1];
  }
  if (n > 15 && n <= 25) {
    rtnValue = temp[2];
  }
  if (n > 25) {
    rtnValue = temp[3];

  }
  return rtnValue;
}
String lightSwitch(int n) {
  String rtnValue;
  if (n <= 256) {
    rtnValue = brightness[0];
  }
  if (n > 256 && n <= 512) {
    rtnValue = brightness[1];
  }
  if (n > 512 && n <= 768) {
    rtnValue = brightness[2];
  }
  if (n > 768 && n <= 1024) {
    rtnValue = brightness[3];

  }
  return rtnValue;
}
String windSwitch(int n) {
  String rtnValue;

  //  Still
  if ((n == prevWind || n == (prevWind + 1) || n == (prevWind - 1) ) && prevWind >= 500 && prevWind <= 520 ) {
    rtnValue = wind[0];
    blinkRed = false;
    digitalWrite(4, LOW);
  }
  //    Breezy
  if ((n > 520 && prevWind < 500) ||  (n < 500 && prevWind > 520) ) {
    rtnValue = wind[1];
    blinkRed = true;
  }
  //Windy
  if ((n == prevWind || n == prevWind + 1 || n == prevWind - 1) && (n < 500 || n > 520)) {
    rtnValue = wind[2];
    blinkRed = true;
  }
  //Gusty
  if (((n < 500 && prevWind < 500) || (n > 520 && prevWind > 520)) && n != prevWind ) {
    rtnValue = wind[3];
    blinkRed = true;
  }
  //Stormy
  if (storm) {
    rtnValue = wind[4];
    blinkRed = false;
    digitalWrite(4, HIGH);
  }

  storm = false;
  return rtnValue;

}

void incrState() {
  btnState = digitalRead(pushBtn);
  if (btnState != prevBtnState) {
    if (btnState == 1) {
      state++;
      if (state > 4) {
        state = 1;
      }
    }
    prevBtnState = btnState;
    delay(50);
  }
}
