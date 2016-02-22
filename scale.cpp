#include "config.h"
#include "scale.h"
#include <HX711.h>

HX711 scale(HX711_DOUT, HX711_PD_SCK);    // parameter "gain" is ommited; the default value 128 is used by the library

void init_scale()
{
	Serial.println("HX711 Demo");

	Serial.println("Before setting up the scale:");
	Serial.print("read: \t\t");
	unsigned long start = micros();  

	Serial.println(scale.read());      // print a raw reading from the ADC
	Serial.println(micros() - start);

	Serial.print("read average(20): \t\t");
	start = 0;
	Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC
	Serial.println(micros() - start);

	Serial.print("get value(5): \t\t");
	start = micros();
	Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)
	Serial.println(micros() - start);

	Serial.print("get units(5): \t\t");
	start = micros();
	Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided 
	Serial.println(micros() - start);
	start = micros();
	// by the SCALE parameter (not set yet)  

	// scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
	start = micros();
	scale.set_scale(SCALE_DIVIDOR_G);                      // this value is obtained by calibrating the scale with known weights; see the README for details
	Serial.println(micros() - start);
	start = micros();
	Serial.println("tare:");
	scale.tare();               // reset the scale to 0
	Serial.println(micros() - start);

	Serial.println("After setting up the scale:");

	Serial.print("read: \t\t");
	start = micros();
	Serial.println(scale.read());                 // print a raw reading from the ADC
	Serial.println(micros() - start);

	Serial.print("read average(20): \t\t");
	start = micros();
	Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC
	Serial.println(micros() - start);

	Serial.print("get value(5): \t\t");
	start = micros();
	Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()
	Serial.println(micros() - start);

	Serial.print("get units(5): \t\t");
	start = micros();
	Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided 
	Serial.println(micros() - start);
	start = micros();
	// by the SCALE parameter set with set_scale

  scale.power_up();  
}

float read_scale()
{
	return (scale.get_units(1));
}

void tare_scale()
{
    scale.tare();	
}
