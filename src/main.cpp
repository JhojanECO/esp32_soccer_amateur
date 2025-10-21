#include <Arduino.h>
#include <BluetoothSerial.h>
#include "motor_control.h"

BluetoothSerial SerialBT;

int baseSpeed = 150;  // Valor inicial
const int MAX_SPEED_PWM = 255;

void setup() {
    SerialBT.begin("Violet");
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
                case 'F'://R
                    controlMotors(baseSpeed, baseSpeed);
                    break;
                case 'B'://L
                    controlMotors(-baseSpeed, -baseSpeed);
                    break;
                case 'I'://F
                    controlMotors(60, 120);
                    break;
                case 'G'://R
                    controlMotors(120, 60);
                    break;
                case 'H'://F
                    controlMotors(-60, -120);
                    break;
                case 'J'://R
                    controlMotors(-120, -60);
                    break;
                case 'R'://F
                    controlMotors(120, -120);
                    break;
                case 'L'://B
                    controlMotors(-120, 120);
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
