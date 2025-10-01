#ifndef ORARIO_H_
#define ORARIO_H_

//Definizione del tipo orario
typedef struct orario *orario;

//Verifica se la data è valida
int controllaOrario(int, int);

//Crea un nuovo orario
orario creaOrario(int, int);

//Restituisce l'ora dall'orario
int ottieniOra(orario);

//Restituisce il minuto dall'orario
int ottieniMinuti(orario);

//Confronta due orari
int confrontaOrario(orario, orario);

//Stampa a schermo l'orario
void stampaOrario(orario);

//Dealloca l'orario
void eliminaOrario(orario);
#endif