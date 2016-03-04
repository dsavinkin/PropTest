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

/* Set 3v3 ADC reference */  
  analogReference(EXTERNAL);

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
  //scale.power_up();  
  float weight = read_scale();
  float current = ((float)analogRead(SENS_CURRENT))/CURRENT_DIVIDOR_A;
  float voltage = ((float)analogRead(SENS_VOLTAGE))/VOLTAGE_DIVIDOR_V;
  //scale.power_down();              // put the ADC in sleep mode

  /*
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
*/
  if (button_released(BUTTON_OK))
  {
    start_test(RISE_FALL);
  }

  if (button_released(BUTTON_CANCEL))
  {
    stop_esc();
  }


    print_item(1, "Time     ", 0, "s");
    print_item(2, "Throttle ", 0, "%");
    print_item(3, "Thrust   ", weight, "g");
    print_item(4, "Current  ", current, "A");
    print_item(5, "Voltage  ", voltage, "V");
    print_item(6, "Watt     ", voltage*current, "W");


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
//  delay(1000);
  
}


/************************************ 
 * Name    : log_state
 * Purpuse : Read and log sensors data to Serial
 * Inputs  : ttime
 *           throttle
 *           throttlems
 * Outputs : None
 * Returns : None
 ************************************/
int log_state(float ttime, float throttle, int throttlems)
{

  if (ttime >= 0)
  {
    float weight = abs(read_scale());  
    float current = ((float)analogRead(SENS_CURRENT))/CURRENT_DIVIDOR_A;
    float voltage = ((float)analogRead(SENS_VOLTAGE))/VOLTAGE_DIVIDOR_V;
    float watt = voltage*current;
    float eff = 0;
    if ((watt != 0) && (throttle > 25)) 
    {
      eff = weight/watt;
    }
      
    Serial.print(ttime);
    Serial.print("\t");
    Serial.print(throttle);
    Serial.print("\t");
    Serial.print(throttlems);
    Serial.print("\t");
    Serial.print(weight);
    Serial.print("\t");
    Serial.print(current);
    Serial.print("\t");
    Serial.print(voltage);
    Serial.print("\t");
    Serial.print(watt);
    Serial.print("\t");
    Serial.print(eff);
    Serial.println();
/*
    print_item(1, "Time     ", ttime, "s");
    print_item(2, "Throttle ", throttle, "%");
    print_item(3, "Thrust   ", weight, "g");
    print_item(4, "Current  ", current, "A");
    print_item(5, "Voltage  ", voltage, "V");
    print_item(6, "Watt     ", watt, "W");
    print_item(7, "EFF      ", eff, "g/W");
*/    
  }
  else
  {
    Serial.print("Time");
    Serial.print("\t");
    Serial.print("Trottle");
    Serial.print("\t");
    Serial.print("_MS");
    Serial.print("\t");
    Serial.print("Thrust");
    Serial.print("\t");
    Serial.print("Current");
    Serial.print("\t");
    Serial.print("Voltage");
    Serial.print("\t");
    Serial.print("Watt");    
    Serial.print("\t");
    Serial.print("g/W");    
    Serial.println();
  }
  
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
  log_state(-1, 0, 0);
  //scale.power_up();  
  
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
      log_state((micros() - absstart)/1000000.0f, throttle, throttlems);
    }

    for (unsigned long starttime = micros(); 
         (micros() - starttime < STALL_TIME_US) ; 
         throttle = THROTTLE_LIMIT)
    {
      throttlems = set_esc(throttle);
      delay(10); //some delay after setting new PWM value
      TEST_CANCEL;
      log_state((micros() - absstart)/1000000.0f, throttle, throttlems);
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
      log_state((micros() - absstart)/1000000.0f, throttle, throttlems);
    }
  }
  
  stop_esc();
  Serial.println("END TEST");

  //scale.power_down();  
 
  return 0;  
}


