// https://randomnerdtutorials.com/sim900-gsm-gprs-shield-arduino/

#include <SoftwareSerial.h>

String inData = "";

// Configure software serial port
SoftwareSerial SIM900(7, 8); 

void dataWrite(String toSend, int tDelay = 500) {
  SIM900.println(toSend);
  delay(tDelay);

  while (SIM900.available()){
     inData = SIM900.readStringUntil('\n');
     if(inData == "10.59.8.243\r"){
        Serial.println("SetupTCP Complete");
    }
     Serial.println(inData);
  }
}

void setupTCP() {
    
    dataWrite("AT+CREG?");
    dataWrite("AT+CGREG?");
    dataWrite("AT+CMEE=1");
    dataWrite("AT+CGACT?");
    dataWrite("AT+CIPSHUT");
    dataWrite("AT+CSTT=\"hologram\"");      //Set the APN to hologram
    dataWrite("AT+CIICR", 1000);
    dataWrite("AT+CIFSR", 1000);            //Get confirmation of the IP address
    delay(1000);
}

void setup() {
  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
  SIM900.begin(19200);
  delay(1000);
  Serial.begin(19200);
  delay(1000);
  setupTCP();
  delay(1000);  
    // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
  
  // Give time to your GSM shield log on to network
  delay(1000);   
  
  // Send the SMS
  sendSMS("Hello World!");
}

void loop() { 
  if(Serial.available() >0){
    inData = Serial.readStringUntil('\r');
    Serial.println("Text to send is: " + inData);
    sendSMS(inData);
  }
  
  while(SIM900.available() >0) {
    inData = SIM900.readStringUntil('\n');
    delay(30);
    Serial.println("Received Message is: " + inData);
    if(inData == "Mode 1\r"){
      Serial.println("Mode Set to: Manual Pump Control");
    }
  }
}

void sendSMS(String inData) {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  // +1 is US code not +01
  dataWrite("AT + CMGS = \"+1XXXXXXXXXX\""); //"AT + CMGS = \"+XXXXXXXXXXXX\"" 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  dataWrite(inData); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000);
  inData = ""; 
}
