//define functions
void print_screen(String msg[]) {
  String emptyline = "";
  for (byte i=0; i<DISP_COL; i++) {
    emptyline += " ";
  }
  for (byte i = 0; i<DISP_ROW; i++) {
    lcd.setCursor(0, i);
    lcd.print(emptyline);
    lcd.setCursor(0, i);
    lcd.print(msg[i]);
  }
}

void setup_screen() {
  lcd.init();
  if (backlight_on) lcd.backlight();
  else lcd.noBacklight();
  lcd.setCursor(0, 0);
}
