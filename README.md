# ESP32-Based Weather Forecasting System

A diploma major project built around an ESP32 and three separate sensing functions:
- DHT11 for relative humidity
- LM35 for temperature
- Rain sensor module for rain detection

The ESP32 reads the sensors and reports the measurements through the Arduino IDE Serial Monitor.

> **Scope note:** The implementation in this repository is a sensor-based weather-monitoring prototype. It reports current sensor readings and rain detection; it does not generate a meteorological forecast for future hours or days.

## Hardware

- ESP32 development board
- DHT11 humidity sensor (module or bare sensor)
- LM35 analog temperature sensor
- Rain sensor module with digital output (DO)
- Jumper wires and breadboard
- USB cable for programming

## Default wiring used by the example

| Module | Sensor pin | ESP32 pin |
|---|---|---|
| DHT11 | VCC | 3V3 |
| DHT11 | GND | GND |
| DHT11 | DATA | GPIO 4 |
| LM35 | Vs | 5V/VIN (according to the sensor board/module specification) |
| LM35 | GND | GND |
| LM35 | Vout | GPIO 34 |
| Rain module | VCC | 3V3, only if the module works at 3.3 V |
| Rain module | GND | GND |
| Rain module | DO | GPIO 27 |

**Important wiring checks**
- The code assumes a common LM35 pin arrangement when looking at the flat face: Vs, Vout, GND. Confirm the pinout printed on your exact component/datasheet before powering it; variants and breakout boards may differ.
- GPIO 34 is an input-only ADC1 pin on the classic ESP32 and is used for the LM35 output.
- ESP32 GPIOs are **not 5 V tolerant**. Never connect a 5 V rain-module digital output directly to GPIO 27. Power the module at 3.3 V if its specifications allow it, or use a suitable logic-level shifter / divider on DO.
- All modules must share a common GND.
- If using a bare 4-pin DHT11 rather than a breakout module, wire it according to its datasheet and add the required pull-up resistor on DATA (commonly 4.7–10 kΩ to 3.3 V).

These are example pin assignments because the original project wiring diagram was not available. Change the constants at the top of `src/weather_forecasting_system.ino` if your original wiring used different GPIOs.

## Arduino IDE setup

1. Install the ESP32 board support package in Arduino IDE and select the correct ESP32 board.
2. Install **DHT sensor library by Adafruit** using Library Manager.
3. Install **Adafruit Unified Sensor** if Library Manager requests it.
4. Open `src/weather_forecasting_system.ino`.
5. Confirm the wiring and rain-sensor output logic before uploading.
6. Open Serial Monitor at **115200 baud**.

## Output

The Serial Monitor displays:
- Temperature in °C from LM35
- Relative humidity in % from DHT11
- Rain status from the rain module's digital output

The rain module's DO output may be active LOW or active HIGH depending on the module/comparator adjustment. The example defaults to active LOW; change `RAIN_ACTIVE_LEVEL` if your module behaves oppositely.

## Repository structure

```text
Weather-Forecasting-System/
├── README.md
├── .gitignore
├── docs/
│   └── wiring-and-calibration.md
└── src/
    └── weather_forecasting_system.ino
```

## Project details

- Project: Weather Forecasting System (sensor-based monitoring prototype)
- Controller: ESP32
- Development environment: Arduino IDE
- Project level: Diploma Major Project

## Limitations and future improvements

- Add an LCD/OLED display or web dashboard.
- Add data logging and historical graphs.
- Add a barometric pressure sensor.
- Add a genuine forecasting method using historical data and a validated model/API.

## Author

Add your name, institute, diploma branch, and project year here before submitting.
