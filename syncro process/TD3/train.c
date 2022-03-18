#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "train.h"


/*
 connexion de la socket client
*/

int connexionServeur(const char *adresse_serveur) {

    /* creation socket en mode connecté */
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		perror("socket()");
		exit(errno);
	} else printf("\n --> creation socket [OK]");

	struct sockaddr_in addr;
	addr.sin_addr.s_addr = inet_addr(adresse_serveur);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8082);

	/* *** A COMPLETER pour connecter la socket **** */
	if (connect(sock,(struct sockaddr *) &addr,sizeof(struct sockaddr)) == SOCKET_ERROR)
	{
		perror("connect()");
		exit(errno);
	}else printf("\n --> connexion au serveur [OK]");

	return sock;
}

/*
 creation de la socket serveur
*/
int creationServeur() {

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		perror("socket()");
		exit(errno);
	} else printf("\n --> creation socket serveur [OK]");

	struct sockaddr_in sin;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8082);

	if (bind(sock, (struct sockaddr *) &sin, sizeof sin)) {
		perror("bind()");
		exit(errno);
	} else printf("\n --> configuration socket serveur [OK]");

	if (listen(sock, 10) == SOCKET_ERROR) {
		perror("listen()");
		exit(errno);
	} else printf("\n --> serveur en ecoute [OK]");

	return sock;
}

void * lanceTrain (void * arg)
{
    printf("%s ","\n *** je suis le thread ****");
    sleep(10);
}


/*
 pgm client de lancement  de train
*/
int departTrain(const char * adresse_serveur) {

	char buffer[50];
	char bufferRep[50];
	pthread_t thread1;

	/* connexion au serveur de socket */
	int sock = connexionServeur(adresse_serveur);

	/* boucle de lecture */
	do {
        /* attente message de lancement */
		
		/* *** A COMPLETER **** */
		if(recv(sock, buffer,50,0) < 0)
		{
			perror("recv()");
			exit(errno);
		}else
		{
			printf("%s %s","\n --> reception message [OK] : ",buffer);
		}

        /* traitement du message */
        if (strcmp(buffer,"LANCETRAIN")==0){
            printf("%s","\n --> lancement du train [OK] : ");

            /* creation du thread */
            
			/* *** A COMPLETER **** */
			if(pthread_create(&thread1, NULL, lanceTrain, NULL) == -1) {
				perror("pthread_create");
				return EXIT_FAILURE;
			} else printf("%s", "\n --> thread created");
            /* attente que le thread se termine */
            if(pthread_join(thread1, NULL))
			{
				perror("pthread_join");
				return EXIT_FAILURE;
			}else printf("%s","\n --> attente fin thread");
			/* *** A COMPLETER **** */

            strcpy(bufferRep,"OK");
        } else {
            strcpy(bufferRep,"NOK");
        }

        /* envoi code retour */
		
		/* *** A COMPLETER **** */
		if(send(sock,bufferRep,strlen(bufferRep)+1,0) < 0)
		{
			perror("send()");
			exit(errno);
		}else
		{
			printf("%s %s","\n --> envoie message [OK] : ",bufferRep);
		}


	} while (strcmp(buffer,"STOP")==0);

	return 0;
}


/*
 pgm serveur d'ordonanceur de train
*/
int ordonanceurTrain() {

	char buffer[1024];

	int sock = creationServeur();
	int csock;
	struct sockaddr_in csin = {0};

	int taille = sizeof(csin);
    csock = accept(sock, (struct sockaddr *) &csin, &taille);
    if (csock == INVALID_SOCKET) {
			perror("accept()");
			exit(errno);
    } else printf("\n --> demande de connexion accepté [OK]\n");

	do {


		strcpy(buffer,"LANCETRAIN");
		if (send(csock, buffer, strlen(buffer)+1, 0) < 0) {
			perror("send()");
			exit(errno);
		} else printf("\n --> envoie commande LANCETRAIN [OK]");

		if (recv(csock, buffer, sizeof buffer, 0) < 0) {
			perror("recv()");
			exit(errno);
		} else printf("\n --> en attente de message ...");

		printf("%s %s","\n --> reception code retour : ",buffer);

	} while (1);

	int monde[6] = {0, 0, 0, 0, 0, 0};
	printf("hello!\n");
	return 0;
}
