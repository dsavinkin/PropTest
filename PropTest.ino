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

  Serial.println("READY");
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
    start_test(RISE_FALL);
  }

  if (button_released(BUTTON_CANCEL))
  {
    stop_esc();
  }


  print_item(cur_pos, "Scale:", weight, "g");


  loopcnt++;
/*
  if ((loopcnt % 500) == 0)
  {
    Serial.print("Scale:\t");
    Serial.print(weight);
    Serial.print("\t time:\t");
    Serial.println(start);
  }
*/  
//  delay(500);
  
}

/************************************ 
 * Name    : start_test
 * Purpuse : Start test procedure
 * Inputs  : mode - test mode
 * Outputs : None
 * Returns : exit code
 *            0 - test OK
 *            1 - test canceled
 *            2 - amp limit reached
 *            3 - watt limit reached
 *            4 - thrust limit reached
 *            5 - voltage limit reached
 ************************************/
int start_test(TEST_MODES mode)
{
  float throttle = 0;
  int throttlems = 0;
  float weight = abs(read_scale());  
  unsigned long absstart = micros();
  
  const long RISE_TIME_US = RISE_TIME*1000000;
  const long FALL_TIME_US = FALL_TIME*1000000;
  const long STALL_TIME_US = STALL_TIME*1000000;
  

  Serial.print("START TEST mode = ");
  Serial.println(mode);
  stop_esc();
  tare_scale();
  
  if ((mode == RISE) || (mode == RISE_FALL))
  {
    throttle = 0;
    for (unsigned long starttime = micros(); 
         (micros() - starttime < RISE_TIME_US) ; 
         throttle = ((micros() - starttime)*100.0f)/RISE_TIME_US)
    {
      throttlems = set_esc(throttle);
      delay(10); //some delay after setting new PWM value
      TEST_CANCEL;
      weight = abs(read_scale()); //~50ms to read
      
      Serial.print((micros() - absstart)/1000000.0f);
      Serial.print("\t");
      Serial.print(throttle);
      Serial.print("\t");
      Serial.print(throttlems);
      Serial.print("\t");
      Serial.println(weight);
    }

    for (unsigned long starttime = micros(); 
         (micros() - starttime < STALL_TIME_US) ; 
         throttle = THROTTLE_LIMIT)
    {
      throttlems = set_esc(throttle);
      delay(10); //some delay after setting new PWM value
      TEST_CANCEL;
      weight = abs(read_scale()); //~50ms to read
      
      Serial.print((micros() - absstart)/1000000.0f);
      Serial.print("\t");
      Serial.print(throttle);
      Serial.print("\t");
      Serial.print(throttlems);
      Serial.print("\t");
      Serial.println(weight);
    }
  }

  if (mode == RISE_FALL)
  {
    throttle = 100;
    for (unsigned long starttime = micros(); 
         (micros() - starttime < FALL_TIME_US) ; 
         throttle = 100 - (micros() - starttime)*100.0f/RISE_TIME_US)
    {
      throttlems = set_esc(throttle);
      delay(10); //some delay after setting new PWM value
      TEST_CANCEL;
      weight = abs(read_scale()); //~50ms to read
      
      Serial.print((micros() - absstart)/1000000.0f);
      Serial.print("\t");
      Serial.print(throttle);
      Serial.print("\t");
      Serial.print(throttlems);
      Serial.print("\t");
      Serial.println(weight);
    }
  }
  
  stop_esc();
  Serial.println("END TEST");
 
  return 0;  
}


