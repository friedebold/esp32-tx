#include <Arduino.h>
#include "main.h"
#include "remote.h"
#include "coms.h"

Remote remote_data;
PID pid_data;
IncomingData incoming;

void setup()
{
  Serial.begin(115200);
  Serial.println("setup");

  setup_wifi();
  setup_remote();
  pinMode(2, OUTPUT);
  pid_data = {0.05, 0.0, 0.01}; // 0.06, 0, 0.02
}

float i = 0;
void loop()
{
  i += 0.1;
  read_remote();

  // Set Onboard LED
  digitalWrite(2, remote_data.left_button);

  send_data(pid_data);

  // Print log
  Serial.print("loop");
  Serial.println(i);

  // Plot a sinus
  Serial.print(">pitch:");
  Serial.println(incoming.imu.pitch);
  Serial.print(">roll:");
  Serial.println(incoming.imu.roll);
  Serial.print(">yaw:");
  Serial.println(incoming.imu.yaw);
  Serial.print(">cBat:");
  Serial.println(incoming.battery.cBat);
  Serial.print(">lowestBat:");
  Serial.println(incoming.battery.lowestBat);
  Serial.print(">gThrust:");
  Serial.println(incoming.global_thrust);
  Serial.print(">left:");
  Serial.println(incoming.thrust.left);
  Serial.print(">right:");
  Serial.println(incoming.thrust.right);
  Serial.print(">front:");
  Serial.println(incoming.thrust.front);
  Serial.print(">back:");
  Serial.println(incoming.thrust.back);
}