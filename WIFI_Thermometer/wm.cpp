#include <WiFiManager.h>  //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

WiFiManager wm;

void wm_init(void){
  // Чтобы не застревать в режиме AP после перезагрузки роутера
  // После истечения 3 минут портал закроется и ESP подключится к сети
  wm.setConfigPortalTimeout(180);

  // custom menu via array or vector
  // 
  // menu tokens, "wifi","wifinoscan","info","param","close","sep","erase","restart","exit" (sep is seperator) (if param is in menu, params will not show up in wifi page!)
  // const char* menu[] = {"wifi","info","param","sep","restart","exit"}; 
  // wm.setMenu(menu,6);  
  std::vector<const char *> menu = {"wifi"};    // Убираем из меню все кноме настроки WIFI
  wm.setMenu(menu);

  wm.autoConnect(Hostname.c_str());    
}
