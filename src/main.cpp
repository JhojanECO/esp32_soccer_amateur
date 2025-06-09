#include <Arduino.h>
#include <BluetoothSerial.h>
#include "motor_control.h"

BluetoothSerial SerialBT;

void setup() {
    SerialBT.begin("Chero");
    initMotors();
}

void loop() {
    if (SerialBT.available()) {
        char command = SerialBT.read();

        if ((command >= '0' && command <= '9') || command == 'q') {
            setSpeed(command);
        } else {
            int speed = getSpeed();
            switch (command) {
                case 'F':
                    motorA_forward(speed);
                    motorB_forward(speed);
                    break;
                case 'B':
                    motorA_backward(speed);
                    motorB_backward(speed);
                    break;
                case 'R':
                    motorA_forward(speed);
                    motorB_backward(speed);
                    break;
                case 'L':
                    motorA_backward(speed);
                    motorB_forward(speed);
                    break;
                default:
                    stopMotors();
                    break;
            }
        }
    }
}
