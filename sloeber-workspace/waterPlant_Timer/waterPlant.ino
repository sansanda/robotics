/**
 *
 * Version 1.0 del proyecto para automatizar el riego de una planta.
 *
 * Actualmente se basa en las siguentes particularidades:
 *
 * 1. CIRCUITO DEL SENSOR DE HUMEDAD
 * Como sensor de humedad utiliza dos barras metálicas de unos 200mm de largo y separadas 10mm. Practicamente se comporta como un elemento curra resistencia
 * varia en funcion de la huemdad del suelo. Habría que determinar si esta variación es lineal pero de moemnto ya nos vale.
 * Este sensor se coloca en serie con una R de 1K formando un divisor resistivo.
 * Los extremos de este divisor resistivo se conectan cada uno a un pin digital del arduino (D7 y D8) para su polarización bipolar (circulación de corrient en ambos sentidos)
 * y así evitar la electrólisis cada vez que se procede a la medida de voltaje la toma media.
 * La toma media de este sensor se conecta a la entrada analogica del arduino, la A0, para la lectura de la tensión en el punto medio. Esta tension será indicativo de la humedad
 * del suelo de la planta.
 *
 * 2. CIRCUITO DE ALIMENTACIÓN Y CONTRO DEL RIEGO
 * Utilizamos una bomba periestaltica cuyo eje se acciona mediante un motor CC de 6V alimentado a través de un puente en H con una pila de 9V.
 *
 * 3. ALIMENTACION DEL ARDUINO
 * Por lo pronto la alimentacion del arduino es via usb
 *
 * 4. ASPECTOS A MEJORAR EN LAS PROXIMAS VERSIONES
 *
 * 		4.1 Uso de timer, interrupciones y rutinas para la automatizacion de la medida de la humedad del suelo y el riego
 * 		4.2 Añadir un display para que, cuando apretemos un boton nos muestre la lectura actual de la humedad del suelo y los diferentes parametros del control
 * 		los valores de min y max.
 * 		4.3 Añadir la opcion de modificar los parametros de control de manera externa mediante un teclado.
 *
 * Este sensor se pincha en la tierra hasta la mitad aprox.
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
git
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



//Pines para el control de puente en H
#define IN1 2
#define IN2 3
#define BRIDGE_ACTIVATION_PIN 4

//Pines utilizados para el sensor de humedad
#define D7 7
#define D8 8
#define A0 14


//pines utilizados para el control del display I2C de 0.91"
#define D6 6
#define ANCHO_PANTALLA 128 // ancho pantalla OLED
#define ALTO_PANTALLA 64 // alto pantalla OLED


//Variables de control de los niveles de humedad
double moistureThresholdMin = 28.0; 		//60.0
double moistureThresholdMax = 30.0; 		//75.0
double brokenMoistureSensor_Threshold = 0.0;//3.0. Cuando la humedad medida está por debajo de este valor se considera que algo ha ocurrido con el sensor.
		 	 	 	 	 	 	 	 	 	// Por ejemplo el sensor puede estar desconectado o roto el cable. Un valor tan bajo siempre indica una corriente
											// muy baja por el divisor de tension que forman la R=1k y el sensor de humedad del suelo.

//Variables para la medidad de la humedad
double 			lastMoistureMeasure;
unsigned long 	takeCareOfPlantPeriod_in_secs 	= 3600; //3600

//Variables para el control del riego de la planta
bool 			enableWatering		= true;
unsigned long 	wateringTime_ms 	= 5000;
unsigned long	delayBetweenWateringTimes_ms = 120000;


//valores de la regresion lineal de la funcion que relaciona la lectura del arduino (x = digital) con el porcentaje de humedad del suelo (y)
//Cuando el sustrato se encuentra practicamente seco, el valor que lee el arduino en el divisor de tension es 900.
//Cuando el sensor se introduce en agua el valor que lee el arduino es 0.
float b = 100.0;
float m = -b/900.0;

//Display
// Objeto de la clase Adafruit_SSD1306
//Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

//The setup function is called once at startup of the sketch
void setup()
{

	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
		Serial.println(F("SSD1306 allocation failed"));
		for(;;); // Don't proceed, loop forever
	}

	// initialize serial communication at 9600 bits per second:
	Serial.println("Initializing serial communication");
	Serial.begin(9600);
	delay(100);

	// Add your initialization code here

	pinMode(LED_BUILTIN, OUTPUT);

	//Definimos como modo salida los pines IN1 y IN2 (digitales) que servirán para controlar la salida 1 del doble puente en H que es el L298N
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);

	//Definimos como modo salida los pines D7 y D8 (digitales) que servirán para polarizar el sensor de humedad del suelo (moisture sensor)
	pinMode(D7, OUTPUT);
	pinMode(D8, OUTPUT);

	//Definimos como modo salida los pines D7 y D8 (digitales) que servirán para polarizar el sensor de humedad del suelo (moisture sensor)
	pinMode(D6, OUTPUT);


	//Definimos como modo salida el pin BRIDGE_ACTIVATION_PIN = 4 que serirá para alimentar la lógica del puente en H.
	pinMode(BRIDGE_ACTIVATION_PIN, OUTPUT);


	//Definimos como modo entrada el pin A0 (Analogico) para la lectura del divisor resistivo formado por un R=1k y el sensor de humedad del suelo
	pinMode(A0, INPUT);

	//Initializing outputs
	digitalWrite(LED_BUILTIN, LOW);
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
	digitalWrite(D7, LOW);
	digitalWrite(D8, LOW);
	digitalWrite(D6, LOW);
	digitalWrite(BRIDGE_ACTIVATION_PIN, LOW);

}

// The loop function is called in an endless loop
void loop()
{
	takeCareOfPlant(); // @suppress("Invalid arguments")
	delay(takeCareOfPlantPeriod_in_secs*1000);
}



//****************************************
//FIN CONFIGURACION TIMER E INTERRUPCIONES
//****************************************

void takeCareOfPlant()
{

	blinkBuiltINLed(50); // @suppress("Invalid arguments")

	lastMoistureMeasure = checkMoisture(D7, D8, A0); // @suppress("Invalid arguments")

	updateDisplay2(moistureThresholdMin, moistureThresholdMax, lastMoistureMeasure);

	if (isSoilMoistureSensorBroken(lastMoistureMeasure)) // @suppress("Invalid arguments")
	{
		//The sensor is broken. We cannot continue
	}
	else
	{
		if ((lastMoistureMeasure>moistureThresholdMin)) {
			//Don't do anything
			Serial.println("Moisture above = " + String(moistureThresholdMin));
		}
		else
		{
			Serial.println("Moisture value is under the minimum = " + String(moistureThresholdMin));
			if (enableWatering)
			{
				while (lastMoistureMeasure<moistureThresholdMax)
				{

					waterPlant(IN1,IN2,wateringTime_ms); // @suppress("Invalid arguments")
					lastMoistureMeasure = checkMoisture(D7, D8, A0); // @suppress("Invalid arguments")
					if (isSoilMoistureSensorBroken(lastMoistureMeasure)) // @suppress("Invalid arguments")
					{
						//The sensor is broken. We cannot continue
						break;
					}

					delay(delayBetweenWateringTimes_ms);
				}
			}
			else
			{
				Serial.println("Watering is disabled. Then, we won't water the plant");
			}

		}
	}
}

bool isSoilMoistureSensorBroken(double moistureMeasure)
{
	bool BrokenMoistureSensor = false;

	if (lastMoistureMeasure<brokenMoistureSensor_Threshold)
	{
		//No conduce corriente o esta es muy baja. Posible rotura del sensor o del cable o fallo en la conexion con el Arduino
		Serial.println("OJO!!!! POSIBLE ROTURA DEL CABLE DEL SENSOR O FALLO EN LA CONEXION CON EL ARDUINO.");
		BrokenMoistureSensor = true;
	}

	return BrokenMoistureSensor;
}

double checkMoisture(int positivePin, int negativePin, int channelLecture)
{

	Serial.println("Checking plant moisture value....");

	unsigned int  a0_lecture = readMoistureSensor(D7, D8, A0); // @suppress("Invalid arguments")

	Serial.println("Plant Moisture Lecture = " + String(a0_lecture));

	double moistureLecture = (m * a0_lecture) + b;

	Serial.println("Plant Moisture in percent = " + String(moistureLecture));

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
	Serial.println("Proceding to water the plant....");

	digitalWrite(BRIDGE_ACTIVATION_PIN, HIGH); //Activación de la lógica de control del puente en H

	delay(200);

	digitalWrite (controlPin1, HIGH);
	digitalWrite (controlPin2, LOW);

	delay(wateringTime_ms);

	digitalWrite (controlPin1, LOW);
	digitalWrite (controlPin2, LOW);

	digitalWrite(BRIDGE_ACTIVATION_PIN, LOW); //Desactivación de la lógica de control del puente en H

}

void blinkBuiltINLed(int times)
{
	for (int i=times;i>0;i--)
	{
		digitalWrite(LED_BUILTIN,HIGH);
		delay(times);
		digitalWrite(LED_BUILTIN,LOW);
		delay(times);
	}
}

void updateDisplay(double min, double max, double lastMoistureMeasure)
{
	// Clear the buffer
	display.clearDisplay();
	display.display();

	// Set color of the text
	display.setTextColor(SSD1306_WHITE);
	// Set position of cursor
	display.setCursor(10, 5);
	// Set text size multiplier (x1 standard size)
	display.setTextSize(1);
	// print text like Serial
	display.print("MIN:"+ String(min,1) + "--MAX:"+ String(max,1));

	// Set position of cursor
	display.setCursor(10, 18);
	// print text like Serial
	display.print("Actual value:"+ String(lastMoistureMeasure,1));


	display.display();

}

void updateDisplay2(double min, double max, double lastMoistureMeasure)
{
	// Clear the buffer
	display.clearDisplay();
	display.display();

	// Set color of the text
	display.setTextColor(SSD1306_WHITE);
	// Set position of cursor
	display.setCursor(10, 5);
	// Set text size multiplier (x1 standard size)
	display.setTextSize(2);
	// print text like Serial
	display.print(String(min,0) +"-"+ String(max,0) +"-"+ String(lastMoistureMeasure,0));

	display.display();

}
