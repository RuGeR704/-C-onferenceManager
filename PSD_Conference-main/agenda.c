#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "orario.h"
#include "evento.h"
#include "agenda.h"

struct nodo{ 
    evento valore;
    struct nodo *prossimo;
};

//Inizializza una nuova agenda
agenda nuovaAgenda(void){
    return NULL;
}

//Verifica se l'agenda è vuota
int agendaVuota(agenda a){
    return a == NULL;
}

//Aggiungi un nuovo evento all'agenda
agenda aggiungiEvento(evento val, agenda a){
    struct nodo *nuovo;

    //Allocazione della memoria per il nuovo nodo
    if(!(nuovo = malloc(sizeof(struct nodo)))){
        printf("Errore\n");
        exit(1);
    }

    nuovo -> valore = val;
    nuovo -> prossimo = NULL;
    
    if(a == NULL){
        //Se l'agenda è vuota, il nuovo nodo diventa il primo nodo
        a = nuovo;
    } 
    
    else{
        //Trova l'ultimo nodo della lista
        struct nodo *ultimo = a;

        while(ultimo -> prossimo != NULL){
            ultimo = ultimo -> prossimo;
        }

        //Aggiungi il nuovo nodo alla fine della lista
        ultimo -> prossimo = nuovo;
    }

    return a;
}

//Rimuovi un nodo dall'agenda
agenda rimuoviNodo(agenda a, int indice){
    struct nodo *temp = a;
    struct nodo *prec = NULL;

    if(agendaVuota(a)){
        printf("AGENDA VUOTA, NESSUN NODO DA ELIMINARE\n");
        return a;
    }

    //Trova il nodo precedente a quello da rimuovere
    for(int i = 0; i < indice - 1; i++){
        prec = temp;
        temp = temp -> prossimo;
    }

    if(prec == NULL){
        //Rimuove il primo nodo
        eliminaEvento(temp -> valore);
        a = rimuoviTesta(a);
        free(temp);
    }
    
    else{
        //Rimuove un nodo intermedio o finale
        eliminaEvento(temp -> valore);
        prec -> prossimo = temp -> prossimo;
        free(temp);
    }

    return a;
}

//Restituisce l'agenda senza il primo nodo
agenda rimuoviTesta(agenda a){
    agenda temp;

    if(!agendaVuota(a)){    
        temp = a -> prossimo;
    } 
    
    else{
        temp = NULL;    
    }

    return temp;
}

//Ottiene il primo evento dell'agenda
evento ottieniPrimo(agenda a){
    evento e;   

    if(!agendaVuota(a)){    
        e = a -> valore;
    } 
    
    else{
        e = NULL;
    }

    return e;
}

//Stampa tutti gli eventi dell'agenda
void stampaAgenda(agenda a){
    struct nodo *temp;
    int i = 1;

    if(agendaVuota(a)){
        printf("L'AGENDA E' VUOTA\n");
    } 
    
    else{
        temp = a;

        while(temp != NULL){
            printf("----------------------------\n");
            printf("Evento %d:\n", i);
            stampaEvento(temp -> valore);
            temp = temp -> prossimo;
            i++;
        }
    }
}

//Conta il numero di eventi nell'agenda
int contaEventi(agenda a){
    int contatore = 0;

    struct nodo *temp = a;
    
    while(temp != NULL){
        contatore++;
        temp = temp -> prossimo;
    }

    return contatore;
}

//Scambia i valori di due nodi
void scambiaNodi(struct nodo *n1, struct nodo *n2){
    evento temp = n1 -> valore;
    n1 -> valore = n2 -> valore;
    n2 -> valore = temp;
}

//Ordina l'agenda per data
agenda ordinaAgenda(agenda a){
    if (agendaVuota(a) || a->prossimo == NULL){
        return a;
    }

    int scambiati;
    struct nodo *ptr1;
    struct nodo *ptr2 = NULL;

    //Bubble sort
    do {
        scambiati = 0;
        ptr1 = a;

        while (ptr1 -> prossimo != ptr2) {
            //Confronta le date dei nodi vicini
            if (confrontaDate(ottieniData(ptr1 -> valore), ottieniData(ptr1 -> prossimo -> valore)) > 0) {
                //Scambia i nodi se non sono in ordine
                scambiaNodi(ptr1, ptr1->prossimo);
                scambiati = 1;
            }
            ptr1 = ptr1->prossimo;
        }
        ptr2 = ptr1;
    } while (scambiati);

    return a;
}

//Elimina tutti gli eventi e dealloca l'agenda
void eliminaAgenda(agenda a){
    while(a != NULL){
        struct nodo *temp = a;
        eliminaEvento(temp -> valore);
        a = a -> prossimo;
        free(temp);
    }

    free(a);
}