/* Configuration file for PropTest */

//#define SD_ENABLE


// For the Adafruit shield, these are the default.
#define TFT_CS 10
#define TFT_DC 9

#define HX711_DOUT 8 
#define HX711_PD_SCK 7 

#ifdef SD_ENABLE
  #define SD_CS 6
#endif

#define BUTTONS A0 //analog buttons are at A0 pin
#define SENS_CURRENT A1
#define SENS_VOLTAGE(n) 
