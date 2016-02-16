#include "config.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define FONTSIZE   2
#define TEXTSIZE   FONTSIZE*8
#define SPACING    2
#define PERIOD     TEXTSIZE+SPACING

void init_TFT();
void clear_screen();
int print_item(int line, char *iname, float value, char *unit);

/*****************************************/
/* Test functions */
/*****************************************/
unsigned long testFillScreen();
unsigned long testText();
unsigned long testLines(uint16_t color);
unsigned long testFastLines(uint16_t color1, uint16_t color2);
unsigned long testRects(uint16_t color);
unsigned long testFilledRects(uint16_t color1, uint16_t color2);
unsigned long testFilledCircles(uint8_t radius, uint16_t color);
unsigned long testCircles(uint8_t radius, uint16_t color);
unsigned long testTriangles();
unsigned long testFilledTriangles();
unsigned long testRoundRects();
unsigned long testFilledRoundRects();

