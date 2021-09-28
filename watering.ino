void water() {
  String watering_screen[] = { //startup menu layoyut
    "WATERING",
    "SESSION",
    "ONGOING",
    (String) MoistWant + "% | " + (String) PhWant};
  if ((ongoing) and (water_timer[0]/3600000.0 >= hours_between)) {
    print_screen(watering_screen);
    water_timer[1] = millis();
    delay(100);

    while (get_moisture() < MoistWant) {
      //water cycle
      motorOn(3);
      delay(5000);
      motorOff(3);

      //check if soil too alkaline
      if (get_pH() > PhWant + 0.5){
        motorOn(1);
        delay(2000);
        motorOff(1);
      }

      //check if soil too acidic
      if (get_pH() < PhWant - 0.5){
        motorOn(2);
        delay(2000);
        motorOff(2);
      }
      
      //dispense cycle
      motorOn(0);
      delay(15000);
      motorOff(0);
    }    
    
    delay(100);
  }
}
