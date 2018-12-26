
#include <ESP8266WiFi.h>


const char* ssid = "NOVAGENIO";
const char* password = "novagenio";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(85);  //puerto 80

/// definición modulo IR
#include <IRremoteESP8266.h>
#include <IRrecv.h>

//int RECV_PIN = 2; //an IR detector/demodulatord is connected to GPIO pin 2
unsigned long IRValue = 0;
IRrecv irrecv(D5);    // recibe por el pin 5 del NodeMcu
decode_results results;

int PressIr, XP, YP = 90;       // indica 0 si no hay IR valor, 1 si hay valor

int BtState = 0;               // indica 0 si bluetooth inactivo 1 activo.
/////////////////////////////////


/////////
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40);

unsigned int pos0=172; // ancho de pulso en cuentas para pocicion 0°
unsigned int pos180=565; // ancho de pulso en cuentas para la pocicion 180°
/////////

char cmd[20]; 
char indice_servo[2];                          

void setServo(uint8_t n_servo, int angulo) {
  int duty;
  duty=map(angulo,0,180,pos0, pos180);
  servos.setPWM(n_servo, 0, duty);  
}


void setup() {
  
  Serial.begin(9600);  //
  delay(10);

  // prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
 

  // inicia driver motores
  Wire.begin(D1, D2);  //(Corresponde a los pines 1 y 2 del nodemcu).
  servos.begin();  
  servos.setPWMFreq(60); //Frecuecia PWM de 60Hz o T=16,66ms

  /////// inicia modulo IR
  irrecv.enableIRIn(); // Start the receiver, IR module

  }

void loop() {
  // Check if a client http has connected
  
 //Serial.println("va a leer el cliente http");
 

     lee_cliente_http();

 
     lee_cliente_bluetooth();

     if (!Serial.available()) {     //si bluetooth no esta activado (puerto serie) puede leer IR
     // lee_cliente_IR();
     }

 
  
} 



void lee_cliente_http()
{
  
  // Check if a client http has connected
  WiFiClient client = server.available();
  if (!client) {
//    Serial.println("no client");
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  
  while (client.connected())  {
                 if (client.available()) {                           // valida que el buffer del server tiene datos enviados por el clinete
                     String req = client.readStringUntil('\n');      // lee datos hasta encontrar /n (final de carro
                     client.flush();                                 // limpia el buffer no leido
                     Serial.println(req); client.println(req);       // muestra en el serial monitor y el el log del movil lo enviado.
                    
                     req.toCharArray(cmd, 8);                        // convierte array de caracteres a char las 8 primeras posiciones 0 a 7
                     req.toCharArray(indice_servo, 3);               // indice_servo indica el prefijo del comando enviado: ej: s1, el indice es 1
                     int val = atoi(cmd+3);                          // deja en val el valor entero de la posisión 2 de cmd
            
                     if ((req.indexOf("s0=")!= -1) or (req.indexOf("s1=")!= -1) or (req.indexOf("s2=")!= -1) or (req.indexOf("s3=")!= -1))
                          {
                          //client.print("indice:"); client.print(indice_servo+1); client.print(" valor:");client.println(val); //se deja en comentario por que retarda mucho
                          //Serial.println("dentro if:");
                          setServo(atoi(indice_servo+1),val);   
                          //Serial.println("antes salir if:");
                          delay(10);
                          }
                     
                     if (req.indexOf("b1=") != -1) //valida si dentro de req viene un valor, en este caso b=
                          {
                          digitalWrite(2, val);
                          }
                     delay(1);
                     }
                 delay(1);
         } //final del while (client.connected()


  //setServo(0,90);
  delay(50); 
  client.stop();
  Serial.println("fin cliente connectado....");
  delay(500);
}




void lee_cliente_bluetooth()
{
                 if (Serial.available()) {                           // valida que el buffer del server tiene datos enviados por el clinete
                     Serial.println("Bluetooth..........");
                     
                     String req = Serial.readStringUntil('\n');      // lee datos hasta encontrar /n (final de carro
                     
                     Serial.println(req);       // muestra en ehootl serial monitor y el el log del movil lo enviado.
                    
                     req.toCharArray(cmd, 8);                        // convierte array de caracteres a char las 8 primeras posiciones 0 a 7
                     req.toCharArray(indice_servo, 3);               // indice_servo indica el prefijo del comando enviado: ej: s1, el indice es 1
                     int val = atoi(cmd+3);                          // deja en val el valor entero de la posisión 2 de cmd
            
                     if ((req.indexOf("s0=")!= -1) or (req.indexOf("s1=")!= -1) or (req.indexOf("s2=")!= -1) or (req.indexOf("s3=")!= -1))
                          {
                          //client.print("indice:"); client.print(indice_servo+1); client.print(" valor:");client.println(val); //se deja en comentario por que retarda mucho
                          //Serial.println("dentro if:");
                          setServo(atoi(indice_servo+1),val);   
                          //Serial.println("antes salir if:");
                          delay(10);
                          }
                      if (req.indexOf("b1=") != -1) //valida si dentro de req viene un valor, en este caso b=
                          {
                          digitalWrite(2, val);
                          }
                     delay(1);
                   }
                   else
                   {
                    
//                   Serial.println("Bluetooth disconnected............");
                   }
               
 }


void MoveIr() {
   
   switch (IRValue) // Aqui tenemos la clausula switch con sus case:
                  { case 50102399:
                        if (XP < 130) {XP=XP+1;} else{PressIr = 0;}
                        PressIr = 1;
                        break;
                    case 50106479:
                        if (XP > 20) {XP=XP-1;} else{PressIr = 0;}
                        PressIr = 1;
                        break;
                    case 50108519:
                        if (YP < 150) {YP=YP+1;} else{PressIr = 0;}
                        PressIr = 1;
                        break;
                    case 50104439:
                        if (YP > 50) {YP=YP-1;} else{PressIr = 0;}
                        PressIr = 1;
                        break;    
                    case 50128919:
                        PressIr = 0;
                        Serial.print("Stop");
                        IRValue=0;
                        break; 
                        
                   }    
                   setServo(0, XP);
                   setServo(1, YP);
                   Serial.print("X,"); Serial.println(XP); 
                   Serial.print("Y:"); Serial.println(YP);
                                     
                   delay(50);
                   
}

void  lee_cliente_IR()
{  
  Serial.println("InfraRojos");  
  if (irrecv.decode(&results)) {
    
          if (IRValue == results.value) {            // SI presiona el mismo boton 2 veces, la variable IRValue es Stop
            IRValue = 50128919;                      //
            }
           else
           {
            IRValue=results.value;
          }
      
        MoveIr();
        irrecv.resume(); // Receive the next value
   }
  
   if (PressIr == 1) {
    MoveIr();
    }
}

