#include <Servo.h>

Servo myservo;  

int trigPin = 7;    
int echoPin = 6;
int servoPin = 9;  
int sensorPin = A0; 
int sensorValue;  
int limit = 10; 
int pos = 0;    // variable to store the servo position
long dist , duration;

void setup() {
 Serial.begin(5000);
 myservo.attach(servoPin);  
 pinMode(trigPin, OUTPUT);  
 pinMode(echoPin, INPUT);  
 myservo.write(0); // Rest position of the separation comp in the middle
 delay(15); // delay of 15ms 
 myservo.detach();
}
void measure() {  

digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(15);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
dist = (duration/2) / 29.1;    //obtain distance
}

void loop() {

 sensorValue = analogRead(sensorPin); 
 Serial.println(sensorValue);
 measure();
 myservo.attach(servoPin);
 myservo.write(90);
 delay(15);
 if(dist<20) { 

    if (sensorValue<=limit) 
    {   
      myservo.write(90);
      delay(1500);  // waits 15ms for the servo to reach the position
      myservo.write(0);   
      delay(3000); 
      Serial.println("Dry Waste Present");  
     }
     else 
     {
      myservo.write(90);
      delay(1500);
      myservo.write(160);
      delay(3000);
      Serial.println("Wet Waste Present");
     }
 myservo.write(90);
 delay(1000); 
}
else {
  Serial.println("NO OBJECT OR SUBSTANCE FOUND");
}
}
 

 
