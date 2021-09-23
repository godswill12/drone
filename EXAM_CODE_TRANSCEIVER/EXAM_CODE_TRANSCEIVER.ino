#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN digital pins on Arduino
const byte address[6] = "01000"; // Address common to both the transmitter and receiver modules.

struct MyData {
  byte throttle;
//  byte yaw;
//  byte pitch;
//  byte roll;
};

MyData data;

void setup() {
  radio.begin();
  radio.openWritingPipe(address); // use radio.openWritingPipe(n, address) for more addresses
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
}

void loop() {
  data.throttle = map(constrain(analogRead(A0), 183, 780), 183, 780, 0, 255);
//  data.yaw = map(constrain(analogRead(A1), 122, 744), 122, 744, 0, 255);
//  data.pitch = map(constrain(analogRead(A2), 274, 897), 274, 897, 0, 255);
//  data.roll = map(constrain(analogRead(A3), 294, 919), 294, 919, 0, 255);

  const char text[] = "Welcome to RAIN.";
  radio.write(&data, sizeof(MyData));
  //delay(1000);

  Serial.print("T: ");
  Serial.print(data.throttle);
  Serial.println(" | ");
//  Serial.print("Y: ");
//  Serial.print(data.yaw);
//  Serial.print(" | ");
//  Serial.print("P: ");
//  Serial.print(data.pitch);
//  Serial.print(" | ");
//  Serial.print("R: ");
//  Serial.println(data.roll);
}
