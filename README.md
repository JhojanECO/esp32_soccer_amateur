# Cómo cargar este proyecto al ESP32 usando Visual Studio Code + PlatformIO

Este proyecto está diseñado para funcionar con ESP32 y controlarse mediante Bluetooth. Si nunca has usado PlatformIO ni Visual Studio Code, ¡no te preocupes! Aquí te guiamos paso a paso.

---

## Requisitos previos

- ✅ [Instalar Visual Studio Code](https://code.visualstudio.com/)
- ✅ [Instalar PlatformIO IDE](https://platformio.org/install/ide?install=vscode)
  - Abre VS Code → ve a la sección de extensiones (ícono cuadrado en la barra lateral) → busca "PlatformIO IDE" → haz clic en instalar.
- ✅ Tener una **placa ESP32** y su cable USB.
- ✅ Conexión a internet (para clonar el repositorio desde GitHub).

---

## 1. Clonar el repositorio

Abre VS Code → abre la terminal (`Ctrl + ñ` o `Ctrl + \``) y escribe:

```bash
git clone https://github.com/JhojanECO/esp32_soccer_amateur.git
cd esp32_soccer_amateur
```

---

## 2. Abrir el proyecto con PlatformIO

Después de clonar:

1. En VS Code, selecciona `File > Open Folder` y abre la carpeta `esp32_soccer_amateur`.
2. Espera unos segundos mientras PlatformIO analiza el proyecto.
3. Verás una barra lateral con el logo de PlatformIO (el hormigón 🐜). Haz clic en ella para ver las opciones.

---

## 3. Conectar y configurar tu ESP32

1. Conecta el ESP32 a tu PC por USB.
2. PlatformIO debería detectar automáticamente el **puerto** (ejemplo: `COM3` o `/dev/ttyUSB0`).
   - Si no lo hace, puedes configurarlo en `platformio.ini`:
     ```ini
     upload_port = COM3  ; o el puerto que te corresponda
     ```

---

## 4. Subir el código

Haz clic en el icono ✔️ (`Build`) para compilar el código.

Luego haz clic en la flecha → (`Upload`) para **subirlo al ESP32**.

También puedes hacerlo desde la terminal de PlatformIO:

```bash
platformio run --target upload
```

---

## 5. Conecta por Bluetooth

- El ESP32 se llamará: `NOVAnombre`
- Usa una app como **Serial Bluetooth Terminal** (Android) o similar para:
  - Enviar comandos:
    - `'F'`: Avanza
    - `'B'`: Retrocede
    - `'L'`: Gira a la izquierda
    - `'R'`: Gira a la derecha
    - `'S'`: Detenerse
  - Cambiar velocidad máxima con un solo número `'0'` a `'9'`.

---

## ¿Problemas?

- Asegúrate de seleccionar el **modelo correcto de ESP32** en `platformio.ini`. Por ejemplo:
  ```ini
  
    [env:esp32doit-devkit-v1]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino
monitor_speed = 115200
  ```
- Verifica que el **driver USB del ESP32** esté correctamente instalado.
- Reinicia VS Code si algo no carga bien.

---

## ¡Listo!

Ahora puedes controlar tu robot o coche con ESP32 usando este código. Si tienes ideas o mejoras, ¡haz un fork o abre un pull request!
