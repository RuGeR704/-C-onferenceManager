#include <stdio.h>
#include <stdlib.h>
#include "data.h"

//Definizione della struttura data per rappresentare una data
struct data {
    int giorno; //Variabile che contiene il giorno
    int mese;   //Variabile che contiene il mese
    int anno;   //Variabile che contiene l'anno
};

//Funzione per determinare se un anno è bisestile
int bisestile(int a) {
    if ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) {
        return 1; //Restituisce 1 se l'anno è bisestile
    } 
    
    else {
        return 0; //Restituisce 0 se l'anno non è bisestile
    }
}

//Funzione per controllare se una data è valida
int controlloData(int g, int m, int a) {
    if(a < 2024 || m < 1 || m > 12 || g < 1 || g > 31){
        return 0; //Restituisce 0 se la data non è valida
    }

    if(bisestile(a) && m == 2 && g > 29){
        return 0; //Restituisce 0 se è un anno bisestile e il giorno è maggiore di 29 in febbraio
    }

    else if(!bisestile(a) && m == 2 && g > 28){
        return 0;   //Restituisce 0 se si porva a mettere 29 febbraio in un anno non bisestile
    }

    if(m == 4 || m == 6 || m == 9 || m == 11){
        if(g > 30){
            return 0; //Restituisce 0 se il mese ha solo 30 giorni e il giorno è maggiore di 30
        }
    }

    return 1; //Restituisce 1 se la data è valida
}

//Funzione per creare una nuova data
data creaData(int g, int m, int a) {
    data d;

    if(!(controlloData(g, m, a))) {
        d = NULL; //Restituisce NULL se la data non è valida
        return d;
    }

    if(!(d = malloc (sizeof(struct data)))) {
        printf("Errore\n");
        exit(1); //Termina il programma se non è possibile allocare memoria per la data
    }

    d -> giorno = g;
    d -> mese = m;
    d -> anno = a;

    return d;
}

//Funzioni per ottenere il giorno, il mese e l'anno da una data
int ottieniGiorno(data d) {
    return d -> giorno;
}

int ottieniMese(data d) {
    return d -> mese;
}

int ottieniAnno(data d) {
    return d -> anno;
}

//Funzione per confrontare due date
int confrontaDate(data d1, data d2) {
    int diffAnno = ottieniAnno(d1) - ottieniAnno(d2);

    if (diffAnno > 0) {
        return 1; //Restituisce 1 se la prima data è successiva alla seconda
    }
    
    else if (diffAnno < 0) {
        return -1; //Restituisce -1 se la prima data è precedente alla seconda
    }

    int diffMese = ottieniMese(d1) - ottieniMese(d2);
    if (diffMese > 0) {
        return 1;
    }
    
    else if (diffMese < 0) {
        return -1;
    }

    int diffGiorno = ottieniGiorno(d1) - ottieniGiorno(d2);
    if(diffGiorno > 0) {
        return 1;
    }
    
    else if(diffGiorno < 0) {
        return -1;
    }

    return 0; //Restituisce 0 se le date sono uguali
}

//Funzione per stampare una data
void stampaData(data d) {
    printf("%02d/%02d/%04d\n", ottieniGiorno(d), ottieniMese(d), ottieniAnno(d));
}

//Funzione per eliminare una data deallocando la memoria
void eliminaData(data d) {
    free(d);
}