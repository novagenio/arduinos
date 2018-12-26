/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>

const char* ssid = "NOVAGENIO";
const char* password = "novagenio";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(85);

char cmd[100];                           

void setup() {
  Serial.begin(115200);
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
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    // Serial.println("no client");
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
 
  while (client.connected())  {
                 if (client.available()) {                           //valida que el buffer del server tiene datos enviados por el clinete
                     String req = client.readStringUntil('\n');      //lee datos hasta encontrar /n (final de carro
                     client.flush();                                  //limpia el buffer no leido
                     Serial.println(req);
                     client.println(req);
                     
                     if (req.indexOf("b=") != -1) //valida si dentro de req viene un valor, en este caso b=
                         {
                          req.toCharArray(cmd, 5);                  //  convierte array de caracteres a char
                          int val = atoi(cmd+2);                    // deja en val el valor entero de la posisión 2 de cmd
                          digitalWrite(2, val);
                         }
                     delay(5);
                     }
                 delay(5);
         } //final del while (client.connected()
  
  delay(50); 
  client.stop();
  Serial.println("fin cliente connectado....");
  delay(1000);
} 


