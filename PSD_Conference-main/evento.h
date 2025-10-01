#ifndef EVENTO_H_
#define EVENTO_H_

#include "data.h"
#include "orario.h"

//Definizione del tipo evento
typedef struct evento *evento;

//Funzione per creare un evento
evento creaEvento(char *, int, data, orario, orario, int);

//Funzione che restituisce il titolo dell'evento
char* ottieniTitolo(evento);

//Funzione che restituisce il tipo dell'evento
char* ottieniTipo(evento);

//Funzione per restituire la data di un evento
data ottieniData(evento);

//Funzione per restituire l'orario di inizio dell'evento
orario ottieniInizio(evento);

//Funzione per restituire l'orario di fine dell'evento
orario ottieniFine(evento);

//Funzione per restituire la stanza di un evento
int ottieniStanza(evento);

//Funzione per modificare il titolo dell'evento
evento modificaTitolo(evento, char*);

//Funzione per modificare il tipo dell'evento
evento modificaTipo(evento, int);

//Funzione per modificare la data dell'evento
evento modificaData(evento, data);

//Funzione per modificare gli orari di inizio e fine dell'evento
evento modificaOrario(evento, orario, orario);

//Funzione che modifica la stanza dell'evento
evento modificaStanza(evento, int);

//Funzione per stampare un evento
void stampaEvento(evento);

//Funzione per eliminare un evento
void eliminaEvento(evento);
#endif