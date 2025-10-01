#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "evento.h"
#include "codaEventi.h"

//Struttura per un nodo della coda
struct nodo {
    evento valore;       //Evento contenuto nel nodo
    struct nodo *prossimo;  //Puntatore al prossimo nodo
};

//Struttura per la coda di eventi
struct codaEventi {
    struct nodo *testa, *fine;  //Puntatori alla testa e alla coda della lista
    int numel;                 //Numero di elementi nella coda
};

coda nuovaCoda(void) {
    struct codaEventi *q;

    //Allocazione della memoria per la nuova coda
    if (!(q = malloc(sizeof(struct codaEventi)))) {
        printf("Errore\n");
        exit(1);
    }

    //Inizializzazione dei membri della coda
    q -> numel = 0;
    q -> testa = NULL;
    q -> fine = NULL;
    return q;
}

int codaVuota(coda q) {
    if (q == NULL){  //Controlla se il puntatore alla coda è nullo
        return -1;
    }

    return q -> numel == 0;  //Ritorna 1 se la coda è vuota, altrimenti 0
}

evento ottieniEventoTesta(coda q) {
    return q -> testa -> valore;
}

int ottieniNumel(coda q) {
    return q -> numel;
}

coda scorriCoda(coda q) {
    coda nuovaCoda;

    nuovaCoda = q;
    nuovaCoda -> testa = nuovaCoda -> testa -> prossimo;

    return nuovaCoda;
}

int accoda(evento ev, coda q) {
    if (q == NULL){  //Controlla se il puntatore alla coda è nullo
        return 1;
    }

    struct nodo *nuovo;

    //Allocazione della memoria per il nuovo nodo
    if (!(nuovo = malloc(sizeof(struct nodo)))) {
        printf("Errore\n");
        exit(1);
    }

    //Inizializzazione del nuovo nodo
    nuovo -> valore = ev;
    nuovo -> prossimo = NULL;

    //Se la coda è vuota, il nuovo nodo diventa la testa
    if (q -> testa == NULL){
        q -> testa = nuovo;
    }

    else{  //Altrimenti, il nodo successivo della coda corrente punta al nuovo nodo
        q -> fine -> prossimo = nuovo;
    }

    //Il nuovo nodo diventa la coda
    q -> fine = nuovo;
    (q -> numel)++;  //Incrementa il numero di elementi nella coda
    return 0;
}

evento rimuoviDacoda(coda q) {
    //Controlla se la coda è vuota o nulla
    if (codaVuota(q) == -1 || codaVuota(q) == 1){ 
        return NULL;
    }

    evento eventoEstratto = q -> testa -> valore;  //Estrae l'evento alla testa
    struct nodo *temp = q -> testa;  //Nodo temporaneo per la testa
    q -> testa = q -> testa -> prossimo;  //Avanza la testa

    free(temp);  //Dealloca il nodo precedente

    if (q -> testa == NULL){
        q -> fine = NULL;
    }

    (q->numel)--;  //Decrementa il numero di elementi nella coda
    return eventoEstratto;
}

void stampaCoda(coda q) {
    struct nodo *temp;
    int i = 1;

    if(codaVuota(q)) {  //Controlla se la coda è vuota
        printf("LA CODA E' VUOTA\n");
    } 
    
    else {
        temp = q -> testa;

        while(temp != NULL) {  //Scorre tutti i nodi della coda
            printf("----------------------------\n");
            printf("Evento %d:\n", i);
            stampaEvento(temp -> valore);  //Stampa l'evento del nodo corrente
            i++;
            temp = temp -> prossimo;  //Avanza al prossimo nodo
        }
    }
}

void eliminaCoda(coda q) {
    struct nodo *nodoCorrente = q -> testa;

    while (nodoCorrente != NULL) {  //Scorre tutti i nodi della coda
        struct nodo *prec = nodoCorrente;
        nodoCorrente = nodoCorrente -> prossimo;
        eliminaEvento(prec -> valore);  //Dealloca l'evento nel nodo
        free(prec);  //Dealloca il nodo
    }

    free(q);  //Dealloca la coda
}