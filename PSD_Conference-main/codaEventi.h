#ifndef CODA_EVENTI_H_
#define CODA_EVENTI_H_

#include "evento.h"

//Definizione del tipo coda
typedef struct codaEventi *coda;

//Funzione per creare una coda
coda nuovaCoda();

//Funzione che verifica se la coda è vuota
int codaVuota(coda);

//Funzione che restituisce l'evento presente nella testa della coda
evento ottieniEventoTesta(coda);

//Funzione che restituisce il numero di elementi in coda
int ottieniNumel(coda);

//Funzione che scorre la coda
coda scorriCoda(coda);

//Funzione per l'inserimento di un nuovo elemento nella coda
int accoda(evento, coda);

//Funzione che toglie e restituisce l'elemento in testa alla coda
evento rimuoviDacoda(coda);

//Funzione per stampare la coda
void stampaCoda(coda);

//Funzione che elimina la coda
void eliminaCoda(coda);
#endif