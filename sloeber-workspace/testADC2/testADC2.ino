#include "Arduino.h"
//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(9600);
	pinMode(LED_BUILTIN, OUTPUT);

}

void initADC( void)
{
	ADMUX = 0; //Select channel 0
	ADCSRA = 0xC3; //Enable ADC & start 1st dummy
	//conversion
	//Set ADC module prescalar to 8
	//critical for accurate ADC results
	while (!(ADCSRA & 0x10)); //Check if conversation is ready
	ADCSRA |= 0x10; //Clear conv rdy flag - set the bit
}

void blinkBuiltINLed (int _n, int _delay)
{
	int i;

	for(i=0; i<_n; i++)
	{
		digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
		delay(_delay);                       // wait for a second
		digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
		delay(_delay);
	}
}


// The loop function is called in an endless loop
void loop()
{
	initADC();
	blinkBuiltINLed(10,200);
}
