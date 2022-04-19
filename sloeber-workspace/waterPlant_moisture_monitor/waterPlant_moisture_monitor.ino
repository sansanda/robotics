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

#include "Arduino.h"
#include <avr/sleep.h>


//Pines utilizados para el sensor de humedad
#define D7 7
#define D8 8
#define A0 14


//Variables para la medidad de la humedad
double 			lastMoistureMeasure;


//valores de la regresion lineal de la funcion que relaciona la lectura del arduino (x = digital) con el porcentaje de humedad del suelo (y)
//Cuando el sustrato se encuentra practicamente seco, el valor que lee el arduino en el divisor de tension es 1024.
//Cuando el sensor se introduce en agua el valor que lee el arduino es 0.
float b = 100.0;
float m = -b/1024.0;


//The setup function is called once at startup of the sketch
void setup()
{



	// Add your initialization code here

	Serial.begin(9600);

	pinMode(LED_BUILTIN, OUTPUT);


	//Definimos como modo salida los pines D7 y D8 (digitales) que servirán para polarizar el sensor de humedad del suelo (moisture sensor)
	pinMode(D7, OUTPUT);
	pinMode(D8, OUTPUT);

	//Definimos como modo entrada el pin A0 (Analogico)
	pinMode(A0, INPUT);

	//Initializing outputs
	digitalWrite(LED_BUILTIN, LOW);
	digitalWrite(D7, LOW);
	digitalWrite(D8, LOW);

}

// The loop function is called in an endless loop
void loop()
{
	myDelay(5000);
	checkMoisture(D7,D8,A0);

}


//****************************************
//FIN CONFIGURACION TIMER E INTERRUPCIONES
//****************************************


double checkMoisture(int positivePin, int negativePin, int channelLecture)
{

	//("Checking plant moisture value....");

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

void myDelay(unsigned long delayInMillis)
{
	unsigned long actualTime = millis();
	unsigned long deadTime = actualTime + delayInMillis;


	while (actualTime<deadTime)
	{
		actualTime = millis();
	}
}
