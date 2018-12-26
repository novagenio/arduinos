// test: Servo, en pos 0, del driver 16. Pines vc y gnd a 3v y gnd nodemcu. y scl y sda a D1 y D2
#include <ESP8266WiFi.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40);

unsigned int pos0=172; // ancho de pulso en cuentas para pocicion 0°
unsigned int pos180=565; // ancho de pulso en cuentas para la pocicion 180°

//


void setServo(uint8_t n_servo, int angulo) {
  int duty;
  duty=map(angulo,0,180,pos0, pos180);
  servos.setPWM(n_servo, 0, duty);  
}

void setup() {
  delay(500); // wait for bluetooth module to start
  //Serial1.begin(9600); // Bluetooth default baud is 115200 serial1, solo para arduino mega, uso de bluetooth
  Serial.begin(115200);
  Wire.begin(D1, D2);  //(Corresponde a los pines 1 y 2 del nodemcu).
  servos.begin();  
  servos.setPWMFreq(60); //Frecuecia PWM de 60Hz o T=16,66ms
}


void loop() {
  setServo(0,120);
  Serial.println("hola");
  delay(3000);
  setServo(0,40);
  delay(3000);
  }

