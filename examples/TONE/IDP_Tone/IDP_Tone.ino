void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);       // initialize serial communications
}

void loop() {
  // put your main code here, to run repeatedly:

   // get a sensor reading:
   int sensorReading = analogRead(A0);
   // map the results from the sensor reading's range
   // to the desired pitch range:
   float frequency = map(sensorReading, 1, 900, 100, 1000);
   // change the pitch, play for 10 ms:
   tone(8, frequency, 3);
}
