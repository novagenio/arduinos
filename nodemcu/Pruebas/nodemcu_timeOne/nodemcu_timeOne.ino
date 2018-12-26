#include <TimerOne.h>
 
void (*resetFunc)(void) = 0;
 
//last time the WDT was ACKd by the application
unsigned long lastUpdate=0;
 
//time, in ms, after which a reset should be triggered
unsigned long timeout=10000;
 
void longWDT(void)
{
  if((millis()-lastUpdate)>timeout)
  {
    //enable interrupts so serial can work
    sei();
 
    //detach Timer1 interrupt so that if processing goes long, WDT isn't re-triggered
    Timer1.detachInterrupt();
 
    //flush, as Serial is buffered; and on hitting reset that buffer is cleared
    Serial.println("WDT triggered");
    Serial.flush();
 
    //call to bootloader / code at address 0
    //resetFunc();
  }
}
 
void setup(void)
{
  Serial.begin(115200);
  Serial.println(F("Hello, WDT!\n")); 
 
  //allow 30s without update; and seed an update
  timeout = 30000; 
  lastUpdate=millis();
 
  Timer1.initialize(1000000); //1 second pulses
  Timer1.attachInterrupt(longWDT); //code to execute
 
  //long running setup code
 
  timeout = 10000;
}
 
void loop(void)
{
  //example app; must see an 'A' on serial port every so often, or will reset
  int serialByte = Serial.read();
  if(serialByte=='A')
    lastUpdate=millis(); 
  else if(serialByte=='B')
    timeout = 5000;
  else if(serialByte=='C')
    timeout = 15000;
}
  
