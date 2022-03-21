#ifndef CLIENTCOL3_H_INCLUDED
#define CLIENTCOL3_H_INCLUDED

#include "col3-bibtp/communCOL3-TP.h"


extern hutte HUTTECLAN;


void recupSiteExtraction();
void gestionAppro();
int testServeur( const char * adresseip, int port,const char * tokenduclan,const char * nomduclan);



#endif // CLIENTCOL3_H_INCLUDED
