#include "ds18b20.h"

#define postingInterval 300000                  // Интервал между отправками данных на narodmon в миллисекундах (5 минут)
unsigned long lastConnectionTime = 0;           // Время последней передачи данных на narodmon

void narodmon_Handle(){
  if (millis() - lastConnectionTime > postingInterval){
    if (SendToNarodmon()){
      lastConnectionTime = millis();
    }else{
      lastConnectionTime = millis() - postingInterval + 15000;
    }
  }    
}

// Отправка данных на narodmon
bool SendToNarodmon(){
  WiFiClient client;
    
  Serial.println("Send to narodmon");
    
  String buf;                                                             // Формируем пакет
    
  buf = "#" + getHostname() + "#WiFi термометр\n";                             // ID и название устройства
    
  buf += "#RSSI#" + String(WiFi.RSSI()) + "#Уровень сигнала\n";           // Уровень сигнала
    
  #ifdef NTC
    buf += "#TEMP#" + String(getTempNTC(),2) + "#NTC\n";                  // NTC термометр
  #endif
  #ifdef DS18
    for (unsigned char i = 0; i < getOneWireSensorsCount(); i++)  {
        buf += "#";
        buf += addressToString(DS18B20_sensors[i].deviceAddress);
        buf += "#";
        buf += String(DS18B20_sensors[i].temperature, 2);
        buf += "\n";
     }      
  #endif
  buf += "##";                                                            // Конец пакета
    
  Serial.println(buf);
    
  if (client.connect("narodmon.ru", 8283)) {                              // Попытка подключения
    client.print(buf);                                                    // Отправляем данные
    while (client.available()){                                           // Если что-то в ответ будет - считываем
      String line = client.readStringUntil('\r'); 
    }
  }else{
    return false;                                                         // Не удалось подключиться
  }
    return true;
}  




  

  
