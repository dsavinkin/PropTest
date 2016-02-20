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

/* SDCARD CS pin */
#ifdef SD_ENABLE
  #define SD_CS 6
#endif

/* Keyboard pins */ 
#define BUTTON_UP_PIN 2
#define BUTTON_DOWN_PIN 3
#define BUTTON_OK_PIN 4
#define BUTTON_CANCEL_PIN 5

//#define BUTTONS A0 //analog buttons are at A0 pin
#define SENS_CURRENT A0
#define SENS_VOLTAGE A1
#define SENS_VCELLS(n) A(n+1)

/*************************************************/
/*               Define parameters               */
/*************************************************/
#define KEYBOARD_READ_PERIOD 25 //ms
#define HOLD_TIME 2 //seconds
#define KEYBOARD_REPEAT_RATE  10  //times per sec
#define KEYBOARD_REPEAT_DELAY 500 //msec

