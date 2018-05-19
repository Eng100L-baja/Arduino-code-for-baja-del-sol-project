// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

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

/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the Dallas library
  Dallas.begin();

  // setup the pin for pump
  pinMode(relay_switch, OUTPUT);
}

/*
 * Main function, get and show the temperature
 */
void loop(void)
{ 
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

  delay(2000);
  
}
