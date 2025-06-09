#include <Arduino.h>
#include <BluetoothSerial.h>
#include "motor_control.h"

BluetoothSerial SerialBT;

float baseSpeed = 150;  // Valor inicial
const float MAX_SPEED_PWM = 255.0f;

void setup() {
    SerialBT.begin("NOVAnombre");
    initMotors();
}

void loop() {
    if (SerialBT.available()) {
        char command = SerialBT.read();

        if (command >= '0' && command <= '9') {
            // Ajustar velocidad proporcional
            int level = command - '0';  // Convierte char '0'-'9' a int 0-9
            baseSpeed = (MAX_SPEED_PWM * level) / 9.0f;
            //SerialBT.print("Speed set to: ");
            //SerialBT.println(baseSpeed);
        } else {
            // Control de movimiento
            switch (command) {
                case 'F':
                    controlMotors(baseSpeed, baseSpeed);
                    break;
                case 'B':
                    controlMotors(-baseSpeed, -baseSpeed);
                    break;
                case 'R':
                    controlMotors(baseSpeed, -baseSpeed);
                    break;
                case 'L':
                    controlMotors(-baseSpeed, baseSpeed);
                    break;
                case 'S':
                    stopMotors();
                    break;
                default:
                    stopMotors();  // Seguridad
                    break;
            }
        }
    }
}
