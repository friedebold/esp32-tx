#include <Arduino.h>
#include "main.h"
#include "remote.h"
#include "coms.h"

Remote remote_data;
PID pid_data;
Battery battery;

// Received Data
float min_bat_v;
float bat_c;
Thrust thrust;
float roll;

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
  Serial.print(">lowBat:");
  Serial.println(battery.lowestBat);
}