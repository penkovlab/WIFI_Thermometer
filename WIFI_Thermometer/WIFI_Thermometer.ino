#include <ESP8266WiFi.h>
#include "ntc.h"
#include "ds18b20.h"
#include "helpers.h"
#include "wm.h"

// Параметры комплектации
#define DS18
//#define NTC



void setup() {
  Serial.begin(115000);

#ifdef DS18
  oneWireInit();
#endif

  WiFi.mode(WIFI_STA);

  wm_init();
}

void loop() {
#ifdef DS18
  oneWireLoop();
#endif

  yield();

  if (WiFi.status() == WL_CONNECTED) {
    led_on();
    narodmon_Handle();
  } else {
    led_off();
  }
}
