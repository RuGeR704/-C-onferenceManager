#ifndef AGENDA_H_
#define AGENDA_H_

#include"evento.h"

//Definizione del tipo agenda
typedef struct nodo *agenda;

//Funzione per creare un agenda
agenda nuovaAgenda(void);

//Funzione che verifica se l'agenda è vuota
int agendaVuota(agenda); 

//Funzione che aggiunge un evento all'agenda
agenda aggiungiEvento(evento, agenda);

//Funzione per rimuovere un nodo dall'agenda
agenda rimuoviNodo(agenda, int);

//Funzione che restituisce la coda dell'agenda
agenda rimuoviTesta(agenda);

//Funzione che restituisce il primo elemento dell'agenda
evento ottieniPrimo(agenda);

//Funzione che stampa l'agenda
void stampaAgenda(agenda);

//Funzione che conta gli eventi dell'agenda
int contaEventi(agenda);

//Funzione che scambia due nodi dell'agenda
void scambiaNodi(struct nodo*, struct nodo*);

//Funzione che ordina l'agenda
agenda ordinaAgenda(agenda);

//Funzione che dealloca l'agenda
void eliminaAgenda(agenda);
#endif