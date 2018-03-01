/*
 * UltraDAR Single Sweep
 * 
 * Example code for fully autonomous travel of a servo driven
 * two-wheeled robot. Sensing is accomplished using a single
 * HC-SR04 ultrasonic sensor that is continuously scanned
 * 180 degrees by means of a micro servo. Proximity data is
 * continuously streamed to the arduino and a decision is made
 * based on the angle of the furthest distance. The robot will
 * either drive forward, if the farthest distance is straight
 * ahead or will make small adjustments to its relative position
 * until the farthest distance is straight ahead. Only then
 * will the robot move forward and the process repeats.
 * 
 * Written by Adam Kemp, 2017
 * 
 */

#include <Servo.h> //The Servo library is used to control the two drive servos and single sweep servo
#include <Ultrasonic.h> //Erick Simões' ultrasonic library is used for single wire control of an HC-SR04 ultrasonic sensor (https://github.com/ErickSimoes/Ultrasonic)

Servo sweep; //Declare our servo names
Servo left;
Servo right;

Ultrasonic ultrasonic1(13); //Declare and attach the modified HC-SR04
//***Modify an HC-SR04 by soldering the Trig and Echo pins together. This will let you drive the sensor with a single servo type cable.

#define leftCenter 88 //Software center position for the left servo. Use the "ServoTest" program to determine this midpoint 
#define rightCenter 92 //Software center posistion for the right servo.

#define leftTurnTime 20 //Amount of delay used for adjustment turns. In ms.
#define rightTurnTime 20 
#define reverseTime 100
#define reverseThreshold 10 //Threshold for triggering a reverse situation. In cm.

#define maxSweepAngle 180 //Maximum angle for the sensor to sweep. 180 = 0 to 180 degrees.
#define sampleAngle 45 //Angle at which each measurement is taken. In degrees.
#define servoSweepDelay 50 //Delay required for servo to reach its setpoint. Adjust for maximum sweep speed.
#define sampleDelay 0 //Delay added to each distance measurement. Shouldn't be needed. In ms.
#define numSamples 20 //Quantity of measurements averaged at each angle. More provides a more accurate measurement, but slower sweeping.

boolean reverse = false; //Flag set when an reverse situation is detected.

void setup() {
  Serial.begin(9600); //Initialize the serial port for debugging
  sweep.attach(11); //Attach sensor sweep servo to D11
  left.attach(10); //Attach left drive servo to D10
  right.attach(9); //Attach right drive servo to D9
  left.write(leftCenter); //Center each servo
  right.write(rightCenter);
  sweep.write(0); //Home the sensor sweep servo
  delay(1000); //Wait until the sensor sweep servo reaches its start position
}

void loop() {
  drive(sense()); //Drive function is controlled by the sense function
}

int sense() {
  int ultra1Read, ultra1Max, ultra1Angle; //Variables used to calculate the angle with the longest distance
  long ultra1Avg;
  
  for (int i = 0; i <= maxSweepAngle; i += sampleAngle){ //Samples each angle and returns the one with the longest distance
    sweep.write(i);
    delay(servoSweepDelay);
    for (int j = 0; j < numSamples; j++){
      int reading = ultrasonic1.distanceRead();
      ultra1Avg += reading;
      delay(sampleDelay);
    }
    ultra1Read = ultra1Avg/numSamples;
    Serial.print(i);
    Serial.print("-");
    Serial.print(ultra1Read);
    Serial.print(", ");
    if (ultra1Read >= ultra1Max) { //check for max distance
      ultra1Max = ultra1Read;
      ultra1Angle = i;
      if (ultra1Angle == 90 & ultra1Read <= reverseThreshold){
        reverse = true;
      }
    }
    ultra1Avg = 0;
    ultra1Read = 0;
  }
  Serial.print("max = ");
  Serial.print(ultra1Angle);
  Serial.println();
  for (int i = 180; i >= 0; i -= sampleAngle) { //Returns the sweep servo to its start position
    sweep.write(i);
    delay(servoSweepDelay);
  }
  
  if (ultra1Angle == 90) { //Determines if the robot drives forward or reverses
    if (reverse) {
      reverse = false;
      return(255);
    }
    else {
      return(90);
    }
  }
  else { //Returns the angle with the longest distance
    return(ultra1Angle);
  }
}

void drive(int _objectAngle){
  int leftVal = leftCenter; //Variables for the servo pulse value
  int rightVal = rightCenter;
  
  if (_objectAngle == 90) {
    Serial.println("Forward");
    leftVal = 0;
    rightVal = 180;
  }
  else if (_objectAngle == 255) {
    Serial.println("Backward");
    leftVal = 180;
    rightVal = 0;
    left.write(leftVal);
    right.write(rightVal);
    delay(reverseTime);
    leftVal = leftCenter;
    rightVal = rightCenter;
  }
  //turn right
  else if (_objectAngle >= 90) {
    Serial.print("Left: ");
    leftVal = leftCenter + 45;
    rightVal = rightCenter + 45;
    left.write(leftVal);
    right.write(rightVal);
    delay(rightTurnTime*((_objectAngle/sampleAngle)-((180*.5)/sampleAngle))); //Calculation determines the amount of time to turn based on the angle's distance from center
    Serial.print(rightTurnTime*((_objectAngle/sampleAngle)-((180*.5)/sampleAngle)));
    Serial.println("ms");
    leftVal = leftCenter;
    rightVal = rightCenter;
  }
  else if (_objectAngle <= 90) {
    Serial.print("Right: ");
    leftVal = leftCenter - 45;
    rightVal = rightCenter - 45;
    left.write(leftVal);
    right.write(rightVal);
    delay(rightTurnTime*(((180*.5)/sampleAngle)-(_objectAngle/sampleAngle)));
    Serial.print(rightTurnTime*(((180*.5)/sampleAngle)-(_objectAngle/sampleAngle)));
    Serial.println("ms");
    leftVal = leftCenter;
    rightVal = rightCenter;
  }
  left.write(leftVal);
  right.write(rightVal);
  delay(15);
}

