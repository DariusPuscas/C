#define _CRT_SECURE_NO_WARNINGS
#include "Tranzactie.h"

#include <string.h>
#include <assert.h>
#include <stdlib.h>

/*
 * creeaza o tranzactie
 */
Tranzactie* createTranzactie(int zi, float suma, char* tip, char* descriere){

    Tranzactie* rez = malloc(sizeof(Tranzactie));
    rez->zi = zi;
    rez->suma = suma;

    unsigned int nr = strlen(tip)+1;
    rez->tip = malloc(nr*sizeof(char));
    strcpy(rez->tip,tip);
    nr = strlen(descriere)+1;
    rez->descriere = malloc(nr*sizeof(char));
    strcpy(rez->descriere, descriere);

    return rez;
}

/*
 * sterge o tranzactie
 */
void destroyTranzactie(Tranzactie* t){

    free(t->descriere);
    free(t->tip);
    free(t);

   // t->descriere[0] = '\0';
    //t->tip[0] = '\0';
}

void test_create_destroy(){

    Tranzactie* t = createTranzactie(12,4,"Intrare","o ciocolata");

    assert(strcmp(t->tip, "Intrare") == 0);
    assert(strcmp(t->descriere, "o ciocolata") == 0);
    assert(t->suma == 4);
    assert(t->zi == 12);

    destroyTranzactie(t);
   // assert(strlen(t.tip) == 0);
   // assert(strlen(t.descriere) == 0);
}

int  valideaza(Tranzactie t){

    if (strlen(t.descriere) == 0)
        return 1;

    if (strlen(t.tip) == 0)
        return 2;

    if(t.suma < 0)
        return 3;

    if(t.zi < 1  || t.zi >31)
        return 4;

    if(strcmp(t.tip,"Intrare")!=0 && strcmp(t.tip,"Iesire")!=0)
        return 5;

    return 0;

}