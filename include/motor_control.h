#pragma once
#include <Arduino.h>

void initMotors();
void controlMotors(float vel_izq, float vel_der);
void stopMotors();
