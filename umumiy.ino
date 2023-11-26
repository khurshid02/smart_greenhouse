#include "DHT.h"
DHT dht;
#include <Servo.h>
Servo servo;

int angle = 10;
const int vent = 3; 
const int sensor_pin = A0;	
#define SIGNAL_PIN A1
#define PIN_TRIG 12
#define PIN_ECHO 11
long duration, sath;
const int pump = 2;  
float namlik_natija;
int namlik;

int x1 =    


x1 = 20, x2 = 40, x3 = x2 - 5;
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
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

void loop()
{ 
  delay(dht.getMinimumSamplingPeriod());	
  float humidity = dht.getHumidity();	   
  float temperature = dht.getTemperature();
  namlik = analogRead(sensor_pin);
  namlik_natija = ( 100 - ( (namlik/1023.00) * 100 ) );

  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  duration = pulseIn(PIN_ECHO, HIGH);
  sath = (duration / 2) / 29.1;
  //OLingan natijalrni chiqarish
  //Serial.print("temperature =");
  Serial.print(temperature);
  Serial.print(",");
  //Serial.print("Havo namligi =");
  Serial.print(humidity);
  Serial.print(",");
  //Serial.print("Tuproq namligi =");
  Serial.print(namlik_natija);
  Serial.print(",");
  //Serial.print("Suv miqdori bosh joy = ");
  Serial.print(sath );
  Serial.print(",");
  delay(1000);

 // namliklar bilan ishlash
  if(namlik_natija < x1 and humidity > y1 and humidity < y2){
    tomchi_suv();// tomchilab surog'ish uchun
  }
  else {
    if(namlik_natija > x1 and humidity < y1){
      raining();  // yomg'ir bilan surog'ish uchun
    }
  }
  if(namlik_natija > x3){
    tomchi_suv_end();// tomchilab surog'ish uchun
  }
  if(humidity > y3){
     raining_end(); // yomg'ir bilan surog'ish uchun
  }

 //temperatura bilan ishlash . havo tizimidan suvlarni almashtirish 

  if(temperature > c1 and sath  > 5){
    digitalWrite(vent, HIGH); 
    digitalWrite(pump, HIGH);
    Serial.print("V");//111 vent y 222 nasos y
    Serial.print(",");
    Serial.print("N");
    Serial.print(",");
    //Serial.println("Nasos va Ventilyator ishlashi boshlandi");
  }
  else{
    if(temperature > c1){
      digitalWrite(vent, HIGH);
      digitalWrite(pump, LOW);
      Serial.print("V");
      Serial.print(",");
      Serial.print("n");
      Serial.print(",");
      //Serial.println("Ventilyator ishlashi boshlandi"); 
    }
    else{
      if(sath  > 20 and sath  > 15){
        digitalWrite(pump, HIGH);
        digitalWrite(vent, LOW);
        Serial.print("v");
        Serial.print(",");
        Serial.print("N");
        Serial.print(","); 
        //Serial.println("Nasos ishlashi boshlandi");
      }
    }
  }
  if(temperature < c2){
    digitalWrite(vent, LOW); 
    //Serial.println("Ventilyator ishlashi toxtadi");
    if(sath  < 15){
      digitalWrite(pump, LOW);
      Serial.print("n"); 
      Serial.print(",");
      //Serial.println("Nasos ishlashi toxtadi");
    }
  }
  Serial.println("");
}

void raining(){  // 
  for(angle = 10; angle <180; angle++)  
    {                                  
      servo.write(angle);               
      delay(10);                   
    }
     Serial.print("Y");
      Serial.print(",");
    //Serial.println("Tomchilab sug'orish boshlandi ");
}

void raining_end(){
  for(angle = 180; angle > 10; angle--)    
    {                                
      servo.write(angle);           
      delay(10);       
    }  
     Serial.print("y");
      Serial.print(",");
    //Serial.println("Tomchilab sug'orish tugadi "); 
}

void tomchi_suv(){
  for(angle = 10; angle <180; angle++)  
    {                                  
      servo.write(angle);               
      delay(10);                   
    }
     Serial.print("T");
      Serial.print(",");
    //Serial.println("Tomchilab sug'orish boshlandi ");
}

void tomchi_suv_end(){
  for(angle = 180; angle > 10; angle--)    
    {                                
      servo.write(angle);           
      delay(10);       
    }  
     Serial.print("t");
      Serial.print(",");
    //Serial.println("Tomchilab sug'orish tugadi "); 
}
