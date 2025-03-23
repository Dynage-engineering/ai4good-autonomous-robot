#include <Arduino.h>
#include <L298N.h>
#include <ESP32Servo.h>
#include <tcs3200.h>
#include "pin_config.h"


//  Color Sensor
#include <tcs3200.h>

int red, green, blue, white;

tcs3200 tcs(18, 5, 17, 4, 16); // (S0, S1, S2, S3, output pin)


//  Motor Pin definition
const unsigned int MOTOR_IN1 = DC_MOTOR_PIN1;
const unsigned int MOTOR_IN2 = DC_MOTOR_PIN2;
const unsigned int MOTOR_EN = DC_MOTOR_ENABLE;

// Create one rearMotor instance.
L298N rearMotor(MOTOR_EN, MOTOR_IN1, MOTOR_IN2);


// Servo
Servo steering;
Servo gripper;
Servo elbow;
Servo shoulder;
Servo waist;

int steeringPin = STEERING_SERVO_PIN;
int gripperPin = GRIPPER_PICKER;
int elbowPin = GRIPPER_ELBOW;
int shoulderPin = GRIPPER_SHOULDER;
int waistPin = GRIPPER_SHOULDER;


#define LED 2


void printSomeInfo();

void pickBlock();

void dropBlock();

void setup()
{
  // Used to display information
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(ULTRASONIC_TRIGGER_PIN,INPUT);
  steering.attach(steeringPin);
  gripper.attach(gripperPin);
  elbow.attach(elbowPin);
  shoulder.attach(shoulderPin);
  waist.attach(waistPin);

  // Wait for Serial Monitor to be opened
  while (!Serial)
  {
    //do nothing
  }

  //  initial speed and Position
  rearMotor.setSpeed(150);
  Serial.println("Moving servos to initial positions...");
  steering.write(85);  // Move steering servo to 80 degrees
  gripper.write(120);   // Move gripper servo to 120 degrees
  // elbow.write(0);    // Move elbow servo to 120 degrees
  shoulder.write(90);  // Move shoulder servo to 60 degrees
  waist.write(90);     // Move waist servo to 90 degrees
}

void loop()
{
  digitalWrite(LED, HIGH);
  delay(00);
  digitalWrite(LED, LOW);
  delay(500);
  printSomeInfo();


  rearMotor.forward();
  delay(200);
  pickBlock();
  delay(300);
  rearMotor.backward();
  delay(500);
  steering.write(30);
  rearMotor.forward();
  dropBlock();
  rearMotor.stop();
  delay(1000);
  printSomeInfo();
  rearMotor.setSpeed(0);
}

/*
Print some informations in Serial Monitor
*/
void detect_Obstacle(){
if (digitalRead(ULTRASONIC_TRIGGER_PIN)==HIGH;){
  rearMotor.stop();
  delay(500);
  rearMotor.backward();
  delay(500);
  rearMotor.stop();
  delay(200);

}
}
void pickBlock()
  {
    // pick an item
    waist.write(0);
    delay(500);
    shoulder.write(180);
    delay(500);
    gripper.write(0);
    delay(500);
  }

  void dropBlock(){
    // drop an item
    shoulder.write(90); // raise item
    delay(500);
    gripper.write(120); // open gripper
    delay(500);
  
  }
  void printSomeInfo()
{
  Serial.print("rearMotor is moving = ");
  Serial.print(rearMotor.isMoving());
  Serial.print(" at speed = ");
  Serial.println(rearMotor.getSpeed());
  Serial.print("Servo is moving = ");
  Serial.print(steering.read());
  Serial.print(" at speed = ");
  Serial.println(steering.readTicks());
}