#include "Arduino.h"
//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(9600);
	pinMode(LED_BUILTIN, OUTPUT);

// Add your initialization code here
}

void initADC()
{
	ADMUX = 0x00; 	//Select channel 0 of ADC

	//Set ADC module prescalar to 8
	ADCSRA = 0x03;

}

void startADC()
{
	ADCSRA = ADCSRA || 0xC0;	// start conversion

	while (!(ADCSRA & 0x10))
	{
		Serial.print("waiting");
		//Check if conversation is ready
	}
	ADCSRA = ADCSRA || 0x10; //Clear conv rdy flag - set the bit

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
	startADC();
	blinkBuiltINLed(10,200);

}
