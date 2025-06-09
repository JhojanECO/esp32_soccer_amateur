#include <Arduino.h>
#include <BluetoothSerial.h>
#include "MotorController.h"

// Pines del TB6612FNG conectados al ESP32
#define PWMA  27
#define AIN2  26
#define AIN1  25
#define BIN1  33
#define BIN2  32
#define PWMB  12

const int veloInicial = 60;     // Velocidad mínima definida por el usuario
const int veloMax = 170;         // Velocidad máxima
int velo = veloInicial;          // Variable para controlar la velocidad actual

BluetoothSerial SerialBT;
MotorController motors(PWMA, AIN1, AIN2, PWMB, BIN1, BIN2);

void setup() {
    SerialBT.begin("Chero");
}


// Función para asignar velocidad según el comando recibido
void setSpeed(char cmd) {
    if (cmd >= '0' && cmd <= '9') {
        int porcentaje = (cmd - '0') * 10; // 0%, 10%, ..., 90%
        velo = veloInicial + ((veloMax - veloInicial) * porcentaje) / 100;
    } else if (cmd == 'q') {
        velo = veloMax;
    }
}

void loop() {
    if (SerialBT.available()) {
        char command = SerialBT.read();

        // Comandos de velocidad
        if ((command >= '0' && command <= '9') || command == 'q') {
            setSpeed(command);
        }
        // Comandos de movimiento
        else {
            switch (command) {
                case 'F':
                    motors.forward(velo);
                    break;
                case 'B':
                    motors.backward(velo);
                    break;
                case 'R':
                    motors.turnRight(velo);
                    break;
                case 'L':
                    motors.turnLeft(velo);
                    break;
                default:
                    motors.stop();
                    break;
            }
        }
    }
}