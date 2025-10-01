#include <stdio.h>
#include <stdlib.h>
#include "orario.h"

//Definizione della struttura per rappresentare un orario
struct orario {
    int ora;    //Variabile che contiene l'ora
    int minuto; //Variabile che contiene i minuti
};

//Funzione per verificare la correttezza dell'orario inserito
int controllaOrario(int ora, int minuto) {
    //Controllo che l'ora sia compresa tra 0 e 24
    if (ora < 0 || ora >= 24) {
        return 0;
    }
    //Controllo che i minuti siano compresi tra 0 e 60
    else if (minuto < 0 || minuto >= 60) {
        return 0;
    } 
    
    else {
        return 1;
    }
}

//Funzione per creare un nuovo orario
orario creaOrario(int ora, int minuto) {
    orario nuovoOrario;   //Dichiarazione del nuovo orario

    //Chiamata della funzione per controllare l'orario
    if((controllaOrario(ora, minuto)) == 0) {
        //In caso di orario non valido restituisco NULL
        nuovoOrario = NULL;
        return nuovoOrario;
    }

    if(!(nuovoOrario = malloc(sizeof(struct orario)))) {
        printf("Errore\n");     //Stampa a schermo dell'errore
        exit(1);                //Esci dal programma
    }

    //Inserimento dei parametri nell'orario
    nuovoOrario -> ora = ora;
    nuovoOrario -> minuto = minuto;

    return nuovoOrario;   //Restituzione del nuovo orario
}

//Funzioni per ottenere informazioni sull'orario
int ottieniOra(orario orario) {
    return orario -> ora;     //Restituisce l'ora
}

int ottieniMinuti(orario orario) {
    return orario -> minuto;  //Restituisce i minuti
} 

//Funzione per confrontare due orari
int confrontaOrario(orario o1, orario o2) {
    if (ottieniOra(o1) > ottieniOra(o2)) {
        return 1;   //La prima è successiva
    } 
    
    else if (ottieniOra(o1) < ottieniOra(o2)) {
        return -1;  //La seconda è successiva
    } 
    
    else {
        if (ottieniMinuti(o1) > ottieniMinuti(o2)) {
            return 1;
        } 
        
        else if (ottieniMinuti(o1) < ottieniMinuti(o2)) {
            return -1;
        } 
        
        else {
            return 0;   //I due orari sono uguali
        }
    }
}

//Funzione per stampare in output l'orario
void stampaOrario(orario ora) {
    printf("%02d:%02d\n", ottieniOra(ora), ottieniMinuti(ora));
}

//Funzione per eliminare l'orario deallocando la memoria
void eliminaOrario(orario ora) {
    free(ora);  //Deallocazione dell'orario
}