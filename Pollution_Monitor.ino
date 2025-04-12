// --- Required Libraries ---
// --- Author#VS# ----
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>  // For 1.3" SH1106 OLEDs
#include <Adafruit_SSD1306.h> // For 0.96" SSD1306 OLED
#include <TCA9548A.h>
#include <DHT.h>

// --- Constants & Definitions ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define DHTPIN 4
#define DHTTYPE DHT11
#define BUZZER_PIN 18
#define LED_PIN 2
#define LDR_PIN 35
#define MQ135_PIN 34

// INMP441 pins
#define MIC_WS 25
#define MIC_SD 26
#define MIC_SCK 27

// --- Objects ---
TCA9548A tca;
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SH1106G display0(128, 64, &Wire, -1); // Air Quality - SH1106
Adafruit_SH1106G display1(128, 64, &Wire, -1); // Microphone - SH1106
Adafruit_SH1106G display2(128, 64, &Wire, -1); // Light Sensor - SH1106
Adafruit_SSD1306 display3(128, 64, &Wire, OLED_RESET); // DHT - SSD1306

// --- Setup ---
void setup() {
  Serial.begin(115200);
  Wire.begin();
  dht.begin();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(MQ135_PIN, INPUT);

  tca.begin(Wire);

  // Initialize all displays
  for (uint8_t i = 0; i < 4; i++) {
    tca.closeAll();
    tca.openChannel(i);
    bool init_ok;
    if (i == 3) {
      init_ok = display3.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    } else {
      Adafruit_SH1106G* disp = (i == 0) ? &display0 : (i == 1) ? &display1 : &display2;
      init_ok = disp->begin(0x3C, true);
    }
    if (!init_ok) {
      Serial.print("Display "); Serial.print(i); Serial.println(" failed to initialize");
    }
    if (i == 3) {
      display3.clearDisplay();
      display3.setTextColor(SSD1306_WHITE);
      display3.setTextSize(2);
      display3.setCursor(0, 0);
      display3.println("Initializing...");
      display3.display();
    } else {
      Adafruit_SH1106G* disp = (i == 0) ? &display0 : (i == 1) ? &display1 : &display2;
      disp->clearDisplay();
      disp->setTextColor(SH110X_WHITE);
      disp->setTextSize(2);
      disp->setCursor(0, 0);
      disp->println("Initializing...");
      disp->display();
    }
  }
}

// --- Read Mic ---
float readMic() {
  // Placeholder: implement I2S reading logic for INMP441 here if needed
  return random(30, 80); // Fake dB value for testing
}

// --- Loop ---
void loop() {
  float gas = analogRead(MQ135_PIN);
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  float sound = readMic();
  int ldr = digitalRead(LDR_PIN);

  // Display 0 - Air Quality
  tca.closeAll(); tca.openChannel(0);
  display0.clearDisplay();
  display0.setTextSize(1);
  display0.setCursor(0,0);
  display0.println("Air Quality:");
  display0.print("Gas: "); display0.println(gas);
  display0.display();

  // Display 1 - Microphone
  tca.closeAll(); tca.openChannel(1);
  display1.clearDisplay();
  display1.setTextSize(1);
  display1.setCursor(0,0);
  display1.println("Sound Level:");
  display1.print(sound); display1.println(" dB");
  display1.display();

  // Display 2 - Light Sensor
  tca.closeAll(); tca.openChannel(2);
  display2.clearDisplay();
  display2.setTextSize(1);
  display2.setCursor(0,0);
  display2.println("Light Level:");
  display2.println(ldr == LOW ? "Bright" : "Dark"); // Inverted logic fix
  display2.display();

  // Display 3 - DHT
  tca.closeAll(); tca.openChannel(3);
  display3.clearDisplay();
  display3.setTextSize(1);
  display3.setCursor(0,0);
  display3.println("Temp & Hum:");
  display3.print("T: "); display3.print(temp); display3.println(" C");
  display3.print("H: "); display3.print(hum); display3.println(" %");
  display3.display();

  // Alert logic
  if (gas > 500 || sound > 75 || ldr == HIGH || temp > 35) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }

  delay(2000);
}
