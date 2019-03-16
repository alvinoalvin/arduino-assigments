// Use the softwareserial library to create a new "soft" serial port
// for the display. This prevents display corruption when uploading code.
#include <SoftwareSerial.h >

// Attach the serial display's RX line to digital pin 2
SoftwareSerial mySerial(3, 2); // pin 2 = TX, pin 3 = RX (unused)

void setup() {
  mySerial.begin(9600); // set up serial port for 9600 baud
  pinMode(A5, INPUT);
}

int temp;
char tempstring[10]; // create string array
double getVoltage();

void loop() {
  //  temp = (getVoltage() - 0.5) * 100.0;//Temperature reading
  temp = getC();
  mySerial.write(254);
  mySerial.write(128);
  sprintf(tempstring, "%4d", temp); // create strings from the numbers

  mySerial.write("Temp: ");
  mySerial.write(tempstring);
  mySerial.write((char)223);
  mySerial.write("C");
  mySerial.println("            ");
  delay(1000);
}
//
double getC() {
  double voltage = analogRead(A5) * 0.004882814;
  return (voltage - 0.5) * 100.0; //Temperature reading
}
