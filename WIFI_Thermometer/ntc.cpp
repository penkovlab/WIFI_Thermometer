#include <math.h>

double getTempNTC() {
  int val = 0;
  for(int i = 0; i < NUMSAMPLES; i++) {
    val += analogRead(A0);
    delay(1);
  }
    
  val = val / NUMSAMPLES;
  
  double R_NTC = Rs / (1023 / (double)val - 1);
  double Temp = R_NTC / Rtherm;
  Temp = log(Temp);
  Temp /= B;
  Temp += 1.0 / (Nominal_t + 273.15);
  Temp = 1.0 / Temp;
  Temp -= 273.15;
  
  return Temp;
}
