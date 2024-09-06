#include "service.h"

//#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
 * adauga tranzactie
 */

int addTranzactie(MyList *l,MyList *undo,int zi, float suma, char* tip, char* descriere){

    Tranzactie* t = createTranzactie(zi,suma,tip,descriere);
    int validator = valideaza(*t);
    if(validator!=0) {
        destroyTranzactie(t);
        return validator;
    }
    add(undo, copyList(l));
    add(l,t);
    return 0;


}

MyList* tranzactii_acelasi_tip(MyList* l , char* tip){

    MyList* rez = createEmpty();
    for(int i=0; i < size(l); i++){
        Tranzactie* t = get(l,i);
        if(strcmp(t->tip,tip)==0)
            add(rez, createTranzactie(t->zi,t->suma,t->tip,t->descriere));
    }
    return rez;
}


MyList* tranzactii_suma(MyList* l, float suma_max){

    MyList* rez = createEmpty();
    for(int i=0; i < size(l); i++){
        Tranzactie* t = get(l,i);
        if(t->suma > suma_max)
            add(rez,createTranzactie(t->zi,t->suma,t->tip,t->descriere));
    }

    return rez;

}

void swap(Tranzactie* a, Tranzactie* b) {
    Tranzactie aux = *a;
    *a = *b;
    *b = aux;
}
int compara_suma( Tranzactie* a,  Tranzactie* b) {
     if(a->suma > b->suma) {
        return 1;
    } else {
        return 0;
    }
}
int compara_zi(Tranzactie*a , Tranzactie* b){
    if(a->zi > b->zi) {
        return 1;
    } else {
        return 0;
    }
}

int compara_suma_zi(Tranzactie*a, Tranzactie* b){

    if(a->suma > b->suma)
        return 1;

    else
        if(a->suma == b->suma)
            if(a->zi > b->zi)
                return 1;
    return 0;
}


void tranzactii_sort(MyList* l,CompareSum comp){

    for(int i=0; i < size(l)-1; i++)
        for(int j=i+1; j< size(l); j++)
            if(comp(l->elemente[i],l->elemente[j]) > 0)
                swap(l->elemente[i],l->elemente[j]);

}


void testaddTranzactie(){

    MyList* l = createEmpty();
    MyList* undo = createEmpty();
    // adaugeam tranzactii invalide

    int error = addTranzactie(l,undo,0,4,"Intrare","o ciocolata");
    assert(error != 0);
    assert(size(l) == 0);

    error = addTranzactie(l,undo,12,-3,"Intrare","o ciocolata");
    assert(error != 0);
    assert(size(l) == 0);

    error = addTranzactie(l,undo,12,4,"Respins","o ciocolata");
    assert(error != 0);
    assert(size(l) == 0);

    error = addTranzactie(l,undo,12,4,"Intrare","");
    assert(error != 0);
    assert(size(l) == 0);

    error = addTranzactie(l,undo,12,4,"","cascaval");
    assert(error != 0);
    assert(size(l) == 0);

    // adaugam tranzactii valide

    error = addTranzactie(l,undo,12,5,"Intrare","o ciocolata");
    assert(error == 0);
    assert(size(undo)==1);
    assert(size(l) == 1);

    error = addTranzactie(l,undo,12,5,"Intrare","o ciocolata");
    assert(error == 0);
    assert(size(undo)==2);
    assert(size(l) == 2);

    destroy(l, (DestroyFunction) destroyTranzactie);
    destroy(undo, (DestroyFunction) destroyListaT);


}

void testfiltrare1(){
    MyList* l = createEmpty();
    add(l, createTranzactie(12, 5,"Intrare","Paine"));
    add(l, createTranzactie(13,15, "Iesire", "Cafea"));
    MyList* test = tranzactii_acelasi_tip(l,"Intrare");
    assert(size(test)==1);
    destroy(test, (DestroyFunction) destroyTranzactie);
    test = tranzactii_acelasi_tip(l,"Iesire");
    assert(size(test)==1);
    destroy(test, (DestroyFunction) destroyTranzactie);
    destroy(l, (DestroyFunction) destroyTranzactie);

}

void testfiltrare2(){

    MyList* l = createEmpty();
    add(l, createTranzactie(12, 6,"Intrare","Paine"));
    add(l, createTranzactie(13,15, "Iesire", "Cafea"));
    MyList* test = tranzactii_suma(l,5);
    assert(size(test)==2);
    destroy(test, (DestroyFunction) destroyTranzactie);
    test = tranzactii_suma(l,20);
    assert(size(test)==0);
    destroy(test, (DestroyFunction) destroyTranzactie);
    destroy(l, (DestroyFunction) destroyTranzactie);


}

void testfiltrare3(){

    MyList* l = createEmpty();
    add(l, createTranzactie(13, 15,"Intrare","Paine"));
    add(l, createTranzactie(12,5, "Iesire", "Cafea"));
    tranzactii_sort(l,compara_suma);
    Tranzactie* t = get(l,0);
    assert(strcmp(t->tip,"Iesire") == 0);
    assert(strcmp(t->descriere,"Cafea") == 0);
    assert(t->zi == 12);
    assert(t->suma == 5);
    t = get(l, 1);
    assert(strcmp(t->tip,"Intrare") == 0);
    assert(strcmp(t->descriere,"Paine") == 0);
    assert(t->zi == 13);
    assert(t->suma == 15);
    destroy(l, (DestroyFunction) destroyTranzactie);

}

void testfiltrare4(){

    MyList* l = createEmpty();
    add(l, createTranzactie(13, 15,"Intrare","Paine"));
    add(l, createTranzactie(12,5, "Iesire", "Cafea"));
    tranzactii_sort(l,compara_zi);
    Tranzactie* t = get(l,0);
    assert(strcmp(t->tip,"Iesire") == 0);
    assert(strcmp(t->descriere,"Cafea") == 0);
    assert(t->zi == 12);
    assert(t->suma == 5);
    t = get(l, 1);
    assert(strcmp(t->tip,"Intrare") == 0);
    assert(strcmp(t->descriere,"Paine") == 0);
    assert(t->zi == 13);
    assert(t->suma == 15);
    destroy(l, (DestroyFunction) destroyTranzactie);

}
void test_tranzactii_sort() {
    MyList* l = createEmpty();
    add(l, createTranzactie(12, 5, "Intrare", "Paine"));
    add(l, createTranzactie(13, 15, "Iesire", "Cafea"));
    add(l, createTranzactie(14, 10, "Intrare", "Lapte"));

    // Sortăm lista folosind funcția de comparare pentru sumă
    tranzactii_sort(l, compara_suma);

    // Verificăm că lista este acum sortată
    Tranzactie* t = get(l,0);
    assert(t->suma==5);
    t = get(l,1);
    assert(t->suma==10);
    t=get(l,2);
    assert(t->suma==15);
 //le iau cu get   assert(l->elemente[0]->suma == 5);
   // assert(l->elemente[1]->suma == 10);
  //  assert(l->elemente[2]->suma == 15);

    destroy(l, (DestroyFunction) destroyTranzactie);
}

void test_sort(){

    MyList* l = createEmpty();
    add(l, createTranzactie(10, 5, "Intrare", "Paine"));
    add(l, createTranzactie(13, 7, "Iesire", "Cafea"));
    add(l, createTranzactie(14, 4, "Intrare", "Lapte"));
    add(l, createTranzactie(13, 5, "Iesire", "Cafea"));
    add(l, createTranzactie(14, 4, "Intrare", "Lapte"));
    tranzactii_sort(l,compara_suma_zi);

    Tranzactie* t = get(l,0);
    assert(t->zi==14);
    assert(t->suma==4);

    destroy(l, (DestroyFunction) destroyTranzactie);

}
