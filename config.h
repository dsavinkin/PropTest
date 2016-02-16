/* Configuration file for PropTest */

//#define SD_ENABLE

#define FONTSIZE   2
#define TEXTSIZE   FONTSIZE*8
#define SPACING    2
#define PERIOD     TEXTSIZE+SPACING

// For the Adafruit shield, these are the default.
#define TFT_CS 10
#define TFT_DC 9

#define HX711_DOUT 8 
#define HX711_PD_SCK 7 

#ifdef SD_ENABLE
  #define SD_CS 6
  // set up variables using the SD utility library functions:
  Sd2Card card;
#endif
