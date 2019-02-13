//Sensors and pushbtn
const int pushBtn = 12;
const int potent = A0;
const int photocell = A1;
const int tempSensor = A2;

//LEDS
const int myPins[] = {2, 3, 4};

//Globals
long int windMill = 0, currMill = 0 ;

int btnState = 0;
int prevBtnState = 0;
int state;
int prevWind = 512, currWind = 512;

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
String windSwitch(int n);

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

  boolean pushValue = digitalRead(pushBtn);;

  for (int ledPin : myPins) {
    digitalWrite(ledPin, HIGH);
  }
  incrState();

  //  unsigned long windCurrMill = millis();
  if (millis() > windMill + 1000) {// use 60000 for minute using 1000 for testing
    windMill = millis();
    prevWind = currWind;
//    Serial.println(prevWind);
  }

  if (millis() > currMill + 950) {
    currMill = millis();
    if (state == tempState) {
      Serial.println("Temperature");
      //double c = (((double)(analogRead(tempSensor)) * 0.0048828125)) * 100; // voltage
     int reading = analogRead(tempSensor);  
     // converting that reading to voltage, for 3.3v arduino use 3.3
     double voltage = reading * 5.0;
     voltage /= 1024.0;
     
     // now print out the temperature
     double c = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
      Serial.print(c);                                               //to degrees ((voltage - 500mV) times 100)      Serial.print(c);
      Serial.print(" C ");

      Serial.print((int)round(1.8 * c + 32));
      Serial.println(" F ");
    }
    else if (state == lightState) {
      Serial.println("Light:");
      Serial.println(analogRead(photocell));
    }
    else if (state == windState) {
      Serial.println("Wind:");
      Serial.println(windSwitch(analogRead(potent)));
    }
    else if (state == allState) {
      Serial.println("----------------------------------------------------------- ");
      Serial.println("Count Lake Resort Date: ");
      Serial.println("Location:");
      Serial.println("----------------------------------------------------------- ");
      Serial.println("Wind: \t");
      Serial.println("Location: \t");
      Serial.println("Outside Ambient Light: \t");;
    }
  }
}

String windSwitch(int n) {
  String rtnValue;
  if (n == (512 - 205) && prevWind == (512 - 205))
    rtnValue = wind[0];
  if (n != (512 - 205) && prevWind == (512 - 205))
    rtnValue = wind[1];
  if (n == prevWind && n != 512)
    rtnValue = wind[2];
  if (n > 615 && n <= 820)
    rtnValue = wind[3];
  if (n >= 820)
    return wind[4];
  currWind = n;
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
      //      Serial.println(state);
    }
    prevBtnState = btnState;
    delay(50);
  }
}
