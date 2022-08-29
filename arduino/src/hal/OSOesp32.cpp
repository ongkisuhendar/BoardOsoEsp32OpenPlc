#include <stdlib.h>
extern "C"
{
#include "openplc.h"
}
#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_ADS1X15.h"
int8_t ADS1115_;
void ADS_(int i)
{
    ADS1115_ = i;
}
// OpenPLC HAL for ESP32 boards

/******************PINOUT CONFIGURATION**************************
Digital In:  00, 17, 18, 19, 21, 22, 23, 27, 32 (%IX0.0 - %IX1.0)
             33                             (%IX1.0 - %IX1.0)
Digital Out: 01, 02, 03, 04, 05, 12, 13, 14 (%QX0.0 - %QX0.7)
             15, 16                         (%QX1.0 - %QX1.1)
Analog In:   34, 35, 36, 39                 (%IW0 - %IW2)
Analog Out:  25, 26                         (%QW0 - %QW1)
*****************************************************************/

// Define the number of inputs and outputs for this board (mapping for the NodeMCU 1.0)
#define NUM_DISCRETE_INPUT 10
#define NUM_ANALOG_INPUT 4
#define NUM_DISCRETE_OUTPUT 10
#define NUM_ANALOG_OUTPUT 2

uint8_t pinMask_DIN[] = {00, 17, 18, 19, 21, 22, 23, 27, 32, 33};
uint8_t pinMask_DOUT[] = {01, 02, 03, 04, 05, 12, 13, 14, 15, 16};
uint8_t pinMask_AOUT[] = {25, 26};

Adafruit_ADS1115 ads;
uint8_t pinMask_AIN_[] = {0, 1, 2, 3};
uint8_t pinMask_AIN[] = {34, 35, 36, 39};


void hardwareInit()
{

    for (int i = 0; i < NUM_DISCRETE_INPUT; i++)
    {
        if (ADS1115_)
        {
            pinMode(pinMask_DIN[i], INPUT);
            if (i == 4)
            {
                pinMask_DIN[i] = 255;
            }
            if (i == 5)
            {
                pinMask_DIN[i] = 255;
            }
        }
        else
        {
            pinMode(pinMask_DIN[i], INPUT);
        }
    }
    if (ADS1115_)
    {
        ads.begin();
    }
    else
    {
        for (int i = 0; i < NUM_ANALOG_INPUT; i++)
        {
            pinMode(pinMask_AIN[i], INPUT);
        }
    }
    for (int i = 0; i < NUM_DISCRETE_OUTPUT; i++)
    {
        pinMode(pinMask_DOUT[i], OUTPUT);
    }

    for (int i = 0; i < NUM_ANALOG_OUTPUT; i++)
    {
        pinMode(pinMask_AOUT[i], OUTPUT);
    }
}

void updateInputBuffers()
{
    for (int i = 0; i < NUM_DISCRETE_INPUT; i++)
    {
        if (bool_input[i / 8][i % 8] != NULL)
            *bool_input[i / 8][i % 8] = digitalRead(pinMask_DIN[i]);
    }

    for (int i = 0; i < NUM_ANALOG_INPUT; i++)
    {
        if (ADS1115_)
        {
            if (int_input[i] != NULL)
                *int_input[i] = ads.readADC_SingleEnded(pinMask_AIN_[i]);
        }
        else
        {
            if (int_input[i] != NULL)
                *int_input[i] = (analogRead(pinMask_AIN[i]) * 64);
        }
    }
}

void updateOutputBuffers()
{
    for (int i = 0; i < NUM_DISCRETE_OUTPUT; i++)
    {
        if (bool_output[i / 8][i % 8] != NULL)
            digitalWrite(pinMask_DOUT[i], *bool_output[i / 8][i % 8]);
    }
    for (int i = 0; i < NUM_ANALOG_OUTPUT; i++)
    {
        if (int_output[i] != NULL)
            dacWrite(pinMask_AOUT[i], (*int_output[i] / 256));
    }
}
