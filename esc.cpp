#include <Arduino.h>
#include <Servo.h>

#include "config.h"
#include "main.h"

Servo esc;

/************************************ 
 * Name    : init_esc
 * Purpuse : Init ESC
 * Inputs  : None
 * Outputs : None
 * Returns : None
 ************************************/
void init_esc()
{
  esc.attach(PWM_PIN);
  esc.writeMicroseconds(ESC_OFF);  
}

/************************************ 
 * Name    : stop_esc
 * Purpuse : stop ESC
 * Inputs  : None
 * Outputs : None
 * Returns : None
 ************************************/
void stop_esc()
{
  esc.writeMicroseconds(ESC_OFF);  
}

/************************************ 
 * Name    : set_esc
 * Purpuse : Set esc value
 * Inputs  : val -  in persentage (0..100)
 * Outputs : None
 * Returns : Written value in MS, or -1 if invald value given.
 ************************************/
int set_esc(float val)
{
  if ((val < 0) && (val > 100))
  {
    ASSERT(false, "set_esc: val out of range");
    return -1;
  }
  
  int valms = ESC_MIN + val*(ESC_MAX-ESC_MIN)/100;
  
  Serial.print("set_esc - ");
  Serial.print(val);
  Serial.print(" - ");
  Serial.println(valms);
  esc.writeMicroseconds(valms);  
  return valms;
}

