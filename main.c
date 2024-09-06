#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <crtdbg.h>

#include "Tranzactie.h"
#include "MyList.h"
#include "service.h"

#include <stdio.h>
#include <string.h>

void test_all(){

    test_create_destroy();
    testCreateList();
    testCopyList();
    testIterateList();
    testaddTranzactie();
    teststergetranzactie();
    testmodifica();
    testfiltrare1();
    testfiltrare2();
    testfiltrare3();
    testfiltrare4();
    test_tranzactii_sort();
    testlistadeliste();
    test_sort();

}

void print_tranzactii(MyList* l){

    printf("Tranzactiile sunt:\n");
    for(int i=0; i < size(l); i++){
        Tranzactie* t = get(l,i);
        printf("Ziua:%d Suma:%f Tipul:%s Descriere:%s\n",t->zi,t->suma,t->tip,t->descriere);
    }


}

/*
 * adauga tranzactie introdusa din input si o pune in lista
 */
void add_ui(MyList* l,MyList* undo){

    int zi;
    float suma;
    char tip[10];
    char descriere[50];

    printf("Introduceti ziua:");
    scanf("%d",&zi);

    printf("Introduceti suma:");
    scanf("%f",&suma);

    printf("Introduceti tipul:");
    scanf("%s",tip);

    printf("Introduceti descrierea:");
    scanf("%s",descriere);

    int error = addTranzactie(l,undo,zi,suma,tip,descriere);
    if (error !=0)
        printf("Tranzactie invalida\n");
    else
        printf("Tranzactie inregistrata cu succes\n");


}

void sterge_ui(MyList* l,MyList* undo){
    int zi;
    float suma;

    printf("Introduceti ziua:");
    scanf("%d",&zi);

    printf("Introduceti suma:");
    scanf("%f",&suma);

    int ind = gaseste_tranzactie(l,zi,suma);
    add(undo, copyList(l));
    sterge_tranzactie(l,ind);
    printf("Stergere efectuata cu succes\n");
}

void modifica_ui(MyList* l,MyList* undo){
    int zi;
    float suma;
    add(undo, copyList(l));
    printf("Introduceti ziua:");
    scanf("%d",&zi);

    printf("Introduceti suma:");
    scanf("%f",&suma);

    int ind = gaseste_tranzactie(l,zi,suma);

    char optiune[10];
    printf("Introduceti ce modificati:");
    scanf("%s",optiune);

    if(strcmp(optiune,"Ziua")==0) {
        printf("Introduceti ziua noua:");
        int zi_noua;
        scanf("%d", &zi_noua);
        modifica_ziua(l, ind, zi_noua);
    }
    else
        if(strcmp(optiune,"Suma")==0) {
            printf("Introduceti suma noua:");
            float suma_noua;
            scanf("%f", &suma_noua);
            modifica_suma(l, ind,suma_noua);
        }

        else
            if(strcmp(optiune,"Tipul")==0){
                printf("Introduceti tipul nou:");
                char tip_nou[10];
                scanf("%s",tip_nou);
                modifica_tip(l,ind,tip_nou);

            }

            else
                if(strcmp(optiune,"Descriere")==0) {
                    printf("Introduceti descrierea noua:");
                    char descriere_noua[50];
                    scanf("%s",descriere_noua);
                    modifica_descriere(l,ind,descriere_noua);
                }
                else
                    printf("Optiune invalida\n");

}

void filter1_ui(MyList* l){

    printf("Introduceti tipul:");
    char tip[50];
    scanf("%s",tip);
    MyList* rez = tranzactii_acelasi_tip(l,tip);
    print_tranzactii(rez);
    destroy(rez, (DestroyFunction) destroyTranzactie);
}

void filter2_ui(MyList *l){

    printf("Introduceti suma:");
    float suma;
    scanf("%f",&suma);
    MyList* rez = tranzactii_suma(l,suma);
    print_tranzactii(rez);
    destroy(rez, (DestroyFunction) destroyTranzactie);

}

void sort_ui(MyList* l){

    printf("Introduceti criteriu sortare:");
    char criteriu[10];
    scanf("%s", criteriu);
    printf("Introduceti tip sortare(crescator/descrescator):\n");
    char tipsort[10];
    scanf("%s", tipsort);
    if (strcmp(criteriu,"suma")==0)
        tranzactii_sort(l,compara_suma);
    else
        tranzactii_sort(l,compara_zi);

    if (strcmp(tipsort,"crescator")==0)
        print_tranzactii(l);
    else {
        printf("Tranzactiile sunt:\n");
        for (int i = size(l)-1; i>=0 ; i--) {
            Tranzactie* t = get(l, i);
            printf("Ziua:%d Suma:%f Tipul:%s Descriere:%s\n", t->zi, t->suma, t->tip, t->descriere);
        }
    }

}

void run(){

    MyList* lista_tranzactii = createEmpty();
    MyList* undo =createEmpty();
    int ruleaza = 1;

    while(ruleaza){
        printf("1.Add\n2.Modifica\n3.Stergere\n4.Filtrare\n5.Afiseaza tranzactiile\n6.Sortare\n7.Undo\n0.Exit\n");
        printf("Introduceti optiune:");
        int op=0;
        scanf("%d",&op);

        switch (op) {

            case 1:
                add_ui(lista_tranzactii,undo);
                break;

            case 2:
                modifica_ui(lista_tranzactii,undo);
                break;

            case 3:
                sterge_ui(lista_tranzactii,undo);
                break;

            case 4:
                filter1_ui(lista_tranzactii);
                break;

            case 5:
                print_tranzactii(lista_tranzactii);
                break;

            case 6:
                sort_ui(lista_tranzactii);
                break;

            case 7:
                lista_tranzactii = copyList(undo->elemente[undo->lg-1]);
                undo->lg--;
                break;

            case 0:
                ruleaza = 0;
                break;

            default:
                printf("Comanda invalida!\n");
        }
    }
    destroy(lista_tranzactii, (DestroyFunction) destroyTranzactie);
}

int main() {

    test_all();
    run();
  // _CrtDumpMemoryLeaks();
    return 0;

}
