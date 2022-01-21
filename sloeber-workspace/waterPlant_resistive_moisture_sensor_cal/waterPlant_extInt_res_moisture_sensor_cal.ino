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

#include <avr/sleep.h>




//Pines utilizados para el sensor de humedad resistivo
#define D7 7
#define D8 8
#define A0 14
#define A1 15


//Variables para la medidad de la humedad
unsigned int resistiveMoistureLecture = 0;
unsigned int referenceMoistureLecture = 0;

int resistivesoilmoisturepercent=0;
int referencesoilmoisturepercent=0;

const int RefAirValue = 567;   //you need to replace this value with Value_1
const int RefWaterValue = 289;  //you need to replace this value with Value_2

const int ResAirValue = 1021;   //you need to replace this value with Value_1
const int ResWaterValue = 243;  //you need to replace this value with Value_2


bool interrupt_received_flag = false;



void takeCareOfPlant()
{
	resistiveMoistureLecture = readResistiveMoistureSensor(D7, D8, A0); // @suppress("Invalid arguments")
	referenceMoistureLecture = readReferenceMoistureSensor(A1); // @suppress("Invalid arguments")

	resistivesoilmoisturepercent = map(resistiveMoistureLecture, ResAirValue, ResWaterValue, 0, 100);
	referencesoilmoisturepercent = map(referenceMoistureLecture, RefAirValue, RefWaterValue, 0, 100);


	Serial.print("resistive Lecture = " + String(resistiveMoistureLecture) + "\t" + "percent = " + String(resistivesoilmoisturepercent) + "\t" + "reference Lecture = " + String(referenceMoistureLecture) + "\t" +  "percent = " + String(referencesoilmoisturepercent) + "\n");




}


//The setup function is called once at startup of the sketch
void setup()
{

	Serial.begin(9600);

	// Add your initialization code here

	pinMode(LED_BUILTIN, OUTPUT);

	pinMode(2,INPUT);  // Enable interrupt input D2 as input


	//Definimos como modo salida los pines D7 y D8 (digitales) que servirán para polarizar el sensor de humedad del suelo (moisture sensor)
	pinMode(D7, OUTPUT);
	pinMode(D8, OUTPUT);




	//Definimos como modo entrada el pin A0 (Analogico)
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);

	//Initializing outputs
	digitalWrite(LED_BUILTIN, LOW);
	digitalWrite(D7, LOW);
	digitalWrite(D8, LOW);

}

// The loop function is called in an endless loop
void loop()
{
	myDelay(60000);
	takeCareOfPlant();
}


//****************************************
//FIN CONFIGURACION TIMER E INTERRUPCIONES
//****************************************


unsigned int readResistiveMoistureSensor(int positivePin, int negativePin, int channelLecture)
{
	unsigned int humidityLecture;

	myDelay(1000);

	digitalWrite(positivePin, HIGH);
	digitalWrite(negativePin, LOW);

	myDelay(1000);

	humidityLecture = analogRead(channelLecture); //devuelve un valor entre 0 y 1024 propio de un adc de 10 bits

	myDelay(100);

	digitalWrite(positivePin, LOW);
	digitalWrite(negativePin, HIGH);

	myDelay(1100);

	digitalWrite(D7, LOW);
	digitalWrite(D8, LOW);

	return humidityLecture;
}

unsigned int readReferenceMoistureSensor(int channelLecture)
{
	unsigned int humidityLecture;

	humidityLecture = analogRead(channelLecture); //devuelve un valor entre 0 y 1024 propio de un adc de 10 bits

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
