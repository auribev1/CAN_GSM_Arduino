#include <SoftwareSerial.h>
SoftwareSerial myserial(9,8); // RX: 9, TX:8
#include <ArduinoJson.h> //Version 5
StaticJsonBuffer<200> jsonBuffer; //Buffer del Json

void setup() {
    Serial.begin(9600); //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
    Serial.println("Initializing..........");
    myserial.begin(9600);         //Begin serial communication with Arduino and SIM800L
    DynamicJsonBuffer jsonBuffer;
}

//SI NO HACE NINGUN PRINT SIGNIFICA QUE NO ENTRO AL WHILE
void loop() {
  
  myserial.listen();
  
  if(myserial.available())
    myserial.read();
   
  myserial.println(F("AT"));
  Serial.println(F("AT"));
  delay(200);
  while (myserial.available() != 0)
    myserial.read();
  delay(1000);
  
  myserial.println(F("AT+CMEE=1"));
  Serial.print(F("AT+CMEE=1"));
  delay(200);
  while (myserial.available() != 0)
    myserial.read();
  delay(1);

  myserial.println(F("AT+CSQ"));
  Serial.print(F("AT+CSQ"));
  delay(200);
  while (myserial.available() != 0)
    myserial.read();
  delay(1);

  myserial.println(F("AT+SAPBR=3,1,\"Contype\",\"GPRS\""));
  Serial.print(F("AT+SAPBR=3,1,\"Contype\",\"GPRS\""));
  delay(200);
  while (myserial.available() != 0)
    myserial.read();
  delay(1);

  myserial.println(F("AT+SAPBR=3,1,\"APN\",\"internet.comcel.com.co\""));//APN
  Serial.print(F("AT+SAPBR=3,1,\"APN\",\"internet.comcel.com.co\""));
  delay(200);
  while (myserial.available() != 0)
    myserial.read();
  delay(1);

  myserial.println(F("AT+CREG?"));
  Serial.print(F("AT+CREG?"));
  delay(200);
    while (myserial.available() != 0)
      myserial.read();
  delay(1);

  myserial.println(F("AT+CGREG?"));
  Serial.print(F("AT+CGREG?"));
  delay(200);
    while (myserial.available() != 0)
      myserial.read();
  delay(1);

  myserial.println(F("AT+SAPBR=1,1"));
  Serial.print(F("AT+SAPBR=1,1"));
  delay(200);
   while (myserial.available() != 0)
    myserial.read();
  delay(1);

  myserial.println(F("AT+SAPBR=2,1"));
  Serial.print(F("AT+SAPBR=2,1"));
  delay(200);
   while (myserial.available() != 0)
    myserial.read();
  delay(1);

  myserial.println(F("AT+HTTPINIT"));
  Serial.print(F("AT+HTTPINIT"));
  delay(200);
  while (myserial.available() != 0)
    myserial.read();
  delay(1);

  myserial.println(F("AT+HTTPPARA=\"CID\",1"));
  Serial.print(F("AT+HTTPPARA=\"CID\",1"));
  delay(200);
  while (myserial.available() != 0)
    myserial.read();
  delay(1);

  //StaticJsonBuffer<110> jsonBuffer;
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& object = jsonBuffer.createObject();

  object.set("Prueba", "Prueba");

  object.printTo(Serial);
  Serial.println(F(" "));
  String sendtoserver;
  object.prettyPrintTo(sendtoserver);
  delay(20);

  myserial.println(F("AT+HTTPPARA=\"URL\",\"http://servidor-monitoria.herokuapp.com/\"")); //Server address
  Serial.println(F("AT+HTTPPARA=\"URL\",\"http://servidor-monitoria.herokuapp.com/\""));
  delay(20);
   while (myserial.available() != 0)
    myserial.read();
  delay(1);

  myserial.println(F("AT+HTTPPARA=\"CONTENT\",\"application/json\""));
  Serial.println(F("AT+HTTPPARA=\"CONTENT\",\"application/json\""));
  delay(20);
    while (myserial.available() != 0)
    myserial.read();
  delay(1);
  
  myserial.println("AT+HTTPDATA=" + String(sendtoserver.length()) + ",100000");
  Serial.println("AT+HTTPDATA=" + String(sendtoserver.length()) + ",100000");
  Serial.println(sendtoserver);
  delay(20);
   while (myserial.available() != 0)
    myserial.read();
  delay(1);

  myserial.println(sendtoserver);
  delay(20);
  while (myserial.available() != 0)
    myserial.read();
  delay(1);

  myserial.println(F("AT+HTTPACTION=1"));
  Serial.println(F("AT+HTTPACTION=1"));
  delay(20);
    while (myserial.available() != 0)
      myserial.read();
  delay(1);

  myserial.println(F("AT+HTTPREAD"));
  Serial.println(F("AT+HTTPREAD"));
  delay(20);
   while (myserial.available() != 0)
    myserial.read();
  delay(1);
  myserial.println(F("AT+HTTPTERM"));
  Serial.println(F("AT+HTTPTERM"));
  delay(1);
    while (myserial.available() != 0)
      myserial.read();
  delay(1);
}
