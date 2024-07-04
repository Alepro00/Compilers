#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define HASHSIZE 137

//Lista concatenata
typedef struct f {
    int numFascia;
    float limiteInferiore;
    float limiteSuperiore;
    float costofascia;
    struct f *next;
} Fascia;


//Struttura normale
typedef struct c {
    float elettricita;
    float fognatura;
    float contatore;
    int iva;
} Costi;

typedef struct p{
    char* nominativo;
    char* codiceFiscale;
    int letturaInizio;
    int letturaFine;
    struct p *next;
}Persona;

// Prototipi delle funzioni



void aggiungiFasciaInCoda(unsigned int numFascia, float limiteInferiore, float limiteSuperiore, float costofascia);
void aggiungiFasciaInCodaS(unsigned int numFascia, float limiteInferiore, float costofascia); 
Fascia* trovaFascia(unsigned int conto);

void aggiungiCosti(float elettricita, float fognatura, float contatore, unsigned int iva);

unsigned int hash(char *s);
Persona *lookup(char *codiceFiscale);
void aggiungiPersona(char *nominativo, char *codiceFiscale, unsigned int letturaInizio, unsigned int letturaFine);

void liberaMemoria();

float calcoloCosto(float contatore);

void stampaPersonePrezzi();
