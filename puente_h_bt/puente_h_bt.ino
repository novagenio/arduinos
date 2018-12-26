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
int x_adel, x_atra, x_izqu, x_dere = 0;

  
void setup()  { 
  pinMode(izqu, OUTPUT);
  pinMode(dere, OUTPUT);
  pinMode(adel, OUTPUT);
  pinMode(atra, OUTPUT);

  delay(500); // wait for bluetooth module to start
  //Serial1.begin(9600); // Bluetooth default baud is 115200 serial1, solo para arduino mega, uso de bluetooth
  Serial.begin(9600);

 } 
 

void loop() {
lee_cliente_bluetooth();


analogWrite(atra, x_atra);
analogWrite(adel, x_adel);
analogWrite(izqu, x_izqu);
analogWrite(dere, x_dere);

}



    


void lee_cliente_bluetooth()
{
                 if (Serial.available()) {                           // valida que el buffer del server tiene datos enviados por el clinete
                     Serial.println("Bluetooth..........");
                     String req = Serial.readStringUntil('\n');      // lee datos hasta encontrar /n (final de carro
                     
                     Serial.println(req);       // muestra en ehootl serial monitor y el el log del movil lo enviado.
                    
Serial.println(x_adel);
Serial.println(x_atra);
            
                    if( req.indexOf("A")!= -1 ) { // A adelante
                        if (x_atra == vel) {    // si esta en reversa lo deja en stop
                          x_atra = 0;
                          Serial.println("stop");
                        } else {      
                          x_adel = vel;
                          Serial.println("adelante");
                        }
                    } 
                  
                   if( req.indexOf("R")!= -1 ) { // example: if cmd is "servo1 1500"
                        if (x_adel == vel) {
                          x_adel = 0;
                          Serial.println("stop");
                        } else {
                          x_atra = vel;
                          Serial.println("reversa");
                        }
                    } 






                    
                    if( req.indexOf("D")!= -1 ) { // example: if cmd is "servo1 1500"
                        if (x_izqu == vel) {
                          x_izqu = 0;
                          Serial.println("recto");
                        } else {
                          x_dere = vel;
                          Serial.println("derecha");
                        }
                    }  
                  
                    if( req.indexOf("I")!= -1 ) { // example: if cmd is "servo1 1500"
                        if (x_dere == vel) {
                          x_dere = 0;
                          Serial.println("recto");
                        } else {
                          x_izqu = vel;
                          Serial.println("izquierda");
                        }
                   }
                   else
                   {
                   //Serial.println("Bluetooth disconnected............");
                   }
               
                 }
}

