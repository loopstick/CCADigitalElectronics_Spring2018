void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);       // initialize serial communications
pinMode (8, OUTPUT);
pinMode (12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

   // get a sensor reading:
   int sensorReading = analogRead(A0);

   //if the sensor is in full light -play nothing!
   if (sensorReading <= 650){
    digitalWrite(12, HIGH);
   // map the results from the sensor reading's range
   // to the desired pitch range:
   float frequency = map(sensorReading, 10, 700, 50, 1000);
   // change the pitch, play for 10 ms:
   tone(8, frequency, 30);
   } else {
    digitalWrite(12, LOW);
   }
   
}
