#include <Arduino.h>
#include "pin_config.h"
#include <tcs3200.h> // Include the TCS3200 library

#include <ESP32Servo.h>

#define LED 2

#include <BluetoothSerial.h>


BluetoothSerial SerialBT;

#define num_of_colors 7   // Declares the number of colors the program can recognise (number of calibrated colors)


bool codeRunning = false;

Servo gripper, shoulder, steering, waist; // Create a servo object
int gripperPin = GRIPPER_PICKER;          // Servo control pin
int shoulderPin = GRIPPER_SHOULDER;
int steeringPin = STEERING_SERVO_PIN;
int waistPin = GRIPPER_WAIST;
int minAngle1 = 0;   // Minimum angle
int maxAngle1 = 160; // Maximum angle
int stepDelay = 15;  // Delay between steps (milliseconds)
int minAngle2 = 20;  // Minimum angle
int maxAngle2 = 140;
int IN1 = DC_MOTOR_PIN1;
int IN2 = DC_MOTOR_PIN2;
int en = DC_MOTOR_ENABLE;

bool waitForCommand() {
  if (SerialBT.available()) {                   // Check if any data is available from Bluetooth
    String command = SerialBT.readString();       // Read the incoming command string
    command.trim();                               // Remove any extra whitespace/newline characters
    Serial.println("Received command: " + command);

    if (command == "X") {
      codeRunning = true;                         // Command "X" starts the robot logic
    } else if (command == "Y") {
      codeRunning = false;                        // Command "Y" stops the robot logic
    }
  }
  return codeRunning;
}
void robotDefault()
{
  gripper.attach(gripperPin); // Attaches the servo to the specified pin
  shoulder.attach(shoulderPin);
  steering.attach(steeringPin);
  waist.attach(waistPin);
  Serial.begin(9600); // Initialize serial communication

  steering.write(80);
  gripper.write(120);
  waist.write(90);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ULTRASONIC_TRIGGER_PIN, INPUT);

  SerialBT.begin("Lyncrest Robot"); //Bluetooth device name


}

String detect_color() {
  // distinctRGB[] array declares calibration values for each declared color in distinctColors[] array
  int distinctRGB[num_of_colors][3] = {
      {250, 250, 250}, // White
      {0, 0, 0},       // Black
      {142, 34, 41},   // Red
      {166, 125, 71},  // Yellow
      {35, 55, 38},    // Green
      {150, 50, 43},   // Orange
      {22, 25, 45}     // Blue
  };

  // distinctColors[] array declares values to be returned from closestColor() function if specified color is recognised
  String distinctColors[num_of_colors] = {"white", "black", "red", "yellow", "green", "orange", "blue"};

  int red, green, blue;

  // Initialize the TCS3200 color sensor
  tcs3200 tcs(COLOR_SENSOR_S0, COLOR_SENSOR_S1, COLOR_SENSOR_S2, COLOR_SENSOR_S3, COLOR_SENSOR_OUT);

  // Read RGB values from the sensor
  red = tcs.colorRead('r');   // Reads color value for red
  green = tcs.colorRead('g'); // Reads color value for green
  blue = tcs.colorRead('b');  // Reads color value for blue

  Serial.print("R= ");
  Serial.print(red);
  Serial.print("    ");
  Serial.print("G= ");
  Serial.print(green);
  Serial.print("    ");
  Serial.print("B= ");
  Serial.print(blue);
  Serial.println();

  // Find the closest color
  int minDistance = INT_MAX;
  int closestColorIndex = -1;

  for (int i = 0; i < num_of_colors; i++) {
    int distance = sqrt(
        pow(red - distinctRGB[i][0], 2) +
        pow(green - distinctRGB[i][1], 2) +
        pow(blue - distinctRGB[i][2], 2));

    if (distance < minDistance) {
      minDistance = distance;
      closestColorIndex = i;
    }
  }

  // Return the name of the closest color
  if (closestColorIndex != -1) {
    return distinctColors[closestColorIndex];
  } else {
    return "unknown";
  }
}
int detect_distance_in_cm()
{

  // Variables for distance calculation
  const int maxDistance = 80; // Maximum detection range in cm
  const int minDistance = 3;  // Minimum detection range in cm

  int sensorValue = analogRead(ULTRASONIC_TRIGGER_PIN);

  // Map the analog value to a distance (in cm)
  int distance = map(sensorValue, 0, 4095, maxDistance, minDistance);

  // Print the distance to the Serial Monitor
  return distance;
}
void open_gripper()
{
  // Sweep from min to max
  Serial.println("Sweeping from min to max");
  for (int angle = minAngle1; angle <= maxAngle1; angle++)
  {
    gripper.write(angle);
    delay(stepDelay);
  }

  delay(500); // Pause at max position
}
void close_gripper()
{
  // Sweep from max to min
  Serial.println("Sweeping from max to min");
  for (int angle = maxAngle1; angle >= minAngle1; angle--)
  {
    gripper.write(angle);
    delay(stepDelay);
  }

  delay(500); // Pause at min position
}
void extender_up(int step = 2)
{
  Serial.println("Sweeping from max to min");
  for (int angle = maxAngle2; angle >= minAngle2; angle -= step)
  {
    shoulder.write(angle);
    delay(stepDelay);
  }

  delay(500);
}
void waist_turn(int target, int step = 2)
{
  // Sweep from min to max
  Serial.println("Sweeping from min to max");
  for (int angle = 0; angle <= target; angle += step)
  {
    waist.write(angle);
    delay(stepDelay);
  }

  delay(500); // Pause at max position

  // Sweep from max to min
  // Pause at min position
}
void extender_down(int step = 2)
{
  // Sweep from min to max
  Serial.println("Sweeping from min to max");
  for (int angle = minAngle1; angle <= maxAngle1; angle += step)
  {
    shoulder.write(angle);
    delay(stepDelay);
  }

  delay(500); // Pause at max position

  // Sweep from max to min
  // Pause at min position
}
void pickblock_and_lift()
{
  open_gripper();
  delay(1000);
  extender_down();
  delay(1000);
  close_gripper();
  delay(1000);
  extender_up();
  delay(1000);
}
void motor_forward(int speed = 150)
{
  analogWrite(en, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}
void motor_backward(int speed = 150)
{
  analogWrite(en, speed);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN1, LOW);
}
void steering_turn_left(int angle = 30)
{
  steering.write(angle);
  delay(300);
}
void steering_turn_right(int angle = 115)
{
  steering.write(angle);
  delay(300);
}
void motor_stop()
{
  analogWrite(en, 150);
  digitalWrite(IN2, LOW);
  digitalWrite(IN1, LOW);
}
void setup()
{
  robotDefault();
}
void loop()
{
  // put your main code here, to run repeatedly:

    // Your robot logic goes here

}