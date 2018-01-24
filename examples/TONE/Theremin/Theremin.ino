/* A very simple example 
  showing how to use the tone() and analogRead() functions to play a tone whose pitch depends on the value
  read from an analog input.
   
   1/25/17 - Michael Shiloh - Initial creation
   Pin usage:
   8 - a piezo transducer or other speaker
   A0 - an analog sensor of some sort
*/

void setup() {
  pinMode (8, OUTPUT); // not strictly necessary, but for clarity   
  pinMode (A0, INPUT);  // not strictly necessary, but for clarity 
}

void loop() {
  // Read the sensor and immediately set the tone to that pitch
  tone (8, analogRead(A0));
  delay(1);
}
