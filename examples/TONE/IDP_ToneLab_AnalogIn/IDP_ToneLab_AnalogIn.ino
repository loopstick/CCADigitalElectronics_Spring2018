void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);       // initialize serial communications
}
 
void loop()
{
  int analogValue = analogRead(A0); // read the analog input
  Serial.println(analogValue);      // print it
}
