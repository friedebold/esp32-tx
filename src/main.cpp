#include <Arduino.h>
#include "main.h"
#include "remote.h"
#include "coms.h"

Remote remote_data;
PID pid_data;

// Received Data
float min_bat_v;
float bat_c;
Thrust thrust;
float roll;

void setup()
{
  Serial.begin(115200);

  setup_wifi();
  setup_remote();
  pinMode(2, OUTPUT);
  pid_data = {0.05, 0.0, 0.01}; // 0.06, 0, 0.02
}

void loop()
{
  read_remote();

  // Set Onboard LED
  digitalWrite(2, remote_data.left_button);

  send_data(pid_data);

  Serial.print(remote_data.left_button);
  Serial.print("\t");
  Serial.print(remote_data.right_button);
  Serial.print("\t");
  Serial.print(remote_data.left.x);
  Serial.print("\t");
  Serial.print(remote_data.left.y);
  Serial.print("\t");
  Serial.print(remote_data.right.x);
  Serial.print("\t");
  Serial.print(remote_data.right.y);
  Serial.println();
}