/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <Servo.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSNbrig
const byte address[6] = "01000";

byte servoPin1 = 3;
byte servoPin2 = 4;

Servo servo1;
Servo servo2;
void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  servo2.attach(servoPin2);
  servo1.attach(servoPin1);
}
void loop() {
  int val1 = 0;
  int val2 = 0;
  struct MyData{
    byte throttle;
    byte yaw;
    byte pitch;
    byte roll;
       };
   MyData data;
  if (radio.available()) {
   // char data[32] = "";
    radio.read(&data, sizeof(MyData));
    Serial.print("throttle =");
    Serial.println(data.throttle);

    int reading = data.throttle;
  if (reading>=200){
    val1 = map(reading,0,255,1000,2000);
    val2 = map(reading,0,255,2000,1000);
    servo1.write(val1);
    servo2.write(val2);
    }
    else if (reading==0){
    val2 = map(reading,0,255,1000,2000);
    val1 = map(reading,0,255,2000,1000);
    servo1.write(val1);
    servo2.write(val2);
    }
  }
}
