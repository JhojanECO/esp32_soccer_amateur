#include "motor_control.h"
#include "constants.h"

int currentSpeedA = 0;
int currentSpeedB = 0;
const int accelStep = 5;

void initMotors() {
    pinMode(PWMA, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
}

void controlSingleMotor(int pwmPin, int in1, int in2, int targetSpeed, int& currentSpeed) {
    if (currentSpeed < targetSpeed) {
        currentSpeed += accelStep;
        if (currentSpeed > targetSpeed) currentSpeed = targetSpeed;
    } else if (currentSpeed > targetSpeed) {
        currentSpeed -= accelStep;
        if (currentSpeed < targetSpeed) currentSpeed = targetSpeed;
    }

    if (currentSpeed > 0) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(pwmPin, currentSpeed);
    } else if (currentSpeed < 0) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(pwmPin, -currentSpeed);
    } else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        analogWrite(pwmPin, 0);
    }
}

void controlMotors(float vel_izq, float vel_der) {
    vel_izq = constrain(vel_izq, -255, 255);
    vel_der = constrain(vel_der, -255, 255);
    controlSingleMotor(PWMA, AIN1, AIN2, (int)vel_izq, currentSpeedA);
    controlSingleMotor(PWMB, BIN1, BIN2, (int)vel_der, currentSpeedB);
}

void stopMotors() {
    currentSpeedA = 0;
    currentSpeedB = 0;
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    analogWrite(PWMA, 0);
    analogWrite(PWMB, 0);
}
