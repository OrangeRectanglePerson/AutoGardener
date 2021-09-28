//startup screen
void main_menu() { //startup screen after product reset ; screen mode 1
  delay(SCRN_SW_DELAY);
  curr_screen = 1; //startup is screen mode 1

  bool stay = true;
  unsigned long refresh_timer = 0;
  String welcome_menu[] = { //startup menu layoyut
    "AUTOGARDENER",
    "F1: New Session",
    "F2: Runtime",
    "F3: Settings"};

  print_screen(welcome_menu); //prints startup menu to display

  while (stay) {
    if (millis() - refresh_timer >= refresh_delay) {
      water(); //carry out watering when it it time to
      water_timer_refresh(); //set ms since last water
      print_screen(welcome_menu); //prints startup menu to display
      refresh_timer = millis();
    }
    
    if (digitalRead(F1)) {
      stay = false;
      curr_screen = 2; //move to new session menu
    }
    else if (digitalRead(F2)) {
      stay = false;
      curr_screen = 3; //move to runtime menu
    }
    else if (digitalRead(F3)) {
      stay = false;
      curr_screen = 4; //move to settings menu
    }
  }
}

//new session
void new_session() { //setting pH & moisture level for a new session ; screen mode 2
  delay(SCRN_SW_DELAY);
  curr_screen = 2; //new session is screen mode 2

  bool stay = true; //true if settings not confirmed
  byte currset = 0; //current settings value to be manipulated (0 is moisture, 1 is pH, 2 is confirm settings & 3 is exit
  
  byte old_MoistWant = MoistWant; //old wanted moisture value in case of abort
  float old_PhWant = PhWant; //old wanted moisture value in case of abort

  refreshscreen_newsession(currset);

  while (stay) {
    if (digitalRead(F1) == HIGH){
      if (currset == 0) {
        if (MoistWant > 0) MoistWant -= 5;
      }
      if (currset == 1) {
        if (PhWant > 4) PhWant -= 0.5;
      }
    }
    else if (digitalRead(F2) == HIGH){
      if (currset == 0) {
        if (MoistWant < 80) MoistWant += 5;
      }
      if (currset == 1) {
        if (PhWant < 8) PhWant += 0.5;
      }
    }
    else if (digitalRead(F3) == HIGH){
      if (currset < 3) currset += 1;
      else currset = 0;  
    }
    else if (digitalRead(F4) == HIGH){
      if (currset > 0) currset -= 1;
      else currset = 3;
    }

    refreshscreen_newsession(currset); //refreshes the screen

    if (digitalRead(F5) == HIGH and currset >= 2) stay = false;
    
  }

  if (currset == 3) { //aborted
    MoistWant = old_MoistWant; //set back to old moisture level
    PhWant = old_PhWant; //set back to old pH level
  }
  curr_screen = 3; // move to runtime menu
}

void refreshscreen_newsession(byte selectedpos) { //part of new session
  delay(SCRN_SW_DELAY);
  
  String sigarrw[] = {"",""," "," "};
  sigarrw[selectedpos] = (char) 127;
  
  String NS_menu[] = {
   "New Session",
   "Moisture: " + (String) MoistWant + "%" + sigarrw[0],
   "Ph: " + (String) PhWant + sigarrw[1],
   "Confirm" + sigarrw[2] + " Exit" + sigarrw[3]};
  
   print_screen(NS_menu);
}

//runtime menu
void runtime_menu() {
  delay(SCRN_SW_DELAY);
  curr_screen = 3; //placeholder is screen mode 0

  bool stay = true;
  String playpause = "";
  unsigned long refresh_timer = 0;
  
  while (stay) {
    if (millis() - refresh_timer >= refresh_delay) {
      water(); //carry out watering when it it time to
      water_timer_refresh(); //set ms since last water
      if (ongoing) playpause = ">";
      else playpause = "||";
      String runtime_display[] = { //runtime menu layoyut
        (String) (water_timer[0]/3600000.0) + " h / " + (String) hours_between + " h",
        "Moisture: " + (String) get_moisture() + "/" + (String) MoistWant + "%",
        "Ph: " + (String) get_pH() + "/" + (String) PhWant,
        "F3: " + playpause + " | F5: exit"};
      print_screen(runtime_display); //prints runtime menu to display
      refresh_timer = millis();
    }
    if (digitalRead(F3)) ongoing = !ongoing;
    if (digitalRead(F5)) stay = false;
  }

  curr_screen = 1; //move to main menu
}

//settings menu
void settings_menu() {
  delay(SCRN_SW_DELAY);
  curr_screen = 4; //settings is screen mode 4

  bool stay = true; //true if settings not entered
  byte currset = 0; //current settings value to be manipulated (0 is backlight, 1 is waittime, 2 is confirm 3 is exit

  float old_hours_between = hours_between;
  bool old_backlight_on = backlight_on;
  
  refreshscreen_settings(currset); //prints settings menu to display

  while (stay) {
    if (digitalRead(F1) == HIGH and digitalRead(F2) == HIGH) hours_between = 0.02; //comment out for for final
    else
    if (digitalRead(F1) == HIGH){
      if (currset == 0) {
        lcd.backlight();
        backlight_on = true;
      }
      if (currset == 1) {
        if (hours_between < 168) hours_between += 0.5;
      }
    }
    else if (digitalRead(F2) == HIGH){
      if (currset == 0) {
        lcd.noBacklight();
        backlight_on = false;
      }
      if (currset == 1) {
        if (hours_between > 1) hours_between -= 0.5;
      }
    }
    else if (digitalRead(F3) == HIGH){
      if (currset < 3) currset += 1;
      else currset = 0;  
    }
    else if (digitalRead(F4) == HIGH){
      if (currset > 0) currset -= 1;
      else currset = 3;
    }

    refreshscreen_settings(currset); //refreshes the screen

    if (digitalRead(F5) == HIGH and currset >= 2) stay = false;
    
  }

  if (currset == 3) {
    hours_between = old_hours_between; //set back to old hours between when aborted
    if (old_backlight_on) lcd.backlight();
    else lcd.noBacklight();
  }
  
  curr_screen = 1; //move to main menu
}

void refreshscreen_settings(byte selectedpos) { //part of settings  
  String sigarrw[] = {"",""," "," "};
  sigarrw[selectedpos] = (char) 127;
  
  String SE_menu[] = {
    "SETTINGS",
    "Backlight" + sigarrw[0],
    "Waittime " + (String) hours_between + "h" + sigarrw[1],
    "Confirm" + sigarrw[2] + " Exit" + sigarrw[3]};
  
   print_screen(SE_menu);
}


//placeholder screen
void placeholder() { //placeholder screen for tests ; screen mode 0
  delay(SCRN_SW_DELAY);
  curr_screen = 0; //placeholder is screen mode 0

  bool stay = true;
  String placeholder_text[] = { //placeholder display layoyut
    "PLACEHOLDER",
    "if you're a user",
    "big bug",
    "F3 for exit"};
    
  print_screen(placeholder_text); //prints placeholder to display

  while (stay){
    if (digitalRead(F3) == HIGH) stay = false;
  }

  curr_screen = 1; //move to main menu
}
