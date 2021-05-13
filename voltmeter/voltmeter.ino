int volt ;
float voltage;

void setup()
{
Serial.begin(9600);
}

void loop() 
{
  volt= analogRead(A0);
  voltage =volt*(5.0 * 11/1023);
  Serial.print("Voltage = ");
  Serial.print(voltage);
  Serial.println("V");
  delay(1000);
}
