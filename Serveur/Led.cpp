#include "Led.h"
#include <iostream>

Led::Led(int num_port)
{	
	numero_port = num_port;
	std::cout << "Construction d'un objet de la classe Led, lié au port:" << numero_port << endl;
	pinMode(numero_port, OUTPUT); //definir le port de la led comme sortie
	pinMode(0, INPUT); //capteur en définit comme une entrée

}

void Led::blinking_led(int num_port)
{
	digitalWrite(num_port,!digitalRead(num_port));
	delay(500);

}

int Led::detection_capteur()
{
	int etat_capteur = 0;
	if (digitalRead(0) == 1) {
		etat_capteur = 1;
	}

	return etat_capteur;


}

int Led::getPortLed()
{
	return numero_port;
}








