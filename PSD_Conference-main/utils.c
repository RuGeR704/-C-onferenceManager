#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "data.h"
#include "orario.h"
#include "evento.h"
#include "agenda.h"
#include "codaEventi.h"

//Stampa del meu delle operazioni disponibili
void stampaMenu(){
    printf("MENU:\n");
    printf("\t [1] AGGIUNGI EVENTO \n");
    printf("\t [2] MODIFICA EVENTO \n");
    printf("\t [3] ELIMINA EVENTO \n");
    printf("\t [4] VISUALIZZA AGENDA \n");
    printf("\t [5] VISUALIZZA CODA\n");
    printf("\t [6] ESCI\n");
}

//Stampa dei tipi di conferenza disponibile
void stampaTipo(){
    printf("TIPI DISPONIBILI:\n");
    printf("\t [1] WORKSHOP \n");
    printf("\t [2] KEYNOTE \n");
    printf("\t [3] PANEL DI DISCUSSIONE \n");
}

//Verifica che il tipo sia valido
int verificaTipo (int tipo) {
    if (tipo < 1 || tipo > 3) {
        return 0;
    }
}

//Conversione del tipo da stringa a intero
int convertiTipo(char *tmpTipo){
    int tipo;

    if(strcmp(tmpTipo, "Workshop") == 0){
        tipo = 1;
    }

    else if(strcmp(tmpTipo, "Keynote") == 0){
        tipo = 2;
    }

    else if(strcmp(tmpTipo, "Panel di discussione") == 0){
        tipo = 3;
    }

    else{
        tipo = 0;
    }

    return tipo;
}

//Lettura da file degli eventi
void leggiFile(FILE *fpAgenda, agenda *a, coda q, int *stanze){
    char tmpTitolo[50];
    char tmpTipo[50];
    int tmpTipo2;
    int tmpGiorno, tmpMese, tmpAnno;
    data tmpData;
    int tmpOra, tmpMinuti;
    orario tmpInizio;
    orario tmpFine;
    int tmpStanza;
    int numEventi = 0;

    //Controllo che il file non sia vuoto
    fgetc(fpAgenda);

    //Ciclo fino alla fine del file
    while((!feof(fpAgenda)) && numEventi < MAXSTANZE){

        while(fgetc(fpAgenda) != '\n'){
            //Ignoro la prima riga
        }

        //Estrazione di tutti i dati dal file
        fgets(tmpTitolo, 50, fpAgenda);
        tmpTitolo[strcspn(tmpTitolo, "\n")] = '\0';
        fgets(tmpTipo, 50, fpAgenda);
        tmpTipo[strcspn(tmpTipo, "\n")] = '\0';
        tmpTipo2 = convertiTipo(tmpTipo);
        fscanf(fpAgenda, "%02d/%02d/%04d\n", &tmpGiorno, &tmpMese, &tmpAnno);
        tmpData = creaData(tmpGiorno, tmpMese, tmpAnno);
        fscanf(fpAgenda, "%02d:%02d\n", &tmpOra, &tmpMinuti);
        tmpInizio = creaOrario(tmpOra, tmpMinuti);
        fscanf(fpAgenda, "%02d:%02d\n", &tmpOra, &tmpMinuti);
        tmpFine = creaOrario(tmpOra, tmpMinuti);
        fscanf(fpAgenda, "Stanza %d\n", &tmpStanza);
        stanze[tmpStanza - 1] = 1;

        fgetc(fpAgenda);
        
        //Salvataggio dei dati in una variabile
        evento tmp = creaEvento(tmpTitolo, tmpTipo2, tmpData, tmpInizio, tmpFine, tmpStanza);

        //Aggiunta dell'evento nella lista
        *a = aggiungiEvento(tmp, *a);

        numEventi = contaEventi(*a);
    }

    if(!feof(fpAgenda)){
        fgetc(fpAgenda);
        while(fgetc(fpAgenda) != '\n'){
            //Ignoro la prima riga
        }
    }
    
    //Ciclo fino alla fine del file
    while(!feof(fpAgenda)){
        while(fgetc(fpAgenda) != '\n'){
            //Ignoro la prima riga
        }

        //Estrazione di tutti i dati dal file
        fgets(tmpTitolo, 50, fpAgenda);
        tmpTitolo[strcspn(tmpTitolo, "\n")] = '\0';
        fgets(tmpTipo, 50, fpAgenda);
        tmpTipo[strcspn(tmpTipo, "\n")] = '\0';
        tmpTipo2 = convertiTipo(tmpTipo);
        fscanf(fpAgenda, "%02d/%02d/%d\n", &tmpGiorno, &tmpMese, &tmpAnno);
        tmpData = creaData(tmpGiorno, tmpMese, tmpAnno);
        fscanf(fpAgenda, "%02d:%02d\n", &tmpOra, &tmpMinuti);
        tmpInizio = creaOrario(tmpOra, tmpMinuti);
        fscanf(fpAgenda, "%02d:%02d\n", &tmpOra, &tmpMinuti);
        tmpFine = creaOrario(tmpOra, tmpMinuti);
        fscanf(fpAgenda, "Stanza: Non assegnata\n");
        tmpStanza = 0;

        fgetc(fpAgenda);

        //Salvataggio dei dati in una variabile
        evento tmp = creaEvento(tmpTitolo, tmpTipo2, tmpData, tmpInizio, tmpFine, tmpStanza);

        //Inserimento dell'evento in coda
        accoda(tmp, q);
    }
}

void scriviFile(FILE *fpAgenda, agenda a, coda q){
    agenda tmpAgenda = a;
    coda tmpCoda = q;

    for(int i = 0; i < contaEventi(a); i++){
        //Salvataggio di tutti i dati della lista nel file
        fprintf(fpAgenda, "Evento %d:\n", i + 1);
        fprintf(fpAgenda, "%s\n", ottieniTitolo(ottieniPrimo(tmpAgenda)));
        fprintf(fpAgenda, "%s\n", ottieniTipo(ottieniPrimo(tmpAgenda)));
        fprintf(fpAgenda, "%02d/%02d/%04d\n", ottieniGiorno(ottieniData(ottieniPrimo(tmpAgenda))), ottieniMese(ottieniData(ottieniPrimo(tmpAgenda))), ottieniAnno(ottieniData(ottieniPrimo(tmpAgenda))));
        fprintf(fpAgenda, "%02d:%02d\n", ottieniOra(ottieniInizio(ottieniPrimo(tmpAgenda))), ottieniMinuti(ottieniInizio(ottieniPrimo(tmpAgenda))));
        fprintf(fpAgenda, "%02d:%02d\n", ottieniOra(ottieniFine(ottieniPrimo(tmpAgenda))), ottieniMinuti(ottieniFine(ottieniPrimo(tmpAgenda))));
        fprintf(fpAgenda, "Stanza %d\n", ottieniStanza(ottieniPrimo(tmpAgenda)));
        fprintf(fpAgenda, "\n");
        tmpAgenda = rimuoviTesta(tmpAgenda);
    }

    if(!codaVuota(q)){
        fprintf(fpAgenda,"Coda:\n");

        for(int i = 0; i < ottieniNumel(tmpCoda); i++){
            //Salvataggio di tutti i dati della coda nel file
            fprintf(fpAgenda, "Evento %d:\n", i + 1);
            fprintf(fpAgenda, "%s\n", ottieniTitolo(ottieniEventoTesta(tmpCoda)));
            fprintf(fpAgenda, "%s\n", ottieniTipo(ottieniEventoTesta(tmpCoda)));
            fprintf(fpAgenda, "%02d/%02d/%04d\n", ottieniGiorno(ottieniData(ottieniEventoTesta(tmpCoda))), ottieniMese(ottieniData(ottieniEventoTesta(tmpCoda))), ottieniAnno(ottieniData(ottieniEventoTesta(tmpCoda))));
            fprintf(fpAgenda, "%02d:%02d\n", ottieniOra(ottieniInizio(ottieniEventoTesta(tmpCoda))), ottieniMinuti(ottieniInizio(ottieniEventoTesta(tmpCoda))));
            fprintf(fpAgenda, "%02d:%02d\n", ottieniOra(ottieniFine(ottieniEventoTesta(tmpCoda))), ottieniMinuti(ottieniFine(ottieniEventoTesta(tmpCoda))));
            fprintf(fpAgenda, "Stanza: Non assegnata\n");
            fprintf(fpAgenda, "\n");
            tmpCoda = scorriCoda(tmpCoda);
        }
    }
}

void visualizzaAgenda (agenda a){
    //Ordinamento e stampa dell'agenda
    a = ordinaAgenda(a);
    stampaAgenda(a); 
    printf("----------------------------\n");
}

void aggiungi (agenda *a, coda q, int *stanze) {
    char titolo[52];
    int tipo = 0;
    int giorno = 0;
    int mese = 0;
    int anno = 0;
    data data;
    int ora = 0;
    int minuti = 0;
    orario inizio;
    orario fine;
    evento nuovoEvento;
    int numStanza = 0;
    int stanzelibere = 0;

    
    //Inserimento titolo dell'evento
    printf ("TITOLO EVENTO (MASSIMO 50 CARATTERI):\t");
    fgets(titolo, 52, stdin);

    while(strlen(titolo) == 51 && titolo[50] != '\n' || strlen(titolo) == 1){
        if(strlen(titolo) == 51 && titolo[50] != '\n'){
            while(getchar() != '\n');
        }
        printf("IL TITOLO INSERITO SUPERA LA LUNGHEZZA MASSIMA O E' VUOTO (50 caratteri), RIPROVARE:\t");
        fgets(titolo, 52, stdin);
    }

    titolo[strcspn(titolo, "\n")] = '\0';

    //Selezione del tipo di evento (Workshop, Keynote, Panel di discussione)
    stampaTipo();
    printf("INSERIRE IL TIPO DI EVENTO TRA QUELLI PROPOSTI:\t");
    scanf("%d" ,&tipo);     //inserimento del valore che rappresenta il tipo di evento
    while(getchar() != '\n');   //Pulizia buffer di input

    //verifico il valore restituito dalla funzione verificaTipo
    while (!(verificaTipo(tipo))) {
        printf("SELEZIONE NON VALIDA!\n");
        stampaTipo();
        printf("INSERIRE IL TIPO DI EVENTO TRA QUELLI PROPOSTI:\t");
        scanf("%d" ,&tipo);                 //inserimento del valore che rappresenta il tipo di evento
        while(getchar() != '\n');   //Pulizia buffer di input
    }

    //Inserimento della data dell'evento
    printf("INSERIRE LA DATA DELL'EVENTO DAL 2024 IN POI (gg/mm/aaaa):\t");
    scanf("%d/%d/%d", &giorno, &mese, &anno);
    while(getchar() != '\n');   //Pulizia buffer di input
    data = creaData(giorno,mese,anno);

    while(!data){
        printf("DATA INSERITA NON VALIDA, RIPROVARE:\t");
        scanf("%d/%d/%d" ,&giorno, &mese, &anno);
        while(getchar() != '\n');   //Pulizia buffer di input
        data = creaData(giorno,mese,anno);
    }

    //Inserimento dell'orario di inizio dell'evento
    printf("INSERIRE ORARIO DI INIZIO DELL'EVENTO:\n");
    printf("ORA:\t");
    while(!(scanf("%d", &ora)) || ora < 0 || ora > 23){
        while(getchar() != '\n');
        printf("ORA NON VALIDA, RIPROVARE:\t");
    }

    printf("MINUTI:\t");

    while(!(scanf("%d", &minuti)) || minuti < 0 || minuti > 59){
        while(getchar() != '\n');
        printf("MINUTI NON VALIDI, RIPROVARE:\t");
    }

    while((ora == 23 && minuti == 59)){
        printf("L'EVENTO NON PUO' INIZIARE ALLE 23:59, RIPROVARE:\n");

        printf("ORA:\t");
        while(!(scanf("%d", &ora)) || ora < 0 || ora > 23){
            while(getchar() != '\n');
            printf("ORA NON VALIDA, RIPROVARE:\t");
        }

        printf("MINUTI:\t");

        while(!(scanf("%d", &minuti)) || minuti < 0 || minuti > 59){
            while(getchar() != '\n');
            printf("MINUTI NON VALIDI, RIPROVARE:\t");
        }

        while(getchar() != '\n');
        inizio = creaOrario(ora, minuti);
    }

    inizio = creaOrario(ora, minuti);

    printf("\n");
    printf("ORARIO DI INIZIO: ");
    stampaOrario(inizio);
    printf("\n");

    //Inserimento dell'orario di fine dell'evento
    printf("INSERIRE ORARIO DI FINE DELL'EVENTO:\n");
    printf("ORA:\t");
    while(!(scanf("%d", &ora)) || ora < 0 || ora > 23){
        while(getchar() != '\n');
        printf("ORA NON VALIDA, RIPROVARE:\t");
    }

    printf("MINUTI:\t");

    while(!(scanf("%d", &minuti)) || minuti < 0 || minuti > 59){
        while(getchar() != '\n');
        printf("MINUTI NON VALIDI, RIPROVARE:\t");
    }

    fine = creaOrario(ora, minuti);

    while(confrontaOrario(fine, inizio) < 1){
        printf("L'ORARIO DI FINE DELL'EVENTO NON PUO' PRECEDERE O ESSERE UGUALE A QUELLO DI INIZIO, RIPROVARE:\n");
                
        printf("ORA:\t");
        while(!(scanf("%d", &ora)) || ora < 0 || ora > 23){
            while(getchar() != '\n');
            printf("ORA NON VALIDA, RIPROVARE:\t");
        }

        printf("\nMINUTI:\t");

        while(!(scanf("%d", &minuti)) || minuti < 0 || minuti > 59){
            while(getchar() != '\n');
            printf("MINUTI NON VALIDI, RIPROVARE:\t");
        }
        while(getchar() != '\n');
        fine = creaOrario(ora, minuti);
    }

    printf("\n");
    printf("ORARIO DI FINE: ");
    stampaOrario(fine);
    printf("\n");

    //Controllo delle stanze libere    
    for(int i = 0; i < MAXSTANZE; i++){
        if(stanze[i] == 0){
           stanzelibere++;
        }
    }

    //Inserimento dell'evento in coda se non ci sono stanze libere
    if(stanzelibere == 0){
        printf("NON CI SONO STANZE LIBERE\n");
        numStanza = 0;
        
        //Creazione evento
        nuovoEvento = creaEvento(titolo, tipo, data, inizio, fine, numStanza);
    
        //Aggiunta dell'evento alla coda
        accoda(nuovoEvento, q);
    }

    //Selezione della stanza in cui effettuare l'evento
    else{
        printf("INSERIRE STANZA PER L'EVENTO:\n");
        printf("STANZE LIBERE:\n");
        for(int i = 0; i < MAXSTANZE; i++){
            if(stanze[i] == 0){
                printf("[%d]\t", i + 1);
            }
        }

        do{
            printf("\n");
            scanf("%d", &numStanza);
            while(getchar() != '\n');   //Pulizia buffer di input

            if(numStanza < 1 || numStanza > MAXSTANZE){
                printf("NUMERO STANZA NON VALIDO, RIPROVARE:\t");
            }

            else if(stanze[numStanza - 1] == 1){
                printf("STANZA OCCUPATA, SCEGLIERE TRA QUELLE LIBERE:\t");
            }
        }while(numStanza < 1 || numStanza > MAXSTANZE || stanze[numStanza - 1] == 1);

        stanze[numStanza - 1] = 1;

        //Creazione evento
        nuovoEvento = creaEvento(titolo, tipo, data, inizio, fine, numStanza);

        //Aggiunta dell'evento all'agenda
        *a = aggiungiEvento(nuovoEvento, *a);
    }
}

void modifica (agenda a){
    agenda tmpAgenda = a;
    evento e;
    char titolo[52];
    int tipo = 0;
    int giorno = 0;
    int mese = 0;
    int anno = 0;
    data data;
    int ora = 0;
    int minuti = 0;
    orario inizio;
    orario fine;
    int eventi = contaEventi(a);
    int selezione = 0;
    int indice = 0;

    //Stampa dell'agenda
    printf("EVENTI IN AGENDA:\n");
    visualizzaAgenda(a);

    //Selezione dell'evento da modificare
    printf("INSERIRE L'INDICE DELL'EVENTO CHE VUOI MODIFICARE\t");
    scanf("%d", &indice);
    while(getchar() != '\n');   //Pulizia buffer di input

    while(indice > eventi || indice < 1){
        printf("INDICE INSERITO NON VALIDO RIPROVARE:\t");
        scanf("%d", &indice);
        while(getchar() != '\n');   //Pulizia buffer di input
    }

    //Scorrimento dell'agenda fino all'evento selezionato
    for(int i = 0; i < indice - 1; i++){
        tmpAgenda = rimuoviTesta(tmpAgenda);
    }

    e = ottieniPrimo(tmpAgenda);

    do { 
        //Selezione del campo da modificare
        printf("COSA VUOI MODIFICARE?\n");
        printf("\t [1] TITOLO \n");
        printf("\t [2] TIPO \n");
        printf("\t [3] DATA \n");
        printf("\t [4] ORARIO \n");
        printf("\t [0] ESCI\n");
        scanf("%d" ,&selezione);
        while(getchar() != '\n');   //Pulizia buffer di input

        switch(selezione) {
            case 1:
                //Modifica del titolo
                printf("INSERIRE IL NUOVO TITOLO (MASSIMO 50 CARATTERI):\t");
                fgets(titolo, 52, stdin);

                while(strlen(titolo) == 51 && titolo[50] != '\n' || strlen(titolo) == 1){
                    if(strlen(titolo) == 51 && titolo[50] != '\n'){
                        while(getchar() != '\n');
                    }
                    printf("IL TITOLO INSERITO SUPERA LA LUNGHEZZA MASSIMA O E' VUOTO (50 caratteri), RIPROVARE:\t");
                    fgets(titolo, 52, stdin);
                }

                titolo[strcspn(titolo, "\n")] = '\0';
                modificaTitolo(e, titolo);
                break;

            case 2:
                //Modifica del tipo
                stampaTipo();
                printf("INSERIRE IL TIPO DI EVENTO TRA QUELLI PROPOSTI:\t");
                scanf("%d" ,&tipo);     //inserimento del valore che rappresenta il tipo di evento
                while(getchar() != '\n');   //Pulizia buffer di input

                while (!(verificaTipo(tipo))) {          //verifico il valore restituito dalla funzione verificaTipo (utils.h)
                    printf("SELEZIONE NON VALIDA!\n");
                    stampaTipo();
                    printf("INSERIRE IL TIPO DI EVENTO TRA QUELLI PROPOSTI:\t");
                    scanf("%d" ,&tipo);                //inserimento del valore che rappresenta il tipo di evento
                    while(getchar() != '\n');   //Pulizia buffer di input
                }

                modificaTipo(e, tipo);
                break;

            case 3:
                //Modifica della data
                printf("INSERIRE LA DATA DELL'EVENTO DAL 2024 IN POI (gg/mm/aaaa):\t");
                scanf("%d/%d/%d" ,&giorno, &mese, &anno);
                while(getchar() != '\n');   //Pulizia buffer di input
                data = creaData(giorno,mese,anno);

                while(!data){
                    printf("DATA INSERITA NON VALIDA, RIPROVARE:\t");
                    scanf("%d/%d/%d" ,&giorno, &mese, &anno);
                    while(getchar() != '\n');   //Pulizia buffer di input
                    data = creaData(giorno,mese,anno);
                }

                modificaData(e, data);
                break;
            
            case 4:
                //Modifica degli orari di inizio e di fine
                printf("INSERIRE ORARIO DI INIZIO DELL'EVENTO:\n");
                printf("ORA:\t");
                while(!(scanf("%d", &ora)) || ora < 0 || ora > 23){
                    while(getchar() != '\n');
                    printf("ORA NON VALIDA, RIPROVARE:\t");
                }

                printf("MINUTI:\t");

                while(!(scanf("%d", &minuti)) || minuti < 0 || minuti > 59){
                    while(getchar() != '\n');
                    printf("MINUTI NON VALIDI, RIPROVARE:\t");
                }

                while((ora == 23 && minuti == 59)){
                    printf("L'EVENTO NON PUO' INIZIARE ALLE 23:59, RIPROVARE:\n");

                    printf("ORA:\t");
                    while(!(scanf("%d", &ora)) || ora < 0 || ora > 23){
                        while(getchar() != '\n');
                        printf("ORA NON VALIDA, RIPROVARE:\t");
                    }

                    printf("MINUTI:\t");

                    while(!(scanf("%d", &minuti)) || minuti < 0 || minuti > 59){
                        while(getchar() != '\n');
                        printf("MINUTI NON VALIDI, RIPROVARE:\t");
                    }

                    while(getchar() != '\n');
                    inizio = creaOrario(ora, minuti);
                }

                inizio = creaOrario(ora, minuti);

                printf("\n");
                printf("ORARIO DI INIZIO: ");
                stampaOrario(inizio);
                printf("\n");

                //Inserimento dell'orario di fine dell'evento
                printf("INSERIRE ORARIO DI FINE DELL'EVENTO:\n");
                printf("ORA:\t");
                while(!(scanf("%d", &ora)) || ora < 0 || ora > 23){
                    while(getchar() != '\n');
                    printf("ORA NON VALIDA, RIPROVARE:\t");
                }

                printf("MINUTI:\t");

                while(!(scanf("%d", &minuti)) || minuti < 0 || minuti > 59){
                    while(getchar() != '\n');
                    printf("MINUTI NON VALIDI, RIPROVARE:\t");
                }

                fine = creaOrario(ora, minuti);

                while(confrontaOrario(fine, inizio) < 1){
                    printf("L'ORARIO DI FINE DELL'EVENTO NON PUO' PRECEDERE O ESSERE UGUALE A QUELLO DI INIZIO, RIPROVARE:\n");
                            
                    printf("ORA:\t");
                    while(!(scanf("%d", &ora)) || ora < 0 || ora > 23){
                        while(getchar() != '\n');
                        printf("ORA NON VALIDA, RIPROVARE:\t");
                    }

                    printf("MINUTI:\t");

                    while(!(scanf("%d", &minuti)) || minuti < 0 || minuti > 59){
                        while(getchar() != '\n');
                        printf("MINUTI NON VALIDI, RIPROVARE:\t");
                    }
                    while(getchar() != '\n');
                    fine = creaOrario(ora, minuti);
                }

                printf("\n");
                printf("ORARIO DI FINE: ");
                stampaOrario(fine);
                printf("\n");
                
                modificaOrario(e, inizio, fine);
                break;

            case 0:
                //Uscita dalla funzione
                break;

            default:
                //Caso in cui la selezione non è valida
                printf("SELEZIONE NON VALIDA! RIPROVA INSERENDO UN VALORE VALIDO TRA QUELLI PRESENTI NEL MENU\n");
                break;
        }
    } while (selezione != 0);
}

void elimina (agenda *a, coda q, int *stanze) {
    int indice;
    int eventi = contaEventi(*a);
    int stanzaLiberata;
    agenda tmpAgenda = *a;
    evento temp;

    //Stampa degli eventi in agenda
    printf("EVENTI IN AGENDA:\n");
    visualizzaAgenda(*a);

    //Selezione dell'evento da eliminare
    printf("INSERIRE L'INDICE DELL'EVENTO CHE VUOI ELIMINARE\t");
    scanf("%d", &indice);
    while(getchar() != '\n');   //Pulizia buffer di input

    while(indice > eventi || indice < 1){
        printf("INDICE INSERITO NON VALIDO RIPROVARE:\t");
        scanf("%d", &indice);
        while(getchar() != '\n');   //Pulizia buffer di input
    }

    //Scorrimento dell'agenda mer arrivare all'evento selezionato
    for(int i = 0; i < indice - 1; i++){
        tmpAgenda = rimuoviTesta(tmpAgenda);
    }

    //Rimozione dell'evento
    stanzaLiberata = ottieniStanza(ottieniPrimo(tmpAgenda));
    *a = rimuoviNodo(*a, indice);

    //Cambiamento dello stato della stanza
    stanze[stanzaLiberata - 1] = 0;

    //Inserimento del primo evento in coda nell'agenda
    if(!codaVuota(q)){
        printf("IL PRIMO ELEMENTO IN CODA VERRA' INSERITO NELL'AGENDA\n");
        temp = rimuoviDacoda(q);
        temp = modificaStanza(temp, stanzaLiberata);
        *a = aggiungiEvento(temp, *a);
        stanze[stanzaLiberata - 1] = 1;
    }

    //Caso in cui la coda è vuota
    else{
        printf("NON CI SONO ELEMENTI IN CODA, LA STANZA E' STATA LIBERATA\n");
    }
}