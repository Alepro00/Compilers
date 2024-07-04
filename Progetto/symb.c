#include "symb.h"

Persona *hashtab[HASHSIZE];
Fascia* fascia = NULL;
Costi costiAggiuntivi;

/*Funzioni per la gestione della fascia
******************************************/
void aggiungiFasciaInCoda(unsigned int numFascia, float limiteInferiore, float limiteSuperiore, float costoFascia) {
    Fascia* nuovo_nodo = (Fascia*) malloc(sizeof(Fascia));
    if (nuovo_nodo == NULL) {
        printf("Errore allocazione memoria\n");
        exit(1);
    }

    nuovo_nodo->numFascia = numFascia;
    nuovo_nodo->limiteInferiore = limiteInferiore;
    nuovo_nodo->limiteSuperiore = limiteSuperiore==0.00 ? DBL_MAX : limiteSuperiore;
    nuovo_nodo->costofascia = costoFascia; 
    nuovo_nodo->next = NULL;

    if (fascia == NULL) {
        fascia = nuovo_nodo;
    } else {
        Fascia* corrente = fascia;
        while (corrente->next != NULL) {
            corrente = corrente->next;
        }
        corrente->next = nuovo_nodo;
    }
}

void aggiungiFasciaInCodaS(unsigned int numFascia, float limiteInferiore, float costoFascia) {
    aggiungiFasciaInCoda(numFascia,limiteInferiore,0.00,costoFascia);
}

Fascia* trovaFascia(unsigned int conto){
    if (fascia == NULL) {
        printf("Errore!\n");
        return NULL;
    }
    Fascia* corrente = fascia;

    while(conto>corrente->limiteSuperiore)
        corrente=corrente->next;
    return corrente;  
}
/*********************************************************************/

//Funzione per la gestione dei costi aggiuntivi
void aggiungiCosti(float elettricita, float fognatura, float contatore, unsigned int iva){
    costiAggiuntivi.elettricita=elettricita;
    costiAggiuntivi.fognatura=fognatura;
    costiAggiuntivi.contatore=contatore;
    costiAggiuntivi.iva=iva;
}


//Corpo della funzione hash
unsigned int hash(char *s){
    int h=0;
    for(;*s!='\0';s++)
        h=(127*h+*s)%HASHSIZE;
    return h;
    
}

/*Funzioni per la gestione dell'hashtable delle persone
********************************************************/
Persona *lookup(char *codiceFiscale){
    Persona *nuovaPersona;
    for(nuovaPersona = hashtab[hash(codiceFiscale)]; nuovaPersona!= NULL; nuovaPersona=nuovaPersona->next)
        if(strcmp(codiceFiscale,nuovaPersona->codiceFiscale)==0)
            return nuovaPersona;
    return NULL;
}

void aggiungiPersona(char *nominativo, char *codiceFiscale,unsigned int letturaInizio, unsigned int letturaFine){
    Persona *nuovaPersona;
    unsigned hashval=hash(codiceFiscale);
    if((nuovaPersona=lookup(codiceFiscale))==NULL){
        if((nuovaPersona = (Persona*)malloc(sizeof(*nuovaPersona))) == NULL)
            return;
        nuovaPersona->nominativo=strdup(nominativo);
        nuovaPersona->letturaInizio=letturaInizio;
        nuovaPersona->letturaFine=letturaFine;
        nuovaPersona->next=hashtab[hashval];
        hashtab[hashval]=nuovaPersona;
    }
}
/********************************************************** */

//Libera la memoria per HashTable e per la Fascia
void liberaMemoria() {    
    for (int i = 0; i < HASHSIZE; i++)
        free(hashtab[i]);

    while (fascia != NULL) {
        Fascia* temp = fascia;
        fascia = fascia->next;
        free(temp);
    }
}

//Funzione per la stampa delle persone ed i prezzi
void stampaPersonePrezzi(){
    int key;
    Persona *nuovaPersona;
    float contatore;
    for(key=0;key<HASHSIZE;key++){
        for(nuovaPersona=hashtab[key]; nuovaPersona!=NULL; nuovaPersona=nuovaPersona->next){
            contatore=(nuovaPersona->letturaFine)-(nuovaPersona->letturaInizio);
            printf("%s ->\t%10.2f\n",nuovaPersona->nominativo, calcoloCosto(contatore));
        }
    }
}

float calcoloCosto(float contatore){
    Fascia* attinente=trovaFascia(contatore);
    float costo=contatore*(attinente->costofascia+costiAggiuntivi.elettricita+costiAggiuntivi.fognatura)+costiAggiuntivi.contatore;
    return costo+(costo*costiAggiuntivi.iva)/100;
}