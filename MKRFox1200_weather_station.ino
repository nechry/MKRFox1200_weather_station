// -------------------------------------------------------------------------
// MKRFox1200 Weather Station
// Sends temperature and humidity through Sigfox network
// Use a HTU21D 3.3V sensor
// Created: 03.07.2018
// Author: Nechry
// Code: https://github.com/Nechry/MKRFOX1200_weather_station
// --------------------------------------------------------------------------

#include "SigFox.h"
#include "ArduinoLowPower.h"
#include "Adafruit_HTU21DF.h"
#include "Adafruit_Sensor.h"
#include "conversions.h"

#define DEBUG         false        // Set DEBUG to false to disable debug serial prints
#define SLEEPTIME     15*60*1000   // Set the delay to 15 minutes

typedef struct __attribute__ ((packed)) sigfox_message {
  int16_t moduleTemperature;
  int16_t sensorTemperature;
  uint16_t humidity;
  uint8_t lastMessageStatus;
} SigfoxMessage;

// Stub for message which will be sent
SigfoxMessage message;

Adafruit_HTU21DF htu = Adafruit_HTU21DF();

void setup() {
  if (DEBUG) {
    // We are using Serial1 instead than Serial because we are going in standby
    // and the USB port could get confused during wakeup. To read the DEBUG prints,
    // connect pins 13-14 (TX-RX) to a 3.3V USB-to-serial converter
    Serial1.begin(115200);
    while (!Serial1) {}
  }

  if (!SigFox.begin()) {
    // Something is really wrong, try rebooting
    // Reboot is useful if we are powering the board using an unreliable power source
    // (eg. solar panels or other energy harvesting methods)
    reboot();
  }

  // Send module to standby until we need to send a message
  SigFox.end();

  if (DEBUG) {
    // Enable DEBUG prints and LED indication if we are testing
    SigFox.debug();
  }

  if (!htu.begin()) {
    if (DEBUG)
      Serial.println("HTU Error");
  }
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humidity = htu.readHumidity();
  // Read temperature as Celsius (the default)
  float sensorTemperature = htu.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(sensorTemperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  message.sensorTemperature = convertFloatToInt16(sensorTemperature, 60, -60);
  message.humidity = convertFloatToUInt16(humidity, 110);

  if (DEBUG) {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(sensorTemperature);
    Serial.print(" *C ");
  }
  // Start the module
  SigFox.begin();
  // Wait at least 30ms after first configuration (100ms before)
  delay(100);

  // We can only read the module temperature before SigFox.end()
  message.moduleTemperature = convertFloatToInt16(SigFox.internalTemperature(), 60, -60);

  // Clears all pending interrupts
  SigFox.status();
  delay(1);

  SigFox.beginPacket();
  SigFox.write((uint8_t*)&message, 12);

  message.lastMessageStatus = SigFox.endPacket();

  SigFox.end();
  //Sleep for 15 minutes
  LowPower.sleep(SLEEPTIME);
}

void reboot() {
  NVIC_SystemReset();
  while (1) ;
}

