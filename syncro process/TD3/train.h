#ifndef CLIENT_INCLUDED
#define CLIENT_INCLUDED

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1


int connexionServeur(const char *adresse_serveur);
int creationServeur() ;
int departTrain(const char * adresse_serveur);
int ordonanceurTrain();

#endif // CLIENT_INCLUDED
