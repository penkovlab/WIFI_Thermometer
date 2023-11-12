#ifndef __DS18B20_H__
#define __DS18B20_H__

#include <Arduino.h>
#include <DallasTemperature.h>

typedef struct
{
  DeviceAddress  deviceAddress;
  float          temperature;
} OWI_device;

// pointer to array we will define later to hold devices data
OWI_device * DS18B20_sensors;

void oneWireInit(void);
int getOneWireSensorsCount(void);
void oneWireLoop(void);
String addressToString(DeviceAddress);

#endif
