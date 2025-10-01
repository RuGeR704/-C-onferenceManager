#ifndef UTILS_H_
#define UTILS_H_

#include "agenda.h"
#include "codaEventi.h"

//Variabile globale per indicare il numero massimo di stanze
#define MAXSTANZE 10

//Stampa a schermo il menu per la scelta dell'operazione da eseguire
void stampaMenu();

//Stampa a schermo le possibili scelte di tipo dell'evento
void stampaTipo();

//Verifica se la selezione del tipo è valida
int verificaTipo(int);

//Restituisce un intero che indica il tipo dell'evento
int convertiTipo(char *);

//Legge da file tutti i dati contenuti nell'agenda
void leggiFile(FILE *, agenda *, coda, int *);

//Scrive in un file i dati contenuti nell'agenda
void scriviFile(FILE *, agenda, coda);

//Funzione per stampare l'agenda
void visualizzaAgenda(agenda);

//Funzione per aggiungere un evento in agenda o in coda
void aggiungi(agenda *, coda, int *);

//Funzione per modificare un evento in agenda
void modifica(agenda );

//Funzione per rimuovere un file dall'agenda
void elimina(agenda *, coda , int *);
#endif