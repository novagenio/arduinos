void setup()
{
 
 pinMode(9, OUTPUT);
 digitalWrite(9, LOW);
 Serial.begin(9600);
}
int sensorValue, activo;
void loop()
{
  
 sensorValue = analogRead(A0);
 Serial.println(sensorValue);
 
 if(sensorValue < 400)
 {
    digitalWrite(9, HIGH);
    activo = 1;
   
 }
 if(sensorValue > 700)
 {
    digitalWrite(9, LOW);
    activo = 1;
   
 }
delay(500); 
}

