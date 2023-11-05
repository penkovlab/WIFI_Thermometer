#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void oneWireInit(void) {
  sensors.begin();
}

uint8_t getDS18B20Count(void) {
  sensors.requestTemperatures();
  return sensors.getDeviceCount();
}

double getDS18B20Temp(uint8_t i) {
  return sensors.getTempCByIndex(i);
}

String getDS18B20Address(uint8_t i) {
  String strDeviceAddress = "";
  DeviceAddress deviceAddress;
  getAddress(deviceAddress, i);
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) strDeviceAddress += "0";
    strDeviceAddress += String(deviceAddress[i], HEX);
  }
  return strDeviceAddress;
}
