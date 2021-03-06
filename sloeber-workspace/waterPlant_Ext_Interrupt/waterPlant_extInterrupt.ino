/**
 *
 * Version 1.0 del proyecto para automatizar el riego de una planta.
 *
 * Actualmente se basa en las siguentes particularidades:
 *
 * 1. CIRCUITO DEL SENSOR DE HUMEDAD
 * Como sensor de humedad utiliza dos barras met?licas de unos 200mm de largo y separadas 10mm. Practicamente se comporta como un elemento curra resistencia
 * varia en funcion de la huemdad del suelo. Habr?a que determinar si esta variaci?n es lineal pero de moemnto ya nos vale.
 * Este sensor se coloca en serie con una R de 1K formando un divisor resistivo.
 * Los extremos de este divisor resistivo se conectan cada uno a un pin digital del arduino (D7 y D8) para su polarizaci?n bipolar (circulaci?n de corrient en ambos sentidos)
 * y as? evitar la electr?lisis cada vez que se procede a la medida de voltaje la toma media.
 * La toma media de este sensor se conecta a la entrada analogica del arduino, la A0, para la lectura de la tensi?n en el punto medio. Esta tension ser? indicativo de la humedad
 * del suelo de la planta.
 *
 * 2. CIRCUITO DE ALIMENTACI?N Y CONTRO DEL RIEGO
 * Utilizamos una bomba periestaltica cuyo eje se acciona mediante un motor CC de 6V alimentado a trav?s de un puente en H con una pila de 9V.
 *
 * 3. ALIMENTACION DEL ARDUINO
 * Por lo pronto la alimentacion del arduino es via usb
 *
 * 4. ASPECTOS A MEJORAR EN LAS PROXIMAS VERSIONES
 *
 * 		4.1 Uso de timer, interrupciones y rutinas para la automatizacion de la medida de la humedad del suelo y el riego
 * 		4.2 A?adir un display para que, cuando apretemos un boton nos muestre la lectura actual de la humedad del suelo y los diferentes parametros del control
 * 		los valores de min y max.
 * 		4.3 A?adir la opcion de modificar los parametros de control de manera externa mediante un teclado.
 *
 * Este sensor se pincha en la tierra hasta la mitad aprox.
 */


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/sleep.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



//Pines para el control de puente en H, pines D10, D11 y D12
#define IN1 10
#define IN2 11
#define BRIDGE_ACTIVATION_PIN 12

//Pines utilizados para el sensor de humedad
#define D7 7
#define D8 8
#define A0 14

//Variables de control de los niveles de humedad
double 	moistureThresholdMin 			= 22.0; //60.0
double 	moistureThresholdMax 			= 26.0; //75.0
double 	brokenMoistureSensor_Threshold = 0.0;	//3.0. Cuando la humedad medida est? por debajo de este valor se considera que algo ha ocurrido con el sensor.
		 	 	 	 	 	 	 	 	 		// Por ejemplo el sensor puede estar desconectado o roto el cable. Un valor tan bajo siempre indica una corriente
												// muy baja por el divisor de tension que forman la R=1k y el sensor de humedad del suelo.

//Variables para la medidad de la humedad
double 			lastMoistureMeasure;

//Variables para el control del riego de la planta
bool 			enableWatering		= false;
unsigned long 	wateringTime_ms 	= 5000; //10000


//valores de la regresion lineal de la funcion que relaciona la lectura del arduino (x = digital) con el porcentaje de humedad del suelo (y)
//Cuando el sustrato se encuentra practicamente seco, el valor que lee el arduino en el divisor de tension es 1024.
//Cuando el sensor se introduce en agua el valor que lee el arduino es 0.
float b = 100.0;
float m = -b/1024.0;

bool interrupt_received_flag = false;

byte adcsra_save;

void wake ()
{
	// cancel sleep as a precaution
	sleep_disable();
	// precautionary while we do other stuff
	detachInterrupt (0);

	//enable various internal modules
	ADCSRA = adcsra_save;

	interrupt_received_flag = true;

}  // end of wake

void takeCareOfPlant()
{
	sendMessageToDisplay("CHECK MOIST"); // @suppress("Invalid arguments")
	lastMoistureMeasure = checkMoisture(D7, D8, A0); // @suppress("Invalid arguments")


	long count = 1000000;
	long i = 0;

	//sendMessageToDisplay(String(lastMoistureMeasure));
	//myDelay(2000);

	if (isSoilMoistureSensorBroken(lastMoistureMeasure)) // @suppress("Invalid arguments")
	{
		sendMessageToDisplay("BROKEN SENSOR!!"); // @suppress("Invalid arguments")
	}
	else
	{
		sendMoistureParametersToDisplay(moistureThresholdMin, moistureThresholdMax, lastMoistureMeasure); // @suppress("Invalid arguments")
		if (lastMoistureMeasure<moistureThresholdMin) enableWatering = true;
		if (lastMoistureMeasure>=moistureThresholdMax) enableWatering = false;
		if (
				(lastMoistureMeasure>moistureThresholdMin && lastMoistureMeasure<moistureThresholdMax && enableWatering)
				|| lastMoistureMeasure<moistureThresholdMin
			)
		{
			//("Moisture value is under the minimum = " + String(moistureThresholdMin));
			waterPlant(IN1,IN2,wateringTime_ms); // @suppress("Invalid arguments")
		}
		sendMoistureParametersToDisplay(moistureThresholdMin, moistureThresholdMax, lastMoistureMeasure); // @suppress("Invalid arguments")
	}
}

void setupInSleepingModeAndListenInterrupts()
{
	//Configure again for interrupts
	// disable various modules but first save the registers
	adcsra_save = ADCSRA; 	//adc
	//prr_save = PRR;			//power reduction register

	ADCSRA = 0;	//turn off adc

	set_sleep_mode (SLEEP_MODE_PWR_DOWN);
	sleep_enable();

	// Do not interrupt before we go to sleep, or the
	// ISR will detach interrupts and we won't wake.
	noInterrupts ();

	// will be called when pin D2 goes low
	attachInterrupt (0, wake, FALLING); // @suppress("Invalid arguments")
	EIFR = bit (INTF0);  // clear flag for interrupt 0

	// turn off brown-out enable in software (for power saving purposes only)
	// BODS must be set to one and BODSE must be set to zero within four clock cycles
	MCUCR = bit (BODS) | bit (BODSE);
	// The BODS bit is automatically cleared after three clock cycles
	MCUCR = bit (BODS);

	// We are guaranteed that the sleep_cpu call will be done
	// as the processor executes the next instruction after
	// interrupts are turned on.
	interrupts ();  // one cycle
	sleep_cpu ();   // one cycle
}

//The setup function is called once at startup of the sketch
void setup()
{

	Serial.begin(9600);

	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
		//(F("SSD1306 allocation failed"));
		for(;;); // Don't proceed, loop forever
	}

	// Add your initialization code here

	pinMode(LED_BUILTIN, OUTPUT);

	pinMode(2,INPUT);  // Enable interrupt input D2 as input

	//Definimos como modo salida los pines IN1 y IN2 (digitales) que servir?n para controlar la salida 1 del doble puente en H que es el L298N
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);

	//Definimos como modo salida los pines D7 y D8 (digitales) que servir?n para polarizar el sensor de humedad del suelo (moisture sensor)
	pinMode(D7, OUTPUT);
	pinMode(D8, OUTPUT);


	//Definimos como modo salida el pin BRIDGE_ACTIVATION_PIN = 4 que serir? para alimentar la l?gica del puente en H.
	pinMode(BRIDGE_ACTIVATION_PIN, OUTPUT);


	//Definimos como modo entrada el pin A0 (Analogico)
	pinMode(A0, INPUT);

	//Initializing outputs
	digitalWrite(LED_BUILTIN, LOW);
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
	digitalWrite(D7, LOW);
	digitalWrite(D8, LOW);
	digitalWrite(BRIDGE_ACTIVATION_PIN, LOW);

	setupInSleepingModeAndListenInterrupts(); // @suppress("Invalid arguments")

}

// The loop function is called in an endless loop
void loop()
{
	if (interrupt_received_flag)
	{
		takeCareOfPlant();
		interrupt_received_flag = false;
		setupInSleepingModeAndListenInterrupts(); // @suppress("Invalid arguments")
	}
}


//****************************************
//FIN CONFIGURACION TIMER E INTERRUPCIONES
//****************************************


bool isSoilMoistureSensorBroken(double moistureMeasure)
{
	bool BrokenMoistureSensor = false;

	if (lastMoistureMeasure<brokenMoistureSensor_Threshold)
	{
		//No conduce corriente o esta es muy baja. Posible rotura del sensor o del cable o fallo en la conexion con el Arduino
		//("OJO!!!! POSIBLE ROTURA DEL CABLE DEL SENSOR O FALLO EN LA CONEXION CON EL ARDUINO.");
		BrokenMoistureSensor = true;
	}

	return BrokenMoistureSensor;
}

double checkMoisture(int positivePin, int negativePin, int channelLecture)
{

	//("Checking plant moisture value....");

	unsigned int  a0_lecture = readMoistureSensor(D7, D8, A0); // @suppress("Invalid arguments")

	//("Plant Moisture Lecture = " + String(a0_lecture));

	double moistureLecture = (m * a0_lecture) + b;

	//("Plant Moisture in percent = " + String(moistureLecture));

	return moistureLecture;
}

unsigned int readMoistureSensor(int positivePin, int negativePin, int channelLecture)
{
	unsigned int humidityLecture;

	delay(1000);

	digitalWrite(positivePin, HIGH);
	digitalWrite(negativePin, LOW);

	delay(1000);

	humidityLecture = analogRead(channelLecture); //devuelve un valor entre 0 y 1024 propio de un adc de 10 bits

	delay(100);

	digitalWrite(positivePin, LOW);
	digitalWrite(negativePin, HIGH);

	delay(1100);

	digitalWrite(D7, LOW);
	digitalWrite(D8, LOW);

	return humidityLecture;
}

void waterPlant(int controlPin1, int controlPin2, unsigned long wateringTime_ms)
{
	//("Proceding to water the plant....");
	sendMessageToDisplay("WATERING");

	digitalWrite(BRIDGE_ACTIVATION_PIN, HIGH); //Activaci?n de la l?gica de control del puente en H

	delay(200);

	digitalWrite (controlPin1, HIGH);
	digitalWrite (controlPin2, LOW);

	delay(wateringTime_ms);

	digitalWrite (controlPin1, LOW);
	digitalWrite (controlPin2, LOW);

	digitalWrite(BRIDGE_ACTIVATION_PIN, LOW); //Desactivaci?n de la l?gica de control del puente en H

}


void sendMoistureParametersToDisplay(double min, double max, double lastMoistureMeasure)
{
	// Clear the buffer
	display.clearDisplay();
	display.display();

	// Set color of the text
	display.setTextColor(SSD1306_WHITE);
	// Set position of cursor
	display.setCursor(0, 5);
	// Set text size multiplier (x1 standard size)
	display.setTextSize(2);
	// print text like Serial

	String signal = "U";
	if (!enableWatering) signal = "D";

	String text = String(min,0) +"-"+ String(max,0) +"-"+ String(lastMoistureMeasure,0) + "-" +signal;
	display.print(text);

	display.display();
}

void sendMessageToDisplay(String message)
{
	// Clear the buffer
	display.clearDisplay();
	display.display();

	// Set color of the text
	display.setTextColor(SSD1306_WHITE);
	// Set position of cursor
	display.setCursor(0, 5);
	// Set text size multiplier (x1 standard size)
	display.setTextSize(2);
	// print text like Serial
	display.print(message);

	display.display();
}

void myDelay(unsigned long delayInMillis)
{
	unsigned long actualTime = millis();
	unsigned long deadTime = actualTime + delayInMillis;


	while (actualTime<deadTime)
	{
		actualTime = millis();
	}
}
