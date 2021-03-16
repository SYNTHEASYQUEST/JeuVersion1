
#include <iostream>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <wiringPi.h>
#include <arpa/inet.h>

#include "Led.h"

// Broche LED - La broche WiringPi 0 est BCM_GPIO 17.
// nous devons utiliser la numérotation BCM au moment de l'initialisation à l'aide de wiringPiSetupSys
// si vous choisissez un autre numéro de broche, utilisez la numérotation BCM, et
// mettez à jour la commande Pages de propriétés - Événements de build - Événement postbuild distant
// qui utilise l'exportation gpio pour la configuration de wiringPiSetupSys
//#define	LED	17

/*int main(void)
{
	wiringPiSetupSys();

	pinMode(LED, OUTPUT);

	while (true)
	{
		digitalWrite(LED, HIGH);  // Activé
		delay(5000); // ms
		digitalWrite(LED, LOW);	  // Désactivé
		delay(5000);
	}
	return 0;
}*/






//#pragma comment(lib,"Ws2_32.lib")
using namespace std;


int main()
{
	// Création d'un objet de type led

	Led led{};

	//Attacher le socket à une adresse IP et un port

	int socket_in =socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in server;
	server.sin_addr.s_addr = INADDR_ANY; //accepte toutes les adresses
	server.sin_family = AF_INET;
	server.sin_port = htons(54000); //Conversion little to big endian

	if (bind(socket_in, (sockaddr*)&server, sizeof(server)) == -1)
	{
		cout << "Erreur pas de bind !!" << errno << endl;

	}

	//Information du client

	sockaddr_in client;
	socklen_t clientlength = sizeof(client);
	
	cout << "Server running, expecting connection..." << endl;

	char message[1024];

	//Boucle d'attente

	while (true)
	{
		
		int bit_recu = recvfrom(socket_in, message, 1024, 0, (sockaddr*)&client,&clientlength);
		if (bit_recu == -1)
		{
			cout << "Error receiving from client" << errno << endl;
			continue;
		}


		//Affichage du message et les infos du client

		char Ip_du_client[256];
		//ZeroMemory(Ip_du_client, 256);

		inet_ntop(AF_INET, &client.sin_addr, Ip_du_client, 256);


		cout << "Message reçu de la part de " << Ip_du_client << ":" << message << endl;

		
		int etat_capteur = led.detection_capteur();
		
		if (etat_capteur() == 1) {
		
			int num_port = led.getPortLed();
			led.blinking_led(num_port);

		}

	
		
		//tester un appui sur le capteur
	

	}

	//Fermeture du socket

	close(socket_in);



	return 0;
}


