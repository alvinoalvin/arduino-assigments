int tempSensor = A2;
int photoCell = A3;
void setup()
{
    Serial.begin(9600);
    pinMode(tempSensor, INPUT);
    pinMode(photoCell, INPUT);
}
void loop()
{
    float temperature = 0;
    float humidity = 0;

    humidity = analogRead(photoCell);
    temperature = analogRead(tempSensor);

    Serial.print((float)temperature);
    Serial.print(",");
    Serial.println((float)humidity);
    delay(2500);
}