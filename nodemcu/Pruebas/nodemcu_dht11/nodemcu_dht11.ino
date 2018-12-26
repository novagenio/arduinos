#include <DHT11.h>

int pin=2;
DHT11 dht11(D2);

void setup()
   {
    ESP.wdtDisable();
ESP.wdtEnable(WDTO_8S);

       Serial.begin(9600);
   }

void loop()
   {
       int err;
       float temp, hum;
       ESP.wdtFeed();


       if((err = dht11.read(hum, temp)) == 0)    // Si devuelve 0 es que ha leido bien
          {
             Serial.print("Temperatura: ");
             Serial.print(temp);
             Serial.print(" Humedad: ");
             Serial.print(hum);
             Serial.println();
          }
       else
          {
             Serial.println();
             Serial.print("Error Num :");
             Serial.print(err);
             Serial.println();
          }
       delay(1000);            //Recordad que solo lee una vez por segundo
   }  
