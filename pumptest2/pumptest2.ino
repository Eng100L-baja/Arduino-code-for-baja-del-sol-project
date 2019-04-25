// Baja Team Controls Subteam
// Control system for Solar Water Heater
// It turns on/off the pump based on temperature

//int water_in = 1;                 //hot water goes to pin 1
//int  water_out = 2;                //cold water goes to pin 2

const int relay_switch = 10;               //pump out from pin 10

void setup() {
//  pinMode(water_in, INPUT);             //define pin 1 as input
//  pinMode(water_out, INPUT);            //defin pin 2 as input
  pinMode(relay_switch, OUTPUT);        // define pump as output
  Serial.begin(9600);                   // speed of information being passed (baud rate)
  
}

void loop() {

  digitalWrite(relay_switch, LOW);
  Serial.println("Pump Off");
  delay(2000);

  digitalWrite(relay_switch, HIGH);
  Serial.println("Pump On");
  delay(1000);




//int  water_in_read = analogRead(water_in);     //water in temperature reading
//int  water_out_read = analogRead(water_out);   //water out temperature reading
//  
//  if (water_out_read > water_in_read){
//    digitalWrite(relay_switch,HIGH);
//    }
//  else if (water_out_read < 0.8*water_in_read) {
//      digitalWrite(relay_switch,LOW);
//      }
//  else  {
//          delay(600000);
//          if (water_out_read <= water_in_read) {
//            digitalWrite(relay_switch,LOW);
//          }
//          else {
//            digitalWrite(relay_switch,HIGH);
//          }
//  }
 }
