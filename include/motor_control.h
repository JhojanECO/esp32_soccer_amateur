#pragma once
#include <Arduino.h>

void initMotors();

void motorA_forward(int speed);
void motorA_backward(int speed);
void motorB_forward(int speed);
void motorB_backward(int speed);
void stopMotors();

void setSpeed(char cmd);
int getSpeed();
