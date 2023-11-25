#include "DHT.h"
DHT dht;
#include <Servo.h>
Servo servo;
int angle = 10;
const int vent = 3; 
const int sensor_pin = A0;	
#define SIGNAL_PIN A1
const int pump = 2;  
int suv_value = 0; 
float namlik_natija;
int namlik;
int x1 = 20, x2 = 40, x3 = x2 - 5;
int y1 = 40, y2 = 60, y3 = y2 - 5;
int c1 = 27, c2 = 25;
int a1 = 80;
void setup()
{
  Serial.begin(9600);
  dht.setup(8); 	
  pinMode(vent, OUTPUT);
  pinMode(pump, OUTPUT);
  servo.attach(7);
  servo.write(angle);
}

void loop()
{ 
  delay(dht.getMinimumSamplingPeriod());	
  float humidity = dht.getHumidity();	   
  float temperature = dht.getTemperature();
  suv_value = analogRead(SIGNAL_PIN);
  namlik = analogRead(sensor_pin);
  namlik_natija = ( 100 - ( (namlik/1023.00) * 100 ) );
  Serial.print("temperature =");
  Serial.print(temperature);
  Serial.print("C\t\t");
  Serial.print("Havo namligi =");
  Serial.print(humidity);
  Serial.print("%\t\t");
  Serial.print("Tuproq namligi =");
  Serial.print(namlik_natija);
  Serial.print("%\n");
  delay(1000);

  if(namlik_natija < x1 and humidity > y1 and humidity < y2){
    for(angle = 10; angle <180; angle++)  
    {                                  
      servo.write(angle);               
      delay(10);                   
    }
    Serial.println("Tomchilab sug'orish boshlandi ");  // tomchilab surog'ish uchun
  }
  else {
    if(humidity < y1){
      for(angle = 10; angle < 180; angle++)  
      {                                  
        servo.write(angle);               
        delay(10);                   
      }
       Serial.println("Yomg'ir usulida sug'orish boshlandi ");    // yomg'ir bilan surog'ish uchun
    }
  }
  if(namlik_natija > x3){
    for(angle = 180; angle > 10; angle--)    
    {                                
      servo.write(angle);           
      delay(10);       
    }  
    Serial.println("Tomchilab sug'orish tugadi "); // tomchilab surog'ish uchun
  }
  if(humidity > y3){
    for(angle = 180; angle > 10; angle--)    
    {                                
      servo.write(angle);           
      delay(10);       
    } 
    Serial.println("Yomg'ir usulida sug'orish tugadi ");   // yomg'ir bilan surog'ish uchun
  }
  if(temperature > c1){
    digitalWrite(vent, HIGH); 
    digitalWrite(pump, HIGH); 
    Serial.println("Nasos va Ventilyator ishlashi boshlandi");
  }
  if(temperature < c2){
    digitalWrite(vent, LOW); 
    digitalWrite(pump, LOW); 
    Serial.println("Nasos va Ventilyator ishlashi boshlandi");
  }
  if(suv_value < 5){
    digitalWrite(pump, HIGH);
    Serial.println("Nasos ishlashi boshlandi");
  }
  if(suv_value > 20){
    digitalWrite(pump, LOW);
    Serial.println("Nasos ishlashi toxtadi");
  }
  
}
