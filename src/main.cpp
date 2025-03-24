#include <Arduino.h>

#include <ESP32Servo.h>

Servo gripper,shoulder,steering, waist;      // Create a servo object
int gripperPin = 26;   // Servo control pin
int shoulderPin =25;
int steeringPin = 27;
int waistPin = 32;
int minAngle1 = 0;   // Minimum angle
int maxAngle1 = 160; // Maximum angle
int stepDelay = 15; // Delay between steps (milliseconds)
int minAngle2 = 20;   // Minimum angle
int maxAngle2 = 140;
int IN1= 22;
int IN2 =23;
int en=21;

void robotDefault(){
  gripper.attach(gripperPin);  // Attaches the servo to the specified pin
  shoulder.attach(shoulderPin);
  steering.attach(steeringPin);
  waist.attach(waistPin);
  Serial.begin(9600);        // Initialize serial communication

  steering.write(80);
  gripper.write(120);
  waist.write(90);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
}

void setup() {
  robotDefault();

}

void open() {
  // Sweep from min to max
  Serial.println("Sweeping from min to max");
  for (int angle = minAngle1; angle <= maxAngle1; angle++) {
    gripper.write(angle);
    delay(stepDelay);
  }
  
  delay(500);  // Pause at max position
}
void close(){ 
  // Sweep from max to min
  Serial.println("Sweeping from max to min");
  for (int angle = maxAngle1; angle >= minAngle1; angle--) {
    gripper.write(angle);
    delay(stepDelay);
  }
  
  delay(500);  // Pause at min position
}
void extender_up(int step =2) {
  Serial.println("Sweeping from max to min");
  for (int angle = maxAngle2; angle >= minAngle2; angle-= step) {
   shoulder.write(angle);
    delay(stepDelay);
  }
  
  delay(500);
}
void waist_turn(int target, int step = 2 ){
  // Sweep from min to max
  Serial.println("Sweeping from min to max");
  for (int angle = 0; angle <= target; angle += step) {
    waist.write(angle);
    delay(stepDelay);
  } 
  
  delay(500);  // Pause at max position
  
  // Sweep from max to min
    // Pause at min position
}
void extender_down(int step = 2) { 
  // Sweep from min to max
  Serial.println("Sweeping from min to max");
  for (int angle = minAngle1; angle <= maxAngle1; angle += step) {
    shoulder.write(angle);
    delay(stepDelay);
  }
  
  delay(500);  // Pause at max position
  
  // Sweep from max to min
    // Pause at min position
}
void pickblock_drop(){
  open();
  delay(1000);
  extender_down();
  delay(1000);
  close();
  delay(1000);
  extender_up();
  delay(1000);
}
void forward(int speed = 150){
analogWrite(en,speed);
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
}
void backward(int speed = 150){
  analogWrite(en,speed);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN1,LOW);
  }

void stop(){
    analogWrite(en,150);
    digitalWrite(IN2,LOW);
    digitalWrite(IN1,LOW);
}
void loop(){
 forward();
 delay(1000);
 backward();
 delay(500);
 stop();
  delay(2000);
  extender_down();
  delay(500);
  open();
  delay(200);
  close();
  delay(500);
  extender_up();
  delay(500);
  open();
  delay(500);



}