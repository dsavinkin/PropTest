
#include "config.h"
#include "main.h"
#include "graphics.h"
#include "keyboard.h"

#include "HX711_int.h"

HX711 scale(HX711_DOUT, HX711_PD_SCK);    // parameter "gain" is ommited; the default value 128 is used by the library

void setup() {

/* First init display */
  init_TFT();
  clear_screen();

/* Initialize keyboard */
  init_keyboard();
  
  Serial.begin(9600);

  Serial.println("HX711 Demo");

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  unsigned long start = micros();  
  Serial.println(scale.read());      // print a raw reading from the ADC
  Serial.println(micros() - start);

  Serial.print("read average(20): \t\t");
  start = 0;
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC
  Serial.println(micros() - start);

  Serial.print("get value(5): \t\t");
  start = micros();
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)
  Serial.println(micros() - start);

  Serial.print("get units(5): \t\t");
  start = micros();
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided 
  Serial.println(micros() - start);
  start = micros();
            // by the SCALE parameter (not set yet)  

 // scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  start = micros();
  scale.set_scale(416);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  Serial.println(micros() - start);
  start = micros();
  Serial.println("tare:");
  scale.tare();               // reset the scale to 0
  Serial.println(micros() - start);

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  start = micros();
  Serial.println(scale.read());                 // print a raw reading from the ADC
  Serial.println(micros() - start);

  Serial.print("read average(20): \t\t");
  start = micros();
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC
  Serial.println(micros() - start);

  Serial.print("get value(5): \t\t");
  start = micros();
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()
  Serial.println(micros() - start);

  Serial.print("get units(5): \t\t");
  start = micros();
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided 
  Serial.println(micros() - start);
  start = micros();
            // by the SCALE parameter set with set_scale

  scale.power_up();  

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
  int weight = scale.get_units(1);
//  int weight = scale.read()/416;
//  scale.power_down();              // put the ADC in sleep mode
  start = micros() - start;  
  
//  if (button_pressed(BUTTON_UP))
  if (button_released(BUTTON_UP))
//  if (button_hold(BUTTON_UP))
  {
    cur_pos--;
    if (cur_pos < 1) cur_pos = 10;
  }

  //  if (button_pressed(BUTTON_DOWN))
  if (button_released(BUTTON_DOWN))
//  if (button_hold(BUTTON_DOWN))
  {
    cur_pos++;
    if (cur_pos > 10) cur_pos = 1;
  }


  if (button_released(BUTTON_CANCEL))
  {
    scale.tare();
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


