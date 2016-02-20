/**************** General Macros *****************/
#define ASSERT(condition, text) if (!(condition)) { Serial.print("ASSERT: "); Serial.println(text);}
#define UBound(n)               sizeof(n) / sizeof(n[0])

/* Keyboard buttons IDs */
typedef enum
{
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_OK,
	BUTTON_CANCEL,
	NUM_BUTTONS
} BUTTONS;
