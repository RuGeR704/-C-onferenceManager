#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "orario.h"
#include "evento.h"
#include "utils.h"
#include "codaEventi.h"
#include "agenda.h"

int aggiungiFile(FILE *, agenda *, coda, int *);
int modificaFile(FILE *, agenda);
int rimuoviFile(FILE *, agenda, coda, int *);
int risultatoAtteso(FILE *, FILE *);

int main(int argc, char *argv[]){
    FILE *fp_testsuite, *fp_inputAgenda, *fp_outputAgenda, *fp_operazione, *fp_oracle, *fp_risultato;
    char tempRighe[50];
    char inputAgenda[50];
    char inputOperazione[50];
    char output[50], oracle[50];
    agenda a;
    coda q;
    int stanze[MAXSTANZE] = {0};
    int scelta;
    int cont = 1;
    int op = 0;
    int righe = 0;

    //Verifica del numero di argomenti passati al programma
    if(argc != 2){
        printf("INSERIRE NOME DEL FILE CONTENENTE LA TEST SUITE\n");
        return 0;
    }

    //Apertura del file di test suite
    if(!(fp_testsuite = fopen(argv[1], "r"))){
        printf("ERRORE NELL'APEURTURA DEL FILE\n");
        return 0;
    }

    //Apertura del file di risultato
    if(!(fp_risultato = fopen("risultato.txt", "w"))){
        printf("ERRORE NELL'APEURTURA DEL FILE\n");
        return 0;
    }

    while(fgets(tempRighe, 50, fp_testsuite) != NULL){
        righe++;
    }

    righe /= 2;

    rewind(fp_testsuite);


    //Ciclo principale per l'esecuzione dei casi di test
    for(int i = 0; i < righe; i++){
        a = nuovaAgenda();      //Creazione di una nuova agenda
        q = nuovaCoda();        //Creazione di una nuova coda

        //Lettura del nome del file di input per l'agenda
        fgets(inputAgenda, 50, fp_testsuite);
        inputAgenda[strcspn(inputAgenda, "\n")] = '\0';

        //Lettura del nome del file di operazione
        fgets(inputOperazione, 50, fp_testsuite);
        inputOperazione[strcspn(inputOperazione, "\n")] = '\0';

        //Creazione dei nomi dei file di output e oracle
        sprintf(output, "tc_%dOutput.txt", cont);
        sprintf(oracle, "tc_%dOracle.txt", cont);

        //Apertura del file di input per l'agenda
        if(!(fp_inputAgenda = fopen(inputAgenda, "r"))){
            printf("ERRORE NELL'APERTURA DEL FILE INPUT\n");
            return 0;
        }

        //Apertura del file di operazione
        if(!(fp_operazione = fopen(inputOperazione, "r"))){
            printf("ERRORE NELL'APERTURA DEL FILE OPERAZIONE\n");
            return 0;
        }

        //Apertura del file di output per l'agenda
        if(!(fp_outputAgenda = fopen(output, "w+"))){
            printf("ERRORE NELL'APERTURA DEL FILE OUTPUT DI AGENDA");
            return 0;
        }

        //Apertura del file oracle per l'agenda
        if(!(fp_oracle = fopen(oracle, "r"))){
            printf("ERRORE NELL'APERTURA DEL FILE ORACLE DI AGENDA");
            return 0;
        }

        //Lettura dei dati dal file di input per l'agenda
        leggiFile(fp_inputAgenda, &a, q, stanze);

        //Lettura della scelta dell'operazione dal file di operazione
        fscanf(fp_operazione, "%d\n", &scelta);

        //Esecuzione dell'operazione scelta
        switch(scelta){
            case 1:
                op = aggiungiFile(fp_operazione, &a, q, stanze);
                break;
            case 2:
                op = modificaFile(fp_operazione, a);
                break;
            case 3:
                op = rimuoviFile(fp_operazione, a, q, stanze);
                break;
            default:
                op = 0;
        }
        
        //Verifica se è stata effettuata un'operazione
        if(op == 0){
            fprintf(fp_outputAgenda, "NESSUNA OPERAZIONE EFFETTUATA");
        }

        else{
            a = ordinaAgenda(a);          //Ordinamento dell'agenda
            scriviFile(fp_outputAgenda, a, q); //Scrittura dell'agenda nel file di output
        }

        rewind(fp_outputAgenda);           //Riavvolgimento del file di output per la lettura

        //Confronto tra il risultato ottenuto e l'output atteso
        if(risultatoAtteso(fp_outputAgenda, fp_oracle)){
            fprintf(fp_risultato, "SUCCESSO\n");
        }

        else{
            fprintf(fp_risultato, "FALLIMENTO\n");
        }

        cont++;    //Incremento del contatore dei casi di test

        //Reimpostazione delle stanze
        for(int i = 0; i < MAXSTANZE; i++){
            stanze[i] = 0;
        }

        //Chiusura dei file aperti
        fclose(fp_inputAgenda);
        fclose(fp_operazione);
        fclose(fp_oracle);
        fclose(fp_outputAgenda);
        eliminaAgenda(a);  //Deallocazione dell'agenda
        eliminaCoda(q);    //Deallocazione della coda
    }

    //Chiusura del file di test suite
    fclose(fp_testsuite);
    return 0;
}

//Funzione per aggiungere un evento da un file
int aggiungiFile(FILE *fp_operazione, agenda *a, coda q, int *stanze){
    char tmpTitolo[52];
    char tmpTipo[50];
    int tmpTipo1;
    int tmpGiorno, tmpMese, tmpAnno;
    data tmpData;
    int tmpOra, tmpMinuto;
    orario tmpInizio;
    orario tmpFine;
    evento tmpEvento;
    int stanzeLibere = 0;
    int tmpStanza = 0;
    int indiceStanza = 0;

    //Controllo delle stanze libere    
    for(int i = 0; i < MAXSTANZE; i++){
        if(stanze[i] == 0){
           stanzeLibere++;
        }
    }

    //Lettura dei dettagli dell'evento dal file di operazione
    fgets(tmpTitolo, 52, fp_operazione);

    if(strlen(tmpTitolo) == 51 && tmpTitolo[50] != '\n'){
        return 0;
    }

    tmpTitolo[strcspn(tmpTitolo, "\n")] = '\0';

    fgets(tmpTipo, 50, fp_operazione);
    tmpTipo[strcspn(tmpTipo, "\n")] = '\0';
    tmpTipo1 = convertiTipo(tmpTipo);

    if(!tmpTipo){
        return 0;
    }

    fscanf(fp_operazione, "%d/%d/%d\n", &tmpGiorno, &tmpMese, &tmpAnno);
    tmpData = creaData(tmpGiorno, tmpMese, tmpAnno);

    if(!tmpData){
        return 0;
    }

    fscanf(fp_operazione, "%d:%d\n", &tmpOra, &tmpMinuto);
    tmpInizio = creaOrario(tmpOra, tmpMinuto);
    fscanf(fp_operazione, "%02d:%02d\n", &tmpOra, &tmpMinuto);
    tmpFine = creaOrario(tmpOra, tmpMinuto);

    if(!tmpInizio || !tmpFine || confrontaOrario(tmpFine, tmpInizio) < 1){
        return 0;
    }

    //Inserimento dell'evento in coda se non ci sono stanze libere
    if(stanzeLibere == 0){
        tmpEvento = creaEvento(tmpTitolo, tmpTipo1, tmpData, tmpInizio, tmpFine, tmpStanza);

        //Aggiunta dell'evento alla coda
        accoda(tmpEvento, q);
    }

    else{
        while(tmpStanza == 0){
            if(stanze[indiceStanza] == 0){
                tmpStanza = indiceStanza + 1;
            }
            indiceStanza++;
        }

        tmpEvento = creaEvento(tmpTitolo, tmpTipo1, tmpData, tmpInizio, tmpFine, tmpStanza);
        stanze[indiceStanza] = 1;
        *a = aggiungiEvento(tmpEvento, *a);
    }

    return 1;
}

//Funzione per modificare un evento da un file
int modificaFile(FILE *fp_operazione, agenda a){
    int indice;
    int campo;
    char tmpTitolo[52];
    char tmpTipo[50];
    int tmpTipo1;
    int tmpGiorno, tmpMese, tmpAnno;
    data tmpData;
    int tmpOra, tmpMinuto;
    orario tmpInizio;
    orario tmpFine;
    evento tmpEvento;
    int stanzeLibere = 0;
    int tmpStanza = 0;
    int indiceStanza = 0;
    agenda tmpAgenda = a;

    fscanf(fp_operazione, "%d %d\n", &indice, &campo);

    //Scorrimento dell'agenda fino all'evento selezionato
    for(int i = 0; i < indice - 1; i++){
        tmpAgenda = rimuoviTesta(tmpAgenda);
    }

    tmpEvento = ottieniPrimo(tmpAgenda);

    if(feof(fp_operazione)){
        return 0;
    }

    //Modifica del campo specificato
    switch(campo){
        case 1:
            fgets(tmpTitolo, 52, fp_operazione);

            if(strlen(tmpTitolo) == 51 && tmpTitolo[50] != '\n'){
                return 0;
            }

            tmpTitolo[strcspn(tmpTitolo, "\n")] = '\0';
            modificaTitolo(tmpEvento, tmpTitolo);
            break;
        case 2:
            fgets(tmpTipo, 50, fp_operazione);
            tmpTipo[strcspn(tmpTipo, "\n")] = '\0';
            tmpTipo1 = convertiTipo(tmpTipo);

            if(tmpTipo1 < 1 || tmpTipo1 > 3){
                return 0;
            }
            else{
                modificaTipo(tmpEvento, tmpTipo1);
            }
            break;
        case 3:
            fscanf(fp_operazione, "%d/%d/%d\n", &tmpGiorno, &tmpMese, &tmpAnno);
            tmpData = creaData(tmpGiorno, tmpMese, tmpAnno);

            if(!tmpData){
                return 0;
            }
            else{
                modificaData(tmpEvento, tmpData);
            }
            break;
        case 4:
            fscanf(fp_operazione, "%d:%d\n", &tmpOra, &tmpMinuto);
            tmpInizio = creaOrario(tmpOra, tmpMinuto);
            fscanf(fp_operazione, "%02d:%02d\n", &tmpOra, &tmpMinuto);
            tmpFine = creaOrario(tmpOra, tmpMinuto);

            if(!tmpInizio || !tmpFine || confrontaOrario(tmpFine, tmpInizio) < 1){
                return 0;
            }
            else{
                modificaOrario(tmpEvento, tmpInizio, tmpFine);
            }
            break;
        default:
            return 0;
    }

    return 1;
}

//Funzione per rimuovere un evento da un file
int rimuoviFile(FILE *fp_operazione, agenda a, coda q, int *stanze){
    int indice;
    int eventi = contaEventi(a);
    int stanzaLiberata;
    data tmpData;
    orario tmpInizio, tmpFine;
    agenda tmpAgenda = a;
    evento temp;

    fscanf(fp_operazione, "%d", &indice);

    if(indice > eventi || indice < 1){
        return 0;
    }

    for(int i = 0; i < indice - 1; i++){
        tmpAgenda = rimuoviTesta(tmpAgenda);
    }

    stanzaLiberata = ottieniStanza(ottieniPrimo(tmpAgenda));
    a = rimuoviNodo(a, indice);

    stanze[stanzaLiberata - 1] = 0;

    if(!codaVuota(q)){
        temp = rimuoviDacoda(q);
        temp = modificaStanza(temp, stanzaLiberata);

        if(ottieniTitolo(temp) == NULL){
            return 0;
        }

        if(strcmp(ottieniTipo(temp), "Workshop") != 0 && strcmp(ottieniTipo(temp), "Keynote") != 0 && strcmp(ottieniTipo(temp), "Panel di discussione") != 0){
            return 0;
        }

        if(!(tmpData = creaData(ottieniGiorno(ottieniData(temp)), ottieniMese(ottieniData(temp)), ottieniAnno(ottieniData(temp))))){
            return 0;
        }

        if(!(tmpInizio = creaOrario(ottieniOra(ottieniInizio(temp)), ottieniMinuti(ottieniInizio(temp))))){
            return 0;
        }

        if(!(tmpFine = creaOrario(ottieniOra(ottieniFine(temp)), ottieniMinuti(ottieniFine(temp))))){
            return 0;
        }

        if(confrontaOrario(tmpFine, tmpInizio) < 1){
            return 0;
        }

        a = aggiungiEvento(temp, a);
        stanze[stanzaLiberata - 1] = 1;
    }
    return 1;
}

//Funzione per confrontare il risultato atteso con l'output ottenuto
int risultatoAtteso(FILE *fp_output, FILE *fp_oracle){
    char ch1, ch2;

    while ((ch1 = fgetc(fp_output)) != EOF && (ch2 = fgetc(fp_oracle)) != EOF) {
        if (ch1 != ch2) {
           return 0;
        }
    }

    return 1;
}
