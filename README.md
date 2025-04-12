# POLLUTION-MONIOTR
ESP32-based pollution detector with MQ135, DHT11, INMP441, LDR, buzzer &amp; LED. Uses TCA9548A I2C mux to drive 3 SH1106 and 1 SSD1306 OLEDs for real-time display of air quality, sound, light, and temperature/humidity. Powered by 3S Li-ion pack with buck converter.

🔧 Features
Air Quality Monitoring using the MQ135 gas sensor.

Sound Level Detection with the INMP441 I2S microphone.

Ambient Light Detection via a digital LDR sensor.

Temperature & Humidity Sensing using the DHT11.

Real-time Display Interface using:

3x 1.3" SH1106 OLEDs

1x 0.96" SSD1306 OLED (for DHT data)

Alert System:

Buzzer and LED indicator trigger on harmful conditions.

Powered by a 3S Li-ion battery pack through a buck converter.

📟 Interface Layout
Each OLED display is dedicated to a specific sensor:

Display 0: Air Quality (Gas concentration)

Display 1: Sound Level (dB)

Display 2: Light Level (Bright/Dark)

Display 3: Temperature & Humidity

🔌 Wiring & Components
ESP32 WROOM-32 DevKit V1

Sensors:

MQ135 → GPIO 34

DHT11 → GPIO 4

INMP441 → WS: GPIO 25, SD: GPIO 26, SCK: GPIO 27

LDR (digital) → GPIO 35

Buzzer: GPIO 18

Status LED: GPIO 2

TCA9548A I2C Multiplexer (default I2C address: 0x70)

OLEDs powered at 3.3V from the ESP32

⚠️ Alerts
The buzzer and LED are triggered if any of the following exceed thresholds:

Gas > 500

Sound > 75 dB

Temperature > 35°C

LDR detects darkness

💻 Tech Stack
Platform: Arduino IDE

Libraries Used:

Adafruit_SH1106

Adafruit_SSD1306

Adafruit_GFX

TCA9548A

DHT

📸 Screenshots & Demo

💡 Future Improvements
Add Wi-Fi data logging or web interface

Integrate more precise air quality sensors (e.g., PMS5003)

Use deep sleep for battery efficiency
