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

#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x6F, 0x1F};
EthernetServer server(80);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  //hardware components
  pinMode(pushBtn, INPUT);
  pinMode(potent, INPUT);
  pinMode(tempSensor, INPUT);
  pinMode(photocell, INPUT);

  for (int ledPin : myPins) {
    pinMode(ledPin, OUTPUT);
  }

  Ethernet.begin(mac);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  unsigned long currentMill = millis();
  boolean pushValue = digitalRead(pushBtn);;
  //update functions
  avgValue();
  incrState();
  bckGrdRefresh();
  redBlink();
  if (TEST == true) {
    MINUTE = 60000;
  }
  if (millis() > currMill + (MINUTE)) {
    currMill = millis();
    // put your main code here, to run repeatedly:
    EthernetClient client = server.available();
    if (client) {
      Serial.println("new client");
      bool currentLineIsBlank = true;

      // an http request ends with a blank line
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          Serial.write(c);
          if (c == '\n' && currentLineIsBlank) {
            client.println("<!DOCTYPE html>");
            client.println("<html lang=\"en\">");
            client.println("");
            client.println("<head>");
            client.println("    <meta charset=\"UTF-8\">");
            client.println("    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
            client.println("    <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">");
            client.println("    <meta http-equiv=\"refresh\" content=\"5\">");
            client.println("    <link href=\"https://fonts.googleapis.com/css?family=Eagle+Lake|Montserrat\" rel=\"stylesheet\">");
            client.println("<style>");
            client.println("    * {");
            client.println("        text-align: center;");
            client.println("        margin: 0;");
            client.println("    }");
            client.println("");
            client.println("    body {");
            client.println("        background-color: #82b6e6;");
            client.println("        font-family: 'Montserrat', sans-serif;");
            client.println("    }");
            client.println("");
            client.println("    .section {");
            client.println("        border-radius: 15px 50px 30px;");
            client.println("        width: 80vw;");
            client.println("        height: 90vh;");
            client.println("        margin-left: 10vw;");
            client.println("        margin-bottom: 50px;");
            client.println("    }");
            client.println("");
            client.println("    .section h2 {");
            client.println("        padding-top: 40vh;");
            client.println("        font-size: 50px;");
            client.println("        font-weight: 200px;");
            client.println("    }");
            client.println("");
            client.println("    .menu {");
            client.println("        position: fixed;");
            client.println("        width: 80vw;");
            client.println("        margin-left: 10vw;");
            client.println("        opacity: 0.8;");
            client.println("    }");
            client.println("");
            client.println("    .menu a {");
            client.println("        padding: 10px 15px;");
            client.println("        float: right;");
            client.println("        text-decoration: none;");
            client.println("        font-size: 18px;");
            client.println("        background-color: white;");
            client.println("    }");
            client.println("");
            client.println("    .menu a:hover {");
            client.println("        background-color: whitesmoke;");
            client.println("    }");
            client.println("");
            client.println("    #all {");
            client.println("        height: 40%;");
            client.println("        padding-bottom: 10%;");
            client.println("    }");
            client.println("");
            client.println("    #all h1 {");
            client.println("        padding-top: 10%;");
            client.println("        padding-bottom: 2%;");
            client.println("        font-size: 50px;");
            client.println("    }");
            client.println("");
            client.println("    #wind {");
            client.println("        background-image: url(\"https://firebasestorage.googleapis.com/v0/b/fir-images-851b6.appspot.com/o/windy-png-hd-breeze-breezy-gust-of-wind-light-breeze-summer-weather-windy-512.png?alt=media&token=f2c1da8e-49b1-4564-8c0e-2e53a14b5e5f\");");
            client.println("        background-size: 400px;");
            client.println("        background-color: #a4dda4;");
            client.println("    }");
            client.println("");
            client.println("    #temp {");
            client.println("        background: url(\"https://firebasestorage.googleapis.com/v0/b/fir-images-851b6.appspot.com/o/thermometer-pngrepo-com.png?alt=media&token=de18912c-6c3f-442c-97e4-cd52cc8b2be2\");");
            client.println("        background-size: 200px;");
            client.println("        background-repeat: space 200px 200px;");
            client.println("        background-color: #3b484d;");
            client.println("        color: #f8f2ff;");
            client.println("    }");
            client.println("");
            client.println("    #light {");
            client.println("        background: url(\"https://firebasestorage.googleapis.com/v0/b/fir-images-851b6.appspot.com/o/pixar-lamp-2.png?alt=media&token=3ca2d01a-4a35-4057-b221-76bf70443816\") space 50px 50px;");
            client.println("        background-size: 250px;");
            client.println("        background-color: #bbd3f0;");
            client.println("        color: white;");
            client.println("    }");
            client.println("");
            client.println("    @media only screen and (max-width: 1600px) {");
            client.println("        #all {");
            client.println("            height: 50vh;");
            client.println("        }");
            client.println("");
            client.println("        #all h1 {");
            client.println("            padding-bottom: 5vh;");
            client.println("            font-size: 50px;");
            client.println("        }");
            client.println("");
            client.println("        .section {");
            client.println("            width: 90%;");
            client.println("            margin: 0% 5% 5% 5%;");
            client.println("        }");
            client.println("");
            client.println("        .menu {");
            client.println("            right: 0;");
            client.println("            width: 100vw;");
            client.println("        }");
            client.println("");
            client.println("        .menu a {");
            client.println("            width: 25vw;");
            client.println("            padding: 10px 0;");
            client.println("            font-size: 15px;");
            client.println("        }");
            client.println("    }");
            client.println("");
            client.println("    @media only screen and (max-width: 600px) {");
            client.println("        .section {");
            client.println("            border-radius: 0;");
            client.println("            width: 100%;");
            client.println("            margin: 0;");
            client.println("            height: 60vh;");
            client.println("        }");
            client.println("");
            client.println("        .section h2 {");
            client.println("            padding-top: 30vh;");
            client.println("            font-size: 40px;");
            client.println("            font-weight: 200px;");
            client.println("        }");
            client.println("");
            client.println("        #all {");
            client.println("            height: 40vh;");
            client.println("            padding-bottom: 10%;");
            client.println("        }");
            client.println("");
            client.println("        #all h1 {");
            client.println("            padding-top: 20%;");
            client.println("            padding-bottom: 10%;");
            client.println("            font-size: 50px;");
            client.println("        }");
            client.println("    }");
            client.println("</style>");
            client.println("    <title>Mount Lake Resort</title>");
            client.println("</head>");
            client.println("");
            client.println("<body>");
            client.println("    <div class=\"menuCont\">");
            client.println("        <div class=\"menu\">");
            client.println("            <a href=\"#light\">Light</a>");
            client.println("            <a href=\"#wind\">Wind</a>");
            client.println("            <a href=\"#temp\">Temperature</a>");
            client.println("            <a href=#all>Home</a>");
            client.println("        </div>");
            client.println("    </div>");
            client.println("    <header id=\"all\" class=\"section\">");
            client.println("        <h1>Mount Lake Resort</h1>");
            client.println("        Wind-speed:" + windSwitch(currWind));
            client.println("        <br>");
            client.println("        Temperature: " + String((int)round(tempC)) + " C " + " &#176;" + String((int)round(tempF)) + " F" + " &#176;");
            client.println("        <br>");
            client.println("        light:" + String(lightSwitch(lux)));
            client.println("    </header>");
            client.println("");
            client.println("");
            client.println("    <div class=\"section\" id=\"temp\">");
            client.println("        <h2> Temperature</br>" + String((int)round(tempC)) + " C" + " &#176; " + String((int)round(tempF)) + "F &#176; </h2> ");
            client.println("    </div > ");
            client.println("    <div class = \"section\" id=\"wind\">");
            client.println("        <h2>Wind Speeds</br>" + windSwitch(currWind) + "</h2>");
            client.println("    </div>");
            client.println("    <div class=\"section\" id=\"light\">");
            client.println("        <h2>Ambient Light</br>" + lightSwitch(avgLight) + "</h2>");
            client.println("    </div>");
            client.println("    <footer></footer>");
            client.println("</body>");
            client.println("");
            client.println("</html>");
            break;
          }
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
} void avgValue() {
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
  if (millis() > constMill + 50u) {
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