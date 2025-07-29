#pragma once
#include <Arduino.h>

void initMotors();
void controlMotors(int vel_izq, int vel_der);
void stopMotors();
