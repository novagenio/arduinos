#include <VirtualWire.h>

void setup()
{
    Serial.begin(9600);  
    Serial.println("Emisor: Setup");

    // Se inicializa el RF
    vw_setup(2000); // velocidad: Bits per segundo
    vw_set_tx_pin(2); //Pin 2 como salida para el RF 
}

void loop()
{
    const char *msg = "Este mundo un poco largo";  
Serial.println("Emisor: Enviendo mensaje");
    digitalWrite(13, true); // Parpadeamos  el led al enviar 
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); //Esperamos hasta que el mensaje se envie
    digitalWrite(13, false);
    delay(2000);
}

