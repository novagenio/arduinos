/* Prueba del Puente H (L293D) 
Dibujo de las conexiones en www.elprofegarcia.com

ARDUINO   L293D(Puente H)        
  5          10
  6          15
  9          7
  10         2
  5V         1, 9, 16
  GND        4, 5, 12, 13
  
  El motor 1 se conecta a los pines 3 y 6 del Puente H
  El motor 2 se conecta a los pines 11 y 14 del Puente H
  
  La fuente de alimentacion de los Motores se conecta a tierra y
  el positivo al pin 8 del puennte H.  

*/
int dere = 9; 
int izqu = 10; 
int atra = 5; 
int adel = 6; 
int vel = 255; // Velocidad de los motores (0-255)

void setup()  { 
  pinMode(izqu, OUTPUT);
  pinMode(dere, OUTPUT);
  pinMode(adel, OUTPUT);
  pinMode(atra, OUTPUT);
 } 
 
void loop()  { 
analogWrite(adel, vel);
delay(2000);
analogWrite(adel, 150);
delay(2000);
}    
    
