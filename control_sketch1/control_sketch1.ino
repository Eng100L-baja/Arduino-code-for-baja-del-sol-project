// Baja Team Controls Subteam
// Control system for Solar Water Heater
// It turns on/off the pump based on temperature

#define water_in A1
#define water_out A2

const int relay_switch 10;

void setup() {
  pinMode(water_in, INPUT);
  pinMode(water_out, INPUT);
  pinMode(relay_switch, OUTPUT);

  Serial.begin(9600);
  
}

void loop() {
  in_temp = analogRead(water_in);
  out_temp = analogRead(water_out);
  
  if (out_temp > in_temp)
    digitalWrite(relay_switch,HIGH);
    else if (out_temp < 0.8*in_temp) 
      digitalWrite(relay_switch,LOW);
      else
        delay(600000);
        if (out_temp <= in_temp);
        digitalWrite(relay_switch,LOW);
        else 
        digitalWrite(relay_switch,HIGH);

   delay(600000);
}
