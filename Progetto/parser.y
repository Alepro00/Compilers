%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "symb.h"
    int yylex(); //analizzatore sintattico
    void yyerror(char *);
%}

%union {
    unsigned int intero;
    float reale;
    char *stringa;
}

%token <intero>  ANNO_VAL INTERO
%token <reale>   REALE
%token <stringa> NOMINATIVO CODICEF
%token          ANNO SEP_SEZIONE FASCIA DUEPUNTI VIRGOLA FRECCIA SEP_SEZIONE2 ELETTRICA 
                FOGNATURA CONTATORE METROCUBO IVA PERCENTUALE SEP_SEZIONE3 PUNTO EURO

%start inizio

%%
inizio              : anno_corrente SEP_SEZIONE descrizione_fasce fascia_speciale SEP_SEZIONE2 costi_aggiuntivi SEP_SEZIONE3 lista_persone
                    ;

anno_corrente       : ANNO ANNO_VAL
                    ;

descrizione_fasce   : descrizione_fasce fasce
                    | fasce
                    ;
fasce               : FASCIA INTERO DUEPUNTI REALE FRECCIA REALE FRECCIA EURO REALE METROCUBO      {aggiungiFasciaInCoda($2, $4, $6, $9);}
                    ;

fascia_speciale     : /*Epsilon*/
                    | FASCIA INTERO DUEPUNTI REALE FRECCIA FRECCIA EURO REALE METROCUBO            {aggiungiFasciaInCodaS($2, $4, $8);}
                    ;                                

costi_aggiuntivi    :   ELETTRICA EURO REALE METROCUBO FOGNATURA EURO REALE METROCUBO CONTATORE EURO REALE PUNTO IVA INTERO PERCENTUALE  {aggiungiCosti($3,$7,$11,$14);}
                    ;

lista_persone       : lista_persone NOMINATIVO VIRGOLA CODICEF VIRGOLA INTERO VIRGOLA INTERO    {aggiungiPersona($2,$4,$6,$8);}
                    | NOMINATIVO VIRGOLA CODICEF VIRGOLA INTERO VIRGOLA INTERO    {aggiungiPersona($1,$3,$5,$7);}
                    ;
%%

int main(){
    //Se il parsing del file in input è completato con successo restituisce 0
    if (yyparse() == 0) {
        //system("cls");
        system("color 0a");
        stampaPersonePrezzi();
        liberaMemoria();
    }
    return 0;
}

void yyerror(char *s){
    //system("cls");
    system("color 0c");
	fprintf(stderr,"%s\n",s);
}
