#include "ntc.h"
#include "ds18b20.h"
#include "helpers.h"

// Параметры комплектации
#define SENSOR_DS18B20
//#define SENSOR_NTC

String Hostname;   

void setup() {
  Serial.begin(115000);
  
  #ifdef SENSOR_DS18B20
    oneWireInit();
  #endif
  
  WiFi.mode(WIFI_STA); 

  Hostname = "ESP00" + WiFi.macAddress();
  Hostname.replace(":","");

  wm_init();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED){
    led_on();
    narodmon_Handle();
  }else{
    led_off();
  }
}
