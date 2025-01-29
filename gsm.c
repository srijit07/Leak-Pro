#include <SoftwareSerial.h>

SoftwareSerial SIM900A(2,3);

void setup()
{
  SIM900A.begin(9600);   // gsm mod baud rate
  Serial.begin(9600);    // serial monitor baud rate
  Serial.println ("Type s to send or r to receive message");
}


void loop()
{
  if (Serial.available()>0)
    switch(Serial.read())
    {
      case 's':
        SendMessage();
        break;
      case 'r':
        ReceiveMessage();
        break;
    }

  if (SIM900A.available()>0)
    Serial.write(SIM900A.read());
}


void SendMessage()
{
  Serial.println ("Sending Message...");
  SIM900A.println("AT+CMGF=1");
  delay(1000);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+919731176374\"\r");
  delay(1000);
  Serial.println ("Set SMS Content");
  SIM900A.println("Testing message from arduino gsm module to my phone lol!");
  delay(100);
  Serial.println ("Done");
  SIM900A.println((char)26);
  // delay(1000);
  Serial.println ("Message sent successfully");
}


void ReceiveMessage()
{
  Serial.println ("Receiving Messages...");
  delay (1000);
  SIM900A.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
  Serial.write ("Message Received Successfully");
}