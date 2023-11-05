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
    
  buf = "#" + Hostname + "#WiFi термометр\n";                             // ID и название устройства
    
  buf += "#RSSI#" + String(WiFi.RSSI()) + "#Уровень сигнала\n";           // Уровень сигнала
    
  #ifdef NTC
    buf += "#TEMP#" + String(getTempNTC(),2) + "#NTC\n";                  // NTC термометр
  #endif
  #ifdef DS18
    DS_handle();
    for (unsigned char i = 0; i < num; i++)  {
        buf += "#";
        for (unsigned char j = 0; j < 8; j++){
          if (allDevices[i].id[j] < 16) buf = buf + "0"; 
          buf = buf + String(allDevices[i].id[j], HEX);
        }

        buf += "#";
     
        word tmp = allDevices[i].temperature;
  
        if ((tmp & 0x8000)){
          buf += "-";
          tmp = -tmp;
          buf += String((float)tmp * 0.0625);
        }else{
          buf += String((float)tmp * 0.0625);
        }
          
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




  

  
