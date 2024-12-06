#include <Arduino.h>

#ifndef MAIN_H
#define MAIN_H

struct Joystick
{
    float x;
    float y;
};

struct Remote
{
    Joystick left;
    Joystick right;
    bool left_button;
    bool right_button;
};

struct PID
{
    float p;
    float i;
    float d;
};

struct IMU
{
    float pitch;
    float roll;
    float yaw;
};

struct Battery
{
    float lowestBat;
    float cBat;
    float vBat1;
    float vBat2;
    float vBat3;
};

struct Thrust
{
    float left;
    float right;
    float front;
    float back;
};

struct IncomingData
{
    Battery battery;
    IMU imu;
    float global_thrust;
    Thrust thrust;
};

extern float min_bat_v;
extern float bat_c;
extern float roll;
extern Remote remote_data;
extern IncomingData incoming;

#endif