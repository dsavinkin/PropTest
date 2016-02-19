/* Configuration file for PropTest */

/* Future growth - enable SDCARD support*/
//#define SD_ENABLE


// For the Adafruit shield, these are the default.
#define TFT_CS 10
#define TFT_DC 9

#define HX711_DOUT 8 
#define HX711_PD_SCK 7 

#ifdef SD_ENABLE
  #define SD_CS 6
#endif

/* Keyboard pins */ 
#define BUTTON_UP 1
#define BUTTON_DOWN 2
#define BUTTON_OK 3
#define BUTTON_CANCEL 4


//#define BUTTONS A0 //analog buttons are at A0 pin
//#define SENS_CURRENT A1
//#define SENS_VOLTAGE(n) 
