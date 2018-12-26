#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

void setup()
{
  pinMode(13, OUTPUT);    // Vamos usar LED onboard como sinalizador de comunicación
  pinMode(9, OUTPUT);     // Pino para acionar el modo de configuracao (pino KEY del módulo)
  digitalWrite(9, HIGH);  // Ativar modo de configuracao para aceitar comandos Hayes
  Serial.begin(38400);
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
  delay(1000);
  Serial.println("Entre con Comandos Hayes: ");
}

void loop()
{

  // Leia la salida del HC-05 and envie al Monitor Serial del Arduino 
  if (BTSerial.available()){
    digitalWrite(13, HIGH);
    Serial.write(BTSerial.read());
    digitalWrite(13, LOW);
  }

  // Leia el que  fue  digitado en el Monitor Serial del Arduino y envie al HC-05
  if (Serial.available()){
      Serial.println(Serial.read());
    digitalWrite(13, HIGH);
    BTSerial.write(Serial.read());
    digitalWrite(13, LOW);
  }
}
