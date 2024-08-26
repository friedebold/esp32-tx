#include <Arduino.h>
#include <remote.h>

const int L_VRY_PIN = A3;
const int L_VRX_PIN = A0;
const int R_VRY_PIN = A6;
const int R_VRX_PIN = A7;
const int R_POW_PIN = 32;
const int L_BTN_PIN = 4;
const int R_BTN_PIN = 12;

void setup_remote()
{
    pinMode(L_VRX_PIN, INPUT);
    pinMode(L_VRY_PIN, INPUT);
    pinMode(R_POW_PIN, OUTPUT);
    digitalWrite(R_POW_PIN, HIGH);
    pinMode(R_VRX_PIN, INPUT);
    pinMode(R_VRY_PIN, INPUT);
    pinMode(L_BTN_PIN, INPUT);
    pinMode(R_BTN_PIN, INPUT);
}

float calibrate_joystick_axis(float value, float positive_factor, float negative_factor)
{
    if (value < 0.01 && value > -0.01)
        value = 0;
    else
    {
        if (value > 0)
            value = value * positive_factor;
        else
            value = value * negative_factor;
    }
    return min(max(float(-1.0), value), float(1.0));
}

float sigmoiding(float value)
{
    const float K = 0.5; // Can be between 0 & < 1
    return (value * sqrt(1 - K)) / sqrt(1 - K * value * value);
}

int left_btn_val;
int right_btn_val;

int prev_left_btn_val = 0;
int prev_right_btn_val = 0;

void read_remote()
{
    // Read Buttons
    left_btn_val = digitalRead(L_BTN_PIN);
    right_btn_val = digitalRead(R_BTN_PIN);

    if (prev_left_btn_val == 1 && left_btn_val == 0)
    {
        remote_data.left_button = !remote_data.left_button;
    }
    if (prev_right_btn_val == 1 && right_btn_val == 0)
    {
        remote_data.right_button = !remote_data.right_button;
    }

    prev_left_btn_val = left_btn_val;
    prev_right_btn_val = right_btn_val;

        // LEFT X-Axis
    int l_x_v = analogRead(L_VRX_PIN);
    float l_x = -(l_x_v / 4095.0 - 0.445);
    l_x = calibrate_joystick_axis(l_x, 2.245, 1.81);
    l_x = sigmoiding(l_x);

    // LEFT Y-Axis
    int l_y_v = analogRead(L_VRY_PIN);
    float l_y = (l_y_v / 4095.0 - 0.445);
    l_y = calibrate_joystick_axis(l_y, 1.795, 2.24);
    l_y = sigmoiding(l_y);

    // RIGTH Y-Axis
    int r_x_v = analogRead(R_VRX_PIN);
    float r_x = r_x_v / 4095.0 - 0.45;
    r_x = calibrate_joystick_axis(r_x, 1.818, 2.222);
    r_x = sigmoiding(r_x);

    // RIGHT Y-Axis
    int r_y_v = analogRead(R_VRY_PIN);
    float r_y = -(r_y_v / 4095.0 - 0.44);
    r_y = calibrate_joystick_axis(r_y, 2.272, 1.785);
    r_y = sigmoiding(r_y);

    Joystick left = {l_x, l_y};
    Joystick right = {r_x, r_y};

    remote_data.left = left;
    remote_data.right = right;
}