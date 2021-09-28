//modules and basic setup
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define DISP_ROW 4
#define DISP_COL 20
#define F1 6
#define F2 5
#define F3 4
#define F4 3
#define F5 2
#define LCD_PWR 13 //lcd power pin
#define SCRN_SW_DELAY 50 //sets ms of delay before screen switches modes

LiquidCrystal_I2C lcd(0x27, DISP_ROW, DISP_COL);

//global vars
String disp_contents[DISP_ROW]; //will contain text to be on screen
int curr_screen = 0; //what screen mode it is in
byte MoistWant = 50; //wanted moisture value
float PhWant = 6.5; //wanted pH value
float hours_between = 24; //hours to wait before re-watering sessions
unsigned long water_timer[2]; //[ms since last watering, last watering millis()]
unsigned int refresh_delay = 500; //define delays of screen refreshes in ms
bool ongoing = true; //is watering session to be run
bool backlight_on = true;

void setup() {
  for (byte i=2; i<=6; i++) pinMode(i, INPUT); //button pins
  for (byte i=8; i<=11; i++) pinMode(i, OUTPUT); //motor pins
  setup_screen();
  main_menu();
}

void loop() {  
  //UI thing here
  if (curr_screen == 1) {
    main_menu();
  }
  else if (curr_screen == 2) { 
    new_session();
  }
  else if (curr_screen == 3) { 
    runtime_menu(); 
  }
  else if (curr_screen == 4) { 
    settings_menu();
  }
  else if (curr_screen == 0) { //catchall for bug or test
    placeholder();
  }

  water_timer_refresh();
}
