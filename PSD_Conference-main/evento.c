#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "orario.h"
#include "evento.h"

//Definizione della struttura per rappresentare un evento
struct evento {
    char *titolo;   //Stringa per contenere il titolo dell'evento
    char *tipo;     //Stringa per contenere il tipo dell'evento
    data data;      //ADT data per contenere la data dell'evento
    orario inizio;  //ADT orario per contenere l'inizio dell'evento
    orario fine;    //ADT orario per contenere la fine dell'evento
    int stanza;     //Intero che indica la stanza alla quale viene assegnato l'evento
};

//Funzione per creare un nuovo evento
evento creaEvento(char *titolo, int tipo, data date, orario inizio, orario fine, int stanza) {
    evento e;
    char temp[25];

    if(!(e = malloc(sizeof(struct evento)))) {   //Controllo se l'allocazione dinamica va a buon fine
        printf("ERRORE!\n");
        exit(1);
    }

    if(tipo == 1) {
        strcpy(temp, "Workshop");
    }
    
    else if(tipo == 2) {
        strcpy(temp, "Keynote");
    }
    
    else {
        strcpy(temp, "Panel di discussione");
    }

    //Assegnazione dei valori all'evento
    e -> titolo = strdup(titolo);
    e -> tipo = strdup(temp);
    e -> data = date;
    e -> inizio = inizio;
    e -> fine = fine;
    e -> stanza = stanza;

    return e;
}

//Funzioni per ottenere informazioni sull'evento
char* ottieniTitolo(evento e) {
    return e -> titolo;
}

char* ottieniTipo(evento e) {
    return e -> tipo;
}

data ottieniData(evento e) {
    return e -> data;
}

orario ottieniInizio(evento e) {
    return e -> inizio;
}

orario ottieniFine(evento e) {
    return e -> fine;
}

int ottieniStanza(evento e) {
    return e -> stanza;
}

//Funzioni per modificare le informazioni sull'evento
evento modificaTitolo(evento e, char *nuovoTitolo) {
    free(e -> titolo);
    e -> titolo = strdup(nuovoTitolo);

    return e;
}

evento modificaTipo(evento e, int nuovoTipo) {
    char temp[25];
    free(e -> tipo);

    if(nuovoTipo == 1) {
        strcpy(temp, "Workshop");
    }
    
    else if(nuovoTipo == 2) {
        strcpy(temp, "Keynote");
    }
    
    else {
        strcpy(temp, "Panel di discussione");
    }

    e -> tipo = strdup(temp);

    return e;
}

evento modificaData(evento e, data nuovaData) {
    eliminaData(e -> data);
    e -> data = nuovaData;

    return e;
}

evento modificaOrario(evento e, orario nuovoInizio, orario nuovaFine) {
    eliminaOrario(e -> inizio);
    eliminaOrario(e -> fine);
    e -> inizio = nuovoInizio;
    e -> fine = nuovaFine;

    return e;
}

evento modificaStanza(evento e, int nuovaStanza) {
    e -> stanza = nuovaStanza;

    return e;
}

//Funzione per stampare le informazioni sull'evento
void stampaEvento(evento e) {
    printf("Titolo: %s\n", ottieniTitolo(e));    //Stampa il titolo
    printf("Tipo: %s\n", ottieniTipo(e));        //Stampa il tipo
    printf("Data: ");
    stampaData(ottieniData(e));               //Stampa la data
    printf("Orario inizio: ");
    stampaOrario(ottieniInizio(e));           //Stampa l'orario di inizio
    printf("Orario fine: ");
    stampaOrario(ottieniFine(e));             //Stampa l'orario di fine
    printf("Stanza: ");
    
    if(ottieniStanza(e) == 0) {
        printf("Non assegnata\n");
    }
    
    else {
        printf("%d\n", ottieniStanza(e));
    }
}

//Funzione per eliminare un evento deallocando la memoria
void eliminaEvento(evento e) {
    //Deallocazione di tutti i campi
    free(e -> titolo);
    free(e -> tipo);
    eliminaData(e -> data);
    eliminaOrario(e -> inizio);
    eliminaOrario(e -> fine);

    //Deallocazione dell'evento
    free(e);
}