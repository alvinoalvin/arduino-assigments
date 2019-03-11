int pinG = 2;
int pinY = 3;
int pinR = 4;

void setup()
{
  // put your setup code here, to run once:
  pinMode(pinG, HIGH);
  pinMode(pinY, HIGH);
  pinMode(pinR, HIGH);
  Serial.begin(9600);
}

void loop()
{
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
