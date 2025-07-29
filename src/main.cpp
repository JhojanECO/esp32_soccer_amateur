#include <Arduino.h>
#include <BluetoothSerial.h>
#include "motor_control.h"

BluetoothSerial SerialBT;

int baseSpeed = 150;  // Valor inicial
const int MAX_SPEED_PWM = 255;

void setup() {
    SerialBT.begin("Rata Rusa");
    initMotors();
}

void loop() {
    if (SerialBT.available()) {
        char command = SerialBT.read();

        if (command >= '0' && command <= '9') {
            // Ajustar velocidad proporcional
            int level = command - '0';  // Convierte char '0'-'9' a int 0-9
            baseSpeed = (MAX_SPEED_PWM * level) / 9;
            //SerialBT.print("Speed set to: ");
            //SerialBT.println(baseSpeed);
        } else {
            // Control de movimiento
            switch (command) {
                case 'R'://R
                    controlMotors(baseSpeed, baseSpeed);
                    break;
                case 'L'://L
                    controlMotors(-baseSpeed, -baseSpeed);
                    break;
                case 'F'://F
                    controlMotors(baseSpeed, -baseSpeed);
                    break;
                case 'B'://B
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
