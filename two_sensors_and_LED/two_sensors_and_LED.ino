// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define water_in 2
#define water_out 4
int relay_switch = 10;
float temp_in;
float temp_out;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire_1(water_in);
OneWire oneWire_2(water_out);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensor_1(&oneWire_1);
DallasTemperature sensor_2(&oneWire_2);

/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensor_1.begin();
  sensor_2.begin();

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

  // Send the command to get temperatures
  sensor_1.requestTemperatures();
  sensor_2.requestTemperatures();
  Serial.println("DONE");

  temp_in = sensor_1.getTempCByIndex(0);
  temp_out = sensor_2.getTempCByIndex(0);
  
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
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
