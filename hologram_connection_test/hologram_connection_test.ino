#include <SoftwareSerial.h>
SoftwareSerial GPRS(7, 8); // RX, TX

unsigned long currentTime;
unsigned long startTime;
const unsigned long period = 10000; 

void dataWrite(String toSend, int tDelay = 500){
  GPRS.println(toSend);
  delay(tDelay);
  while(GPRS.available()) 
    Serial.write(GPRS.read());
}

void setupTCP(){
  dataWrite("AT+CREG?");
  dataWrite("AT+CGREG?");
  dataWrite("AT+CMEE=1");
  dataWrite("AT+CGACT?");
  dataWrite("AT+CIPSHUT");
  dataWrite("AT+CSTT=\"hologram\"");      //Set the APN to hologram
  dataWrite("AT+CIICR",1000);
  dataWrite("AT+CIFSR",1000);             //Get conformation of the IP address
  Serial.println("SETUPTCP COMPLETE");
}


void sendData(int data){
  dataWrite("AT+CIPSTART=\"TCP\",\"cloudsocket.hologram.io\",\"9999\"",5000);
  dataWrite("AT+CIPSEND",100);
  dataWrite("{\"k\":\"nEPN%q2_\",\"d\":\"" + String(data) + "\",\"t\":\"data\"}",100);
  GPRS.write(0x1a);
  delay(1000);
  while(GPRS.available()) 
    Serial.write(GPRS.read());
}

void setup() {
  GPRS.begin(19200);
  Serial.begin(19200);
  delay(500);
  startTime = millis();
  setupTCP();
//  sendData(105);
//  Serial.write("LETS GO");
}

void loop() {
  currentTime = millis();
  if( currentTime - startTime >= period){
    sendData(9000);
  }

//  while(GPRS.available()) 
//    Serial.write(GPRS.read());
//  while (Serial.available()) {
//    byte b = Serial.read();
//    if (b == '*')
//      GPRS.write(0x1a);
//    else
//      GPRS.write(b);
//      GPRS.write(Serial.read());
//  }

}
