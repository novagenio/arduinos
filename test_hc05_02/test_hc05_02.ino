
#include <SoftwareSerial.h>
#define BT_RT 10
#define BT_TX 11
#define BTVCC 12
#define BTKEY 13

SoftwareSerial Bluetooth(BT_TX, BT_RT); // RX, TX


void setup() {
  Serial.begin(9600);
  pinMode(BTVCC, OUTPUT);                         // Marca el PIN de alimentacion para el HC-05 como salida
  pinMode(BTKEY, OUTPUT);                          // Marca el PIN del modo AT para el HC-05 como salida
  digitalWrite(BTKEY, HIGH);                         // Activa el modo AT Full
  delay (500) ;                                           // Espera antes de encender el modulo
  Serial.println("Alimentando el modulo HC-05");
  digitalWrite (BTVCC, HIGH);                       // Enciende el modulo
  //delay(600); digitalWrite (BTKEY, LOW);      // Cambia al modo AT Mini
  Serial.println("Esperando comandos AT:");
  Bluetooth.begin(38400); 
}

void loop(){
  if (Bluetooth.available()){ Serial.write(Bluetooth.read()); }
  if (Serial.available()){ Bluetooth.write(Serial.read()); }
}
