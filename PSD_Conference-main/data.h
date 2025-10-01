#ifndef DATA_H_
#define DATA_H_

//Definizione del tipo data
typedef struct data *data;

//Funzione che controlla se è possibile creare una data coi valori inseriti
int controlloData(int, int, int);

//Funzione che controlla se un anno è bisestile, restituisce 1 se è bisestile, 0 altrimenti
int bisestile(int);

//Funzione per creare una nuova data
data creaData(int, int, int);

//Funzione che restituisce il giorno della data
int ottieniGiorno(data);

//Funzione che restituisce il mese della data
int ottieniMese(data);

//Funzione che restituisce l'anno della data
int ottieniAnno(data);

//Funzione che confronta due date, restituisce 1 se la prima è maggiore, -1 se la prima è minore, 0 altrimenti
int confrontaDate(data, data);

//Funzione per stampare a schermo una data
void stampaData(data);

//Funzione per deallocare lo spazio occupato da una data
void eliminaData(data);
#endif