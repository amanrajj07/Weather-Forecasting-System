/*
  ESP32-Based Weather Forecasting System
  Sensors:
    - DHT11: humidity
    - LM35: temperature (analog)
    - Rain sensor module: digital output (DO)

  Example wiring:
    DHT11 DATA -> GPIO 4
    LM35 VOUT  -> GPIO 34 (ADC1)
    Rain DO    -> GPIO 27

  IMPORTANT:
  - Verify your actual sensor pinouts and module voltage ratings.
  - ESP32 GPIO pins are NOT 5 V tolerant.
  - The rain module DO signal must be 3.3 V-safe.
  - This sketch monitors current conditions; it does not predict future weather.
*/

#include <DHT.h>

#define DHT_PIN       4
#define DHT_TYPE      DHT11
#define LM35_PIN      34
#define RAIN_PIN      27

// Many rain modules assert DO LOW when rain/wetness is detected.
// Change this to HIGH if your module behaves in the opposite way.
const int RAIN_ACTIVE_LEVEL = LOW;

const unsigned long READ_INTERVAL_MS = 2000;
unsigned long lastReadTime = 0;

DHT dht(DHT_PIN, DHT_TYPE);

float readLm35TemperatureC() {
  // analogReadMilliVolts() is supported by the Arduino-ESP32 core.
  // LM35 scale factor: 10 mV per degree Celsius.
  const uint32_t millivolts = analogReadMilliVolts(LM35_PIN);
  return millivolts / 10.0f;
}

void printSensorReadings() {
  const float humidity = dht.readHumidity();
  const float dhtTemperature = dht.readTemperature();
  const float lm35Temperature = readLm35TemperatureC();
  const int rainState = digitalRead(RAIN_PIN);

  Serial.println(F("----------------------------------"));

  if (isnan(humidity) || isnan(dhtTemperature)) {
    Serial.println(F("DHT11 reading failed. Check DATA wiring and sensor power."));
  } else {
    Serial.print(F("Humidity (DHT11): "));
    Serial.print(humidity, 1);
    Serial.println(F(" %"));

    Serial.print(F("DHT11 temperature (diagnostic): "));
    Serial.print(dhtTemperature, 1);
    Serial.println(F(" C"));
  }

  Serial.print(F("Temperature (LM35): "));
  Serial.print(lm35Temperature, 1);
  Serial.println(F(" C"));

  Serial.print(F("Rain status: "));
  if (rainState == RAIN_ACTIVE_LEVEL) {
    Serial.println(F("RAIN / WETNESS DETECTED"));
  } else {
    Serial.println(F("NO RAIN DETECTED"));
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(RAIN_PIN, INPUT);
  analogReadResolution(12);
  dht.begin();

  Serial.println();
  Serial.println(F("ESP32 Weather Monitoring System"));
  Serial.println(F("DHT11 + LM35 + Rain Sensor"));
  Serial.println(F("Serial Monitor: 115200 baud"));
}

void loop() {
  const unsigned long now = millis();

  if (now - lastReadTime >= READ_INTERVAL_MS) {
    lastReadTime = now;
    printSensorReadings();
  }
}
