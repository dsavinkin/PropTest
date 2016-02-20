
#include "config.h"
#include "main.h"
#include "graphics.h"
#include "keyboard.h"

#include "HX711.h"

#ifdef SD_ENABLE
  #include "SD.h"
  // set up variables using the SD utility library functions:
  Sd2Card card;
#endif

HX711 scale(HX711_DOUT, HX711_PD_SCK);    // parameter "gain" is ommited; the default value 128 is used by the library

void setup() {

/* First init display */
  init_TFT();
  clear_screen();

/* Initialize keyboard */
  init_keyboard();
  
  Serial.begin(9600);

#ifdef SD_ENABLE

  Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, SD_CS)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    //return;
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }
#endif

  Serial.println("HX711 Demo");

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided 
            // by the SCALE parameter (not set yet)  

 // scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.set_scale(416.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided 
            // by the SCALE parameter set with set_scale

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
  scale.power_up();  
  float weight = scale.get_units(1);
  scale.power_down();              // put the ADC in sleep mode
  
  if (button_released(BUTTON_UP))
  {
    cur_pos++;
	if (cur_pos > 10) cur_pos = 1;
  }

  print_item(cur_pos, "Scale:", weight, "g");


  loopcnt++;

  if ((loopcnt % 50) == 0)
  {
    Serial.print("Scale:\t");
    Serial.println(weight, 1);
  }
  
//  delay(500);
  
}


