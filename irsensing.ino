/******************************************************************************
  QRD1114_Proximity_Example.ino
  Example sketch for SparkFun's QRD1114 Reflectance Proximity Sensor
  (https://www.sparkfun.com/products/246)
  Jim Lindblom @ SparkFun Electronics
  May 2, 2016

  Connect a QRD1114, 330 resistor and 10k resistor as follows:

  QRD1114 Pin ---- Arduino ---- Resistors
    1              A0      10k Pull-up to 5V
    2              GND
    3                      330 Resistor to 5V
    4              GND

  As an object comes closer to the QRD1114, the voltage on A0 should go down.

  Development environment specifics:
  Arduino 1.6.7
******************************************************************************/
//Setup IR sensors
const int LeftIR = A0; // Sensor output voltage
const int RightIR = A1; // Sensor output voltage

//Setup motors and servo
#include <Servo.h>
Servo myservo;

const int motor = 5; //PWM for motor
int in1 = 12;
int slow = 180;
int fast = 180;
int RightTurn = -60; //servo angle for right turn
int LeftTurn = 90; //servo angle for left turn
int Straight = 45; //servo angle for straight

void setup()
{
  Serial.begin(9600);
  pinMode(LeftIR, INPUT);
  pinMode(RightIR, INPUT);

  // sets up servo
  myservo.write(RightTurn); //Sets the servo to
  myservo.attach(11);  // attaches the servo on pin 6 to the servo object
}

void loop()
{
  int average = 0;
  for (int counter = 0; counter < 1000; counter++) {
    int Left = analogRead(LeftIR);
    int Right = analogRead(RightIR);
    average = average + (Left-Right);
    delayMicroseconds(50);
//    Serial.println(counter);
  }
  average = average/1000;
  Serial.println(average);

  if ((average) < -7) //if left IR sensor is over tape
  {
    Serial.println("TurnRight");
    TurnRight();
  }
  else if (average > 8) //if right IR sensor is over tape
  {
    TurnLeft();
    Serial.println("TurnLeft");
  }
  else
  {
    Forward();
    Serial.println("Foreward");
  }

}

void TurnRight() {
  analogWrite(motor, slow);
 
  myservo.write(RightTurn);              // tell servo to go to position 'RightTurn'
  delay(600);
    analogWrite(motor, 0);
   
}

void TurnLeft() {
  analogWrite(motor, slow);
  myservo.write(LeftTurn);              // tell servo to go to position 'RightTurn'
     delay(600);
    analogWrite(motor, 0);
}

void Forward() {
  analogWrite(motor, fast);
  myservo.write(Straight);              // tell servo to go to position 'RightTurn'
   delay(300);
    analogWrite(motor, 0);
}
