void water_timer_refresh() {
  if (water_timer[1] <= millis()) {
    water_timer[0] = millis() - water_timer[1];
  }
  if (water_timer[1] > millis()) {
    water_timer[0] = millis() + (4294967295 - water_timer[0]);
  } 
}
