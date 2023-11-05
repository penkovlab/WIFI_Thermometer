void led_init(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void led_on(void) {
  digitalWrite(LED_BUILTIN, LOW);
}
void led_off(void) {
  digitalWrite(LED_BUILTIN, HIGH);
}
