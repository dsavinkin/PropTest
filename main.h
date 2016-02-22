/**************** General Macros *****************/
#define ASSERT(condition, text) if (!(condition)) { Serial.print("ASSERT: "); Serial.println(text);}
#define UBound(n)               sizeof(n) / sizeof(n[0])

#define TEST_CANCEL if ((button_pressed(BUTTON_CANCEL)) || (button_released(BUTTON_CANCEL))) \
                    { \
                      stop_esc(); \
                      return 1; \
                      Serial.println("CANCELED"); \
                    }

//#define LOG_STATE(p1, p2, p3) 


/* Keyboard buttons IDs */
typedef enum
{
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_OK,
	BUTTON_CANCEL,
	NUM_BUTTONS
} BUTTONS;

/* Test Mode IDs */
typedef enum
{
  RISE,
  RISE_FALL,
  CONST_AMP,
  CONST_WATT,
  CONST_THRO
} TEST_MODES;


