#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

SoftwareSerial GPRS(7, 8); // RX, TX

// All data wire are plugged into port 2 on the Arduino
#define temp_sensors 2
#define relay_switch 10
float temp_in;
float temp_out;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
// call the library oneWire, provide a name to your Onewire devices (we called them "Sajjie")
// and provide the pin number of these "Sajje" devices (our pin number is temp_sensor = 2)
OneWire Sajje(temp_sensors);

// Pass our oneWire reference to Dallas Temperature. 
// call the library oneWire, name your Dallas library (we called them "Dallas")
// and provide the "Sajje" devices reference to Dallas
// The & symbol in a C++ variable declaration means it's a reference. https://en.wikipedia.org/wiki/Reference_%28C%2B%2B%29
DallasTemperature Dallas(&Sajje);

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
  Serial.println("SetupTCP Complete");
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
  delay(1000);
  setupTCP();
  delay(1000);
//  sendData(105);
//  Serial.write("LETS GO");

  // Start up the Dallas library
  Dallas.begin();
  Serial.println("Dallas Temperature Begin");

  // setup the pin for pump
  pinMode(relay_switch, OUTPUT);
}

void loop() {
    // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");

  // Send the command to get temperatures using Dallas Library (same as printing "Done" using the "Serial" library)
  Dallas.requestTemperatures();
  Serial.println("DONE");
  // We use the function ByIndex
  temp_in = Dallas.getTempCByIndex(0);
  temp_out = Dallas.getTempCByIndex(1);
  
  // After we got the temperatures, we can print them here.
  Serial.print("Temperature for water inlet is: ");
  Serial.println(temp_in);  
  Serial.print("Temperature for water outlet is: ");
  Serial.println(temp_out);

  if (temp_out - temp_in > 0){
    Serial.println("turn on the pump.");
    Serial.println(" ");
    digitalWrite(relay_switch,HIGH);
  }
  else {
    Serial.println("turn off the pump.");
    digitalWrite(relay_switch,LOW);
    Serial.println(" ");
  }

  sendData(temp_in);
  delay(10000);

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
