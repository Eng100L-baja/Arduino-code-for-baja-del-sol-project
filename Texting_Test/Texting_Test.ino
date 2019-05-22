#include <SoftwareSerial.h>

String inData = "";

// Configure software serial port
SoftwareSerial SIM900(7, 8); 

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
  
  // Give time to your GSM shield log on to network
  delay(20000);   
  
  // Send the SMS
  sendSMS();
}

void loop() { 
  while(SIM900.available() >0) {
    inData = SIM900.readStringUntil('\n');
    delay(30);
    Serial.println("Received Message is: " + inData);
  }
}

void sendSMS() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+016262154064\""); //"AT + CMGS = \"+XXXXXXXXXXXX\"" 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Hello World!"); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
}
