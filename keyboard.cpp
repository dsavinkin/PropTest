
#include "keyboard.h"
#include "config.h"
#include "arduino.h"
#include "main.h"

#define HOLD_TIME 2 //seconds
const int BUTTON_HOLD_FRAMES = ((HOLD_TIME*1000)/KEYBOARD_READ_PERIOD);

#define KEYBOARD_REPEAT_RATE  10  //times per sec
#define KEYBOARD_REPEAT_DELAY 500 //msec
const int KEYBOARD_REPEAT_PERIOD = (1000/KEYBOARD_REPEAT_RATE);

#define NUM_BUTTONS 4
const char BUTTONS[NUM_BUTTONS] = {BUTTON_UP, BUTTON_DOWN, BUTTON_OK, BUTTON_CANCEL};
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
    pinMode(BUTTONS[i], INPUT_PULLUP);
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
    if (digitalRead(BUTTONS[i]))
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
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    if (BUTTONS[i] == id)
    {
      /* do not clear button_press_state[i] - only return state */
      return (button_press_state[i] > 0);
    }
  } 
  ASSERT(false, "button_pressed: wrong id");
  return -1;   
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
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    if (BUTTONS[i] == id)
    {
      if (button_press_state[i] > 0)
      {
        /* Set flag that we are waiting for button_release */
        button_release_state[i] = 1;
      }
      else if (button_press_state[i] == 0)
      {
        if ( button_release_state[i] == 1)
        {
          button_release_state[i] = 0;
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
    }
  } 
  ASSERT(false, "button_released: wrong id");
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
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    if (BUTTONS[i] == id)
    {
      if (button_press_state[i] > BUTTON_HOLD_FRAMES)
      {
        button_release_state[i] = 0;
        return 1;
      }
      else
      {
        return 0;
      }
    }
  } 
  ASSERT(false, "button_hold: wrong id");
  return -1;   
}

