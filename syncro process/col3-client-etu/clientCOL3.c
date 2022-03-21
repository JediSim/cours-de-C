#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include "col3-bibtp/communCOL3-TP.h"
#include "clientCOL3.h"



/* ===================================
     fonction d'extraction des sites 
       (a completer)
  ==================================*/
		   
void recupSiteExtraction()
{

 printf("\n  *** au boulot ... ****\n");
	
}


/* ===================================
     fonction de recupération de MP 
       (a completer)
  ==================================*/
		   
void gestionAppro()
{

 printf("\n  *** au boulot ... ****\n");
	
}


/*  ======================================
	  fonction de test d'échange initiale 
      avec le serveur
    =====================================*/ 

int testServeur( const char * adresseip, int port,const char * tokenduclan,const char * nomduclan) {
	
	int socket;

	


	logClientCOL3(info,"test", 
					  "le clan[%s] crée une socket pour tester le serveur",
					  nomduclan);
	
	/* -----------------------------
	   ECHANGE 1 : envoi du token de test 
	   ----------------------------- */

	/* creation et connexion au serveur de socket */
	socket = connexionServeurCOL3(adresseip,port,tokenduclan,nomduclan); // on met MSG_TEST à la place du TOKEN


	/* -----------------------------
	   ECHANGE 2 : valildation echange  
	   ----------------------------- */
	if (socket != INVALID_SOCKET) {

		logClientCOL3(info,"test", 
					  "le clan[%s] a validé son test de connexion  %b ",
					  nomduclan,debug_ok); 
		close(socket);
			
	} 
	else {
				logClientCOL3(error,"test", 
					  "le clan[%s] n'a pas validé son test de connexion  %b ",
					  nomduclan,debug_nok); 
	}
	


	return socket;
}

