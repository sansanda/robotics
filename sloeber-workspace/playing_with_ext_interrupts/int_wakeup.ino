#include <avr/sleep.h>

bool led_builtin_state = 0;
bool interrupt_received_flag = false;

void wake ()
{
	// cancel sleep as a precaution
	sleep_disable();
	// precautionary while we do other stuff
	detachInterrupt (0);

	interrupt_received_flag = true;

}  // end of wake

void setupInSleepingModeAndListenInterrupts()
{
	//COnfigure again for interrupts
	// disable ADC
	ADCSRA = 0;

	set_sleep_mode (SLEEP_MODE_PWR_DOWN);
	sleep_enable();

	// Do not interrupt before we go to sleep, or the
	// ISR will detach interrupts and we won't wake.
	noInterrupts();

	// will be called when pin D2 goes low
	attachInterrupt (0, wake, FALLING);
	EIFR = bit (INTF0);  // clear flag for interrupt 0

	// We are guaranteed that the sleep_cpu call will be done
	// as the processor executes the next instruction after
	// interrupts are turned on.
	interrupts ();  // one cycle
	sleep_cpu ();   // one cycle
}

void setup ()
{
	Serial.begin(9600);
	pinMode(2,INPUT);  // enable pull-up on D2
	pinMode(LED_BUILTIN, OUTPUT);

	setupInSleepingModeAndListenInterrupts(); // @suppress("Invalid arguments")

}  // end of setup

void loop ()
{
	if (interrupt_received_flag)
	{
		myDelay(1000); // @suppress("Invalid arguments")

		//code for wake function
		if(led_builtin_state)
		{
		  digitalWrite(LED_BUILTIN, LOW);
		  led_builtin_state = 0;
		}
		else
		{
		  digitalWrite(LED_BUILTIN, HIGH);
		  led_builtin_state = 1;
		}

		interrupt_received_flag = false;

		setupInSleepingModeAndListenInterrupts(); // @suppress("Invalid arguments")
	}

} // end of loop

void myDelay(unsigned long delayInMillis)
{
	unsigned long actualTime = millis();
	unsigned long deadTime = actualTime + delayInMillis;


	while (actualTime<deadTime)
	{
		actualTime = millis();
	}
}
