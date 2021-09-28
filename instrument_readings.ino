int get_moisture() {
  //takes 0-3.6v input from moisture sensor and converts to 0-100% range
  return map(analogRead(A0), 0, 737, 0, 100); 
}

float get_pH() {
  return 34*(analogRead(A2)*5.0/1024) - 52;
}
