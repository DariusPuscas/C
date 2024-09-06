#pragma once

typedef struct{

    int zi;
    float suma;
    char* tip;
    char* descriere;

}Tranzactie;

/*
 * creeaza o tranzactie
 */
Tranzactie* createTranzactie(int zi, float suma, char* tip, char* descriere);

/*
 * sterge o tranzactie
 */
void destroyTranzactie(Tranzactie* t);


void test_create_destroy();

/*
 * valideaza o tranzactie
 */
int  valideaza(Tranzactie);