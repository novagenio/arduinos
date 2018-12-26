/*
 * IRremoteESP8266: IRrecvDump - dump details of IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 Sept, 2015
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009, Copyright 2009 Ken Shirriff, http://arcfn.com
 * JVC and Panasonic protocol added by Kristian Lauszus (Thanks to zenwheel and other people at the original blog post)
 * LG added by Darryl Smith (based on the JVC protocol)
 */

#include <IRremoteESP8266.h>

//int RECV_PIN = 2; //an IR detector/demodulatord is connected to GPIO pin 2
unsigned long IRValue = 0;
IRrecv irrecv(D5);    // recibe por el pin 5 del NodeMcu
decode_results results;

int PressIr, XP, YP = 0;       // indica 0 si no hay IR valor, 1 si hay valor

void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver, IR module
}

void loop() {
  
  if (irrecv.decode(&results)) {
    
    if (IRValue == results.value) {
      IRValue = 50128919;
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



void MoveIr() {
   
   Serial.println(IRValue);
   switch (IRValue) // Aqui tenemos la clausula switch con sus case:
                  { case 50102399:
                        XP=XP+1;
                        PressIr = 1;
                        break;
                    case 50106479:
                        XP=XP-1;
                        PressIr = 1;
                        break;
                    case 50108519:
                        YP=YP+1;
                        PressIr = 1;
                        break;
                    case 50104439:
                        YP=YP-1;
                        PressIr = 1;
                        break;    
                    case 50128919:
                        PressIr = 0;
                        Serial.print("Stop");
                        IRValue=0;
                        break; 
                        
                   }    
                   Serial.print("X:"); Serial.println(XP);
                   Serial.print("Y:"); Serial.println(YP);
                                     
                   delay(100);
                   
}
