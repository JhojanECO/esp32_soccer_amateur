#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>

class MotorController {
public:
    MotorController(int pwma, int ain1, int ain2,
                    int pwmb, int bin1, int bin2);

    void forward(int speed);
    void backward(int speed);
    void turnLeft(int speed);
    void turnRight(int speed);
    void stop();

private:
    int _pwma;
    int _ain1;
    int _ain2;
    int _pwmb;
    int _bin1;
    int _bin2;

    void motorAForward(int speed);
    void motorABackward(int speed);
    void motorBForward(int speed);
    void motorBBackward(int speed);
};

#endif // MOTORCONTROLLER_H
