/* meArm_Adafruit IK test - York Hackspace May 2014
 * Test applying Nick Moriarty's Inverse Kinematics solver
 * to Phenoptix' meArm robot arm, to walk a specified path.
 *
 * Pins:
 * Arduino    PWMServo
 *    GND         GND
 *     5V    VCC & V+
 *     A4         SDA
 *     A5         SCL
 * 
 * The servos attach to the first block of four servo connections on
 * the Adafruit board, brown wire at the bottom, yellow wire at the top.
 * Adafruit    Servo
 *       0      Base
 *       1  Shoulder (right)
 *       2     Elbow (left)
 *       3   Gripper
 *
 * You can attach to a different block of four by changing the 'begin' call
 * to specify a block 0-3, e.g. to use the second block call arm.begin(1);
 * - to mirror movements to all 4 blocks, call arm.begin(-1);
 */
#include <ESP8266WiFi.h>

#include <meArm_Adafruit.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

meArm arm;

void setup() {
    Wire.begin(D1, D2);
  Serial.begin(9600);
 arm.begin();


  
}

void loop() {
  //Clap - so it's obvious we're at this part of the routine
  arm.openGripper();
  arm.closeGripper();
  
  delay(500);
  //Go up and left to grab something
  arm.gotoPoint(0, 100, 10); 
  
  //Go down, forward and
  delay(1000);
//  right to drop it
 
  
  arm.gotoPoint(-100,100,10);
    delay(1000);
    
  arm.gotoPoint(-100,150,10);
    delay(1000);

  //Back to start position
  arm.gotoPoint(100,150,10);
    delay(1000);

arm.gotoPoint(100,100,10);
    delay(1000);

}

