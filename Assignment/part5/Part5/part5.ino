int pinG = 12;
int pinY = 11;
int pinR = 10;
char val;

void setup()
{
  // put your setup code here, to run once:
  pinMode(pinG, OUTPUT);
  pinMode(pinY, OUTPUT);
  pinMode(pinR, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(pinR, HIGH);
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    char val = Serial.read();
  }
  if (val == 'r')
  {
    digitalWrite(pinR, HIGH);
  }
  else if (val == 'y')
  {
    digitalWrite(pinR, HIGH);
  }
  else if (val == 'g')
  {
    digitalWrite(pinR, HIGH);
  }
  else if (val == 'o')
  {
    digitalWrite(pinR, LOW);
    digitalWrite(pinG, LOW);
    digitalWrite(pinY, LOW);
  }
}
