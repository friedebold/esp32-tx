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

struct Thrust
{
    float left;
    float right;
};

struct PID
{
    float p;
    float i;
    float d;
};

struct Correction
{
    PID pitch;
    PID roll;
    PID yaw;
};

extern float min_bat_v;
extern float bat_c;
extern Thrust thrust;
extern float roll;
extern Remote remote_data;

#endif