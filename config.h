/* Configuration file for PropTest */

/*************************************************/
/*                Enable peripherals             */
/*************************************************/

/* enable SDCARD support*/
//#define SD_ENABLE

/*************************************************/
/*                 Define pinouts                */
/*************************************************/
/* PWM pin */
#define PWM_PIN 6

/* TFT pins */
#define TFT_CS 10
#define TFT_DC 9

/* ADC for scale sensor pins */
#define HX711_DOUT 8 
#define HX711_PD_SCK 7 

/* Keyboard pins */ 
#define BUTTON_UP_PIN 2
#define BUTTON_DOWN_PIN 3
#define BUTTON_OK_PIN 5
#define BUTTON_CANCEL_PIN 4

//#define BUTTONS A0 //analog buttons are at A0 pin
#define SENS_CURRENT 0
#define SENS_VOLTAGE 1
#define SENS_VCELLS(n) (n+1) //TBD

/*************************************************/
/*               Define parameters               */
/*************************************************/
#define KEYBOARD_READ_PERIOD 25 //ms
#define HOLD_TIME 2 //seconds
#define KEYBOARD_REPEAT_RATE  10  //times per sec
#define KEYBOARD_REPEAT_DELAY 500 //msec

#define SCALE_DIVIDOR_G 412
#define CURRENT_DIVIDOR_A 18.5f
#define VOLTAGE_DIVIDOR_V 43.72f

#define ESC_OFF 899
#define ESC_MIN 1000
#define ESC_MAX 2000

#define THRUST_LIMIT 5000
#define THROTTLE_LIMIT 100

#define RISE_TIME 10 //seconds
#define STALL_TIME 1 //seconds
#define FALL_TIME 10 //seconds

