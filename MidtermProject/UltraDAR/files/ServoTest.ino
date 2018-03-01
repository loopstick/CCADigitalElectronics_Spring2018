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

Servo servo;
byte servoTrim = 90;

void setup() {
  servo.attach(10);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0) {
    byte inByte = Serial.read();
    if (inByte == '=') {
      servoTrim++;
    }
    else if (inByte == '-') {
      servoTrim--;
    }
    Serial.println(servoTrim);
  }
  servo.write(servoTrim);
  delay(15);
}
