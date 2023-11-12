#include "ds18b20.h"
#include <OneWire.h>
#include <DallasTemperature.h>  //https://github.com/milesburton/Arduino-Temperature-Control-Library

// Data wire is plugged into port 2 on the ESP8266
#define ONE_WIRE_BUS          2
#define TEMPERATURE_PRECISION 9
#define DELAY_FOR_CONVERSION  1000

uint32_t lastRequest;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// count of devices
int devices = 0;






void oneWireInit(void) {
  // Start sensor
  sensors.begin();

  // locate devices on the bus
  devices = sensors.getDeviceCount();

  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(devices, DEC);
  Serial.println(" devices.");

  // This dynamically allocates the deviceAddresses array to the number of devices
  // We already created the pointer to it above so it's global
  DS18B20_sensors = new OWI_device[devices];

  sensors.setWaitForConversion(false);  // makes it async
  sensors.requestTemperatures();
  lastRequest = millis();
}

int getOneWireSensorsCount(void) {
  return devices;
}

void oneWireLoop(void) {
  if (millis() - lastRequest > DELAY_FOR_CONVERSION) {

    // Get temp
    for (uint8_t i = 0; i < devices; i++) {
      DS18B20_sensors[i].temperature = sensors.getTempC(DS18B20_sensors[i].deviceAddress);
    }

    // Request to all devices on the bus
    sensors.requestTemperatures();
    lastRequest = millis();
  }

}

// function to convert a device address to string
String addressToString(DeviceAddress deviceAddress)
{
  String address;
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) address.concat("0");
    String addrByteHex = String(deviceAddress[i], HEX);
    address.concat(addrByteHex);
    address.toUpperCase();
  }
  return address;
}
