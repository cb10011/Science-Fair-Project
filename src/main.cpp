#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
sensors_event_t event;

void setup() {
  tsl.enableAutoRange(true);
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
  uint32_t currentFrequency;

  Serial.begin(9600);
  Serial.println("Hello!");

  Serial.println("Measuring voltage and current with INA219...");
  ina219.begin();
}

void loop(void)
{
  tsl.getEvent(&event);

  if (event.light)
  {
    Serial.print("Light:         ");
    Serial.print(event.light);
    Serial.println(" lux");
  }
  else
  {
    /* If event.light = 0 lux the sensor is probably saturated
       and no reliable data could be generated! */
    Serial.println("Sensor overload");
  }

  float shuntvoltage = 0;
  float busvoltage   = 0;
  float current_mA   = 0;
  float loadvoltage  = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage   = ina219.getBusVoltage_V();
  current_mA   = ina219.getCurrent_mA() * -1;
  loadvoltage  = busvoltage + (shuntvoltage / 1000);

  //  Serial.print("Bus Voltage:   "); Serial.print(busvoltage);
  // Serial.println(" V");
  //  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage);
  // Serial.println(" mV");
  //  Serial.print("Load Voltage:  "); Serial.print(loadvoltage);
  // Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.println("");

  delay(2000);
}
