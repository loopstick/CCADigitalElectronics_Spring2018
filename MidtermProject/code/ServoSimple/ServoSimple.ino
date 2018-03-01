/*
 * Servo Test and Calibration
 * 
 * This code can be used to center and calibrate continuous rotation servos.
 * Upload the code and use the serial monitor to send "=" and "-" characters
 * which in turn adjust the servo output value. The value reported can then
 * be used to determine the software midpoint for the servo.
 * 
 * Written by Adam Kemp, 2017
 * 
 */

#include <Servo.h>
//include the library file which has all the necessary functions for controlling servo motors

Servo servo;
byte servoTrim = 0;

void setup() {
  servo.attach(11);
  Serial.begin(9600);
}

void loop() {
  Serial.println(servoTrim);
  servo.attach(11);
  servo.write(90);
  delay(1000);
  servo.detach();
//delay(1000);
  //servo.attach(5);
  //servo.write(180);
  //delay(1000);
delay(1000);
}
