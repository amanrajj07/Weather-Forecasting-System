# Wiring and calibration notes

## Example GPIO assignment
- DHT11 DATA: GPIO 4
- LM35 VOUT: GPIO 34 (ADC1)
- Rain sensor DO: GPIO 27

These are example assignments, not a claim about the original diploma prototype's wiring.

## LM35
The LM35 produces approximately 10 mV per °C. The sketch converts the ESP32 ADC's calibrated millivolt reading to °C by dividing by 10. For better accuracy, compare the reading with a trusted thermometer and document any calibration offset.

Check the exact LM35 package pinout before wiring. Do not rely on wire colours alone.

## Rain sensor
The sketch reads the module's digital output (DO). Adjust the module's potentiometer if it has one. If the status is reversed, change `RAIN_ACTIVE_LEVEL` in the sketch from `LOW` to `HIGH`.

The ESP32 input must never receive 5 V. Confirm the rain module's output voltage; use a level shifter or divider if required.

## DHT11
The sketch uses the Adafruit DHT library. A breakout board usually includes the required pull-up resistor; a bare DHT11 may need an external pull-up resistor from DATA to 3.3 V. Check the exact module.
