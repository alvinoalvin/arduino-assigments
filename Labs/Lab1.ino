int switch_1 = 11;
int switch_2 = 12;
int myPins[] = {2, 3, 4, 5, 6, 7};
int statePins[] = {53, 52};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(switch_1, INPUT);
  pinMode(switch_2, INPUT);

  for (int ledPin : myPins) {
    pinMode(ledPin, OUTPUT);
  }
  for (int pin : statePins) {
    pinMode(pin, OUTPUT);
  }

}
void loop() {
  int s1State = digitalRead(switch_1);
  int s2State = digitalRead(switch_2);

  showState(s1State, s2State);
  ledStates(s1State, s2State);
}

//was gonna use timers for this but didnt have time to implement it.
//shows the state using the leds at the end.
void showState(int s1State, int s2State) {
  digitalWrite(statePins[0], s1State);
  digitalWrite(statePins[1], s2State);
}

void ledStates(int s1State, int s2State) {
  if (s1State == LOW && s2State == LOW) {
    state00();
  }
  else if (s1State == LOW && s2State == HIGH) {
    state01();
  }
  else if (s1State == HIGH && s2State == LOW) {
    state10();
  }
  else if (s1State == HIGH && s2State == HIGH) {
    state11();
  }
}

//STATE 00
void state00() {
  Serial.println("State 00");

  //    STATE 1
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(7, HIGH);

  //    STATE 2
  delay(1000);
  digitalWrite(2, LOW);
  blink(3, 1000);

  //    STATE 3
  delay(1000);
  digitalWrite(7, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);

  //    STATE 4
  delay(1000);
  digitalWrite(5, LOW);
  blink(6, 1000);
  delay(1000);
}

//STATE 01
void state01() {
  Serial.println("State 01");
  //    STATE 1
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(7, HIGH);

  //    STATE 2
  delay(5000);
  digitalWrite(2, LOW);
  blink(3, 5000);

  //    STATE 3
  delay(1000);
  digitalWrite(7, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);

  //    STATE 4
  delay(5000);
  digitalWrite(5, LOW);
  blink(6, 5000);
  delay(1000);
}

//STATE 10
void state10() {
  Serial.println("State 10");
  //    STATE 1
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(7, HIGH);

  //    STATE 2
  delay(8000);
  digitalWrite(2, LOW);
  blink(3, 8000);

  //    STATE 3
  delay(2000);
  digitalWrite(7, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);

  //    STATE 4
  delay(8000);
  digitalWrite(5, LOW);
  blink(6, 8000);
  delay(2000);
}

//STATE 11
void state11() {
  Serial.println("State 11");
  //    STATE 1
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(7, HIGH);

  //    STATE 2
  delay(15000);
  digitalWrite(2, LOW);
  blink(3, 15000);

  //    STATE 3
  delay(5000);
  digitalWrite(7, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);

  //    STATE 4
  delay(10000);
  digitalWrite(5, LOW);
  blink(6, 10000);
  delay(5000);
}

void blink(int pin, int time) {
  for (int i = 0; i < (time / 90); i++) {
    digitalWrite(pin, HIGH);
    delay(30);
    digitalWrite(pin, LOW);
    delay(30);
    digitalWrite(pin, HIGH);
    delay(30);
  }
}