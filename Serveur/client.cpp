#include <iostream>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <wiringPi.h>
#include <arpa/inet.h>


//#pragma comment(lib,"ws2_32.lib")

using namespace std;

void main(int argc, char* argv[]) //On pourra récupérer les éléments de la ligne de commande
{

	//Information sur le serveur avec lequel on communique

	sockaddr_in serveur;
	serveur.sin_family = AF_INET;
	serveur.sin_port = htons(54000);
	inet_pton(AF_INET, "192.168.0.211", &serveur.sin_addr);


	//Création du socket

	SOCKET socket_out = socket(AF_INET, SOCK_DGRAM, 0);

	//Ecriture du message à transmettre

	string message_client(argv[1]);
	int octets_envoyes = sendto(socket_out, message_client.c_str(), message_client.size() + 1, 0, (sockaddr*)&serveur, sizeof(serveur));

	if (octets_envoyes ==-1)
	{
		cout << "Quelque chose dans l'envoi n'a pas fonctionné" << WSAGetLastError();


	}


	//Fermeture du socket

	close(socket_out);




}





























