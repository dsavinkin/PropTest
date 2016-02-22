#include "config.h"
#include "main.h"
#include "graphics.h"
#include "keyboard.h"
#include "scale.h"
#include "esc.h"

void setup() {
/* First init serial */
  Serial.begin(9600);

/* Init display */
  init_TFT();
  clear_screen();

/* Initilize ESC PWM */  
  init_esc();

/* Initialize keyboard */
  init_keyboard();

/* Initialize scale */
  init_scale();

}

static int cur_pos = 1;

void loop(void) {
/*  for(uint8_t rotation=0; rotation<4; rotation++) {
    tft.setRotation(rotation);
    testText();
    delay(1000);
  }
  
*/

  static int loopcnt = 0;
  unsigned long start = micros(); 
//  scale.power_up();  
  double weight = read_scale();
//  int weight = scale.read()/416;
//  scale.power_down();              // put the ADC in sleep mode
  start = micros() - start;  
  
//  if (button_pressed(BUTTON_UP))
  if (button_released(BUTTON_UP))
//  if (button_hold(BUTTON_UP))
  {
    cur_pos--;
    if (cur_pos < 1) cur_pos = 10;
    set_esc((cur_pos-1)*10);
  }

  //  if (button_pressed(BUTTON_DOWN))
  if (button_released(BUTTON_DOWN))
//  if (button_hold(BUTTON_DOWN))
  {
    cur_pos++;
    if (cur_pos > 10) cur_pos = 1;
    set_esc((cur_pos-1)*10);
  }

  if (button_released(BUTTON_OK))
  {
    tare_scale();
  }

  if (button_released(BUTTON_CANCEL))
  {
    stop_esc();
  }


  print_item(cur_pos, "Scale:", weight, "g");


  loopcnt++;

  if ((loopcnt % 500) == 0)
  {
    Serial.print("Scale:\t");
    Serial.print(weight);
    Serial.print("\t time:\t");
    Serial.println(start);
  }
  
//  delay(500);
  
}


