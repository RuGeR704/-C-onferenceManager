#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "orario.h"
#include "evento.h"
#include "utils.h"
#include "codaEventi.h"
#include "agenda.h"

int main () {
    int selezione;
    int stanze[MAXSTANZE] = {0};
    agenda a = nuovaAgenda();
    coda q = nuovaCoda();
    FILE *fpAgenda;

    //Apertura del file agenda e creazione nel caso in cui non esista
    if(!(fpAgenda = fopen("agenda.txt","r"))){
        printf("FILE \"agenda.txt\" NON TROVATO, CREAZIONE\n");

        if(!(fpAgenda = fopen("agenda.txt", "w"))){
            printf("IMPOSSIBILE CREARE IL FILE, INSERIRLO MANUALMENTE\n");
            exit(1);
        }

        fclose(fpAgenda);

        if(!(fpAgenda = fopen("agenda.txt","r"))){
            printf("ERRORE NELL'APERTURA DEL FILE\n");
            exit(1);
        }
    }

    //Lettura da file degli eventi in agenda e in coda
    leggiFile(fpAgenda, &a, q, stanze);

    //Chiusura dei file
    fclose(fpAgenda);

    do{
        selezione = 0;
        stampaMenu();       //Chiamata della funzione per visualizzare le operazioni disponibili
        scanf("%d", &selezione);    //selezione dell'operazione da effettuare
        while(getchar() != '\n');   //Pulizia buffer di input

        switch (selezione) {
            case 1:
                //Operazione di aggiunta
                printf("----------------------------\n");
                aggiungi(&a, q, stanze);
                printf("----------------------------\n");
                break;
            
            case 2:
                //Operazione di modifica
                if(agendaVuota(a)){
                    printf("L'AGENDA E' VUOTA, NON CI SONO EVENTI DA MODIFICARE\n");
                }

                else{
                    modifica(a);
                }

                printf("----------------------------\n");
                break;

            case 3:
                //Operazione di rimozione
                if(agendaVuota(a)){
                    printf("L'AGENDA E' VUOTA, NON CI SONO EVENTI DA ELIMINARE\n");
                }

                else{
                    printf("----------------------------\n");
                    elimina(&a, q, stanze);
                }
                
                printf("----------------------------\n");
                break;

            case 4:
                //Operazione di stampa dell'agenda
                visualizzaAgenda(a);    //chiamata della funzione visualizzaAgenda
                break;

            case 5:
                //Operazione di stanoa della coda
                stampaCoda(q);
                printf("----------------------------\n");
                break;

            case 6:
                //Chiusura del programma
                printf("CHIUSURA PROGRAMMA E SALVATAGGIO SU FILE\n");
                break;

            default:
                //Caso in cui l'utente non sceglie nessuna delle operazioni disponibili
                printf("SELEZIONE NON VALIDA! RIPROVA INSERENDO UN VALORE VALIDO TRA QUELLI PRESENTI NEL MENU\n");
        }
    }while(selezione != 6);

    //Ordinamento dell'agenda
    a = ordinaAgenda(a);

    //Apertura del file agenda in scrittura
    if(!(fpAgenda = fopen("agenda.txt","w"))){
        printf("ERRORE NELL'APERTURA DEL FILE\n");
        exit(1);
    }

    //Scrittura su file
    scriviFile(fpAgenda, a, q);

    //Chiusura dei file
    fclose(fpAgenda);

    //Eliminazione dell'agenda e della coda
    eliminaAgenda(a);
    eliminaCoda(q);

    return 0;
}