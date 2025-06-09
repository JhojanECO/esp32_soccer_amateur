#include "MotorController.h"

MotorController::MotorController(int pwma, int ain1, int ain2,
                                 int pwmb, int bin1, int bin2)
    : _pwma(pwma), _ain1(ain1), _ain2(ain2),
      _pwmb(pwmb), _bin1(bin1), _bin2(bin2) {
    pinMode(_pwma, OUTPUT);
    pinMode(_pwmb, OUTPUT);
    pinMode(_ain1, OUTPUT);
    pinMode(_ain2, OUTPUT);
    pinMode(_bin1, OUTPUT);
    pinMode(_bin2, OUTPUT);
}

void MotorController::motorAForward(int speed) {
    digitalWrite(_ain1, LOW);
    digitalWrite(_ain2, HIGH);
    analogWrite(_pwma, speed);
}

void MotorController::motorABackward(int speed) {
    digitalWrite(_ain1, HIGH);
    digitalWrite(_ain2, LOW);
    analogWrite(_pwma, speed);
}

void MotorController::motorBForward(int speed) {
    digitalWrite(_bin1, HIGH);
    digitalWrite(_bin2, LOW);
    analogWrite(_pwmb, speed);
}

void MotorController::motorBBackward(int speed) {
    digitalWrite(_bin1, LOW);
    digitalWrite(_bin2, HIGH);
    analogWrite(_pwmb, speed);
}

void MotorController::forward(int speed) {
    motorAForward(speed);
    motorBForward(speed);
}

void MotorController::backward(int speed) {
    motorABackward(speed);
    motorBBackward(speed);
}

void MotorController::turnLeft(int speed) {
    motorABackward(speed);
    motorBForward(speed);
}

void MotorController::turnRight(int speed) {
    motorAForward(speed);
    motorBBackward(speed);
}

void MotorController::stop() {
    digitalWrite(_ain1, LOW);
    digitalWrite(_ain2, LOW);
    digitalWrite(_bin1, LOW);
    digitalWrite(_bin2, LOW);
    analogWrite(_pwma, 0);
    analogWrite(_pwmb, 0);
}

