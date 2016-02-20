
#include "keyboard.h"
#include "config.h"
#include "arduino.h"
#include "main.h"
#include "MsTimer2.h"

const int BUTTON_HOLD_FRAMES = ((HOLD_TIME*1000)/KEYBOARD_READ_PERIOD);
const int KEYBOARD_REPEAT_PERIOD = (1000/KEYBOARD_REPEAT_RATE);

const char BUTTON_PINS[] = {BUTTON_UP_PIN, BUTTON_DOWN_PIN, BUTTON_OK_PIN, BUTTON_CANCEL_PIN};
static char button_press_state[NUM_BUTTONS];
static char button_release_state[NUM_BUTTONS];

/************************************
 * Name    : init_keyboard
 * Purpuse : Initialize keyboard pins and variables
 * Inputs  : None
 * Outputs : None
 * Returns : None
 ************************************/
void init_keyboard()
{
	
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    button_press_state[i] = 0;
    button_release_state[i] = 0;
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  MsTimer2::set (KEYBOARD_READ_PERIOD, read_keyboard); 
  MsTimer2::start ();  
}

/************************************
 * Name    : clear_keyboard
 * Purpuse : Clear keyboard states
 * Inputs  : None
 * Outputs : None
 * Returns : None
 ************************************/
void clear_keyboard()
{
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    button_press_state[i] = 0;
    button_release_state[i] = 0;
  }
}

/************************************
 * Name    : read_keyboard
 * Purpuse : This funnction is called on timer2 interrupt
 * Inputs  : None
 * Outputs : None
 * Returns : None
 ************************************/
void read_keyboard()
{
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    if (digitalRead(BUTTON_PINS[i]))
    {
      button_press_state[i]++;
    }
    else
    {
      button_press_state[i] = 0;
    }
  }
}

/************************************
 * Name    : button_pressed
 * Purpuse : Returns the button press status
 * Inputs  : id - button ID
 * Outputs : None
 * Returns : 1 if button is pressed now (according to repeat rate), 0 otherwise
 ************************************/
int button_pressed(char id)
{
  /* TBD * Add repeat rate * TBD */
  /* do not clear button_press_state[i] - only return state */
  return (button_press_state[id] > 0);
}

/************************************
 * Name    : button_released
 * Purpuse : Returns the button release status
 * Inputs  : id - button ID
 * Outputs : None
 * Returns : 1 if button has been released, 0 otherwise
 ************************************/
int button_released(char id)
{
  /* When button is pressed, set flag...
   * and then wait for button release.
   * If button_hold event got, flag is also cleared */
  if (button_press_state[id] > 0)
  {
    /* Set flag that we are waiting for button_release */
    button_release_state[id] = 1;
  }
  else if (button_press_state[id] == 0)
  {
    if ( button_release_state[id] == 1)
    {
      button_release_state[id] = 0;
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    ASSERT(false, "button_released: negative button_press_state");
  }
  return -1;
}

/************************************
 * Name    : button_hold
 * Purpuse : Returns the button hold status
 * Inputs  : id - button ID
 * Outputs : None
 * Returns : 1 if button has been hold for more than 2 seconds, 0 otherwise
 ************************************/
int button_hold(char id)
{
 if (button_press_state[id] > BUTTON_HOLD_FRAMES)
 {
   button_release_state[id] = 0;
   return 1;
 }
 else
 {
   return 0;
 }
}

