#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN digital pins on Arduino
const byte address[6] = "01000"; // Address common to both the transmitter and receiver modules.

struct MyData {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
};

MyData data;

void setup() {
  radio.begin();
  radio.openWritingPipe(address); // use radio.openWritingPipe(n, address) for more addresses
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
}
int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse) {
  val = constrain(val, lower, upper);
  if (val < middle) {
    val = map(val, lower, middle, 0, 127);
  }
  else {
    val = map(val, middle, upper, 127, 255);
  }

  return(reverse?val:255-val);
}

void loop() {
  data.throttle = mapJoystickValues(analogRead(A0), 183, 472, 780, true);
 // data.yaw = mapJoystickValues(analogRead(A1), 122, 432, 744, true);
//  data.pitch = mapJoystickValues(analogRead(A2), 274, 593, 897, true);
//  data.roll = mapJoystickValues(analogRead(A3), 294, 593, 919, true);

  //  data.yaw = map(constrain(analogRead(A1), 122, 744), 122, 744, 0, 255);
  //  data.pitch = map(constrain(analogRead(A2), 274, 897), 274, 897, 0, 255);
  //  data.roll = map(constrain(analogRead(A3), 294, 919), 294, 919, 0, 255);

  const char text[] = "Welcome to RAIN.";
  radio.write(&data, sizeof(MyData));
  //delay(1000);

  Serial.print("T: ");
  Serial.print(data.throttle);
  Serial.print(" | ");
  Serial.print("Y: ");
  Serial.print(data.yaw);
  Serial.print(" | ");
  Serial.print("P: ");
  Serial.print(data.pitch);
  Serial.print(" | ");
  Serial.print("R: ");
  Serial.println(data.roll);
}
