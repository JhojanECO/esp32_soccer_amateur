#include <Arduino.h>
#include <BluetoothSerial.h>

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

void setup() {
    SerialBT.begin("Chero");
    pinMode(PWMA, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
}

void motorA_forward(int speed) {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, speed);
}

void motorA_backward(int speed) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, speed);
}

void motorB_forward(int speed) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    analogWrite(PWMB, speed);
}

void motorB_backward(int speed) {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    analogWrite(PWMB, speed);
}

void stopMotors() {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    analogWrite(PWMA, 0);
    analogWrite(PWMB, 0);
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
                    motorA_forward(velo);
                    motorB_forward(velo);
                    break;
                case 'B':
                    motorA_backward(velo);
                    motorB_backward(velo);
                    break;
                case 'R':
                    motorA_forward(velo);
                    motorB_backward(velo);
                    break;
                case 'L':
                    motorA_backward(velo);
                    motorB_forward(velo);
                    break;
                default:
                    stopMotors();
                    break;
            }
        }
    }
}