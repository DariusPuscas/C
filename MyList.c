#define _CRT_SECURE_NO_WARNINGS
#include "MyList.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>

/*
Create an empty list
*/
MyList* createEmpty() {
    MyList* rez = malloc(sizeof(MyList));
    rez->capacitate = 50;
    rez->elemente = malloc(sizeof(Tranzactie)*rez->capacitate);
    rez->lg = 0;
    return rez;
}

void destroyListaT(MyList* l){
    destroy(l, (DestroyFunction) destroyTranzactie);
}


/*
Destroy list
*/
void destroy(MyList* l, DestroyFunction destroyFunction) {
    for(int i=0; i< l->lg; i++) {
        ElemType t = l->elemente[i];
        destroyFunction(t);
    }
   // l->lg = 0;
    free(l->elemente);
    free(l);
}

/*
returneaza elementul din lista
poz - positia elementului
return elementul de pe positie
*/
ElemType get(MyList* l, int poz) {
    return l->elemente[poz];
}

/*
returneaza numarul de elemente din lista
*/
int size(MyList* l) {
    return l->lg;
}

int capacitate(MyList* l){
    return l->capacitate;
}

/*
Add element in lista
post: elementul este adaugat la finalul listei
*/
void add(MyList* l, ElemType el) {
    if(l->capacitate <= l->lg){
        /// alocam spatiu mai mare
        ElemType* aux = malloc(sizeof(ElemType)*(l->capacitate+5));
        /// copiem lista in spatiul nou alocat
        for(int i=0; i< l->lg; i++)
            aux[i] = l->elemente[i];
        free(l->elemente);
        l->elemente = aux;
        l->capacitate+=5;
    }
    l->elemente[l->lg] = el;
    l->lg++;
}


/*
 * gaseste o tranzactie
 * returneaza indexul, adica pozitia sa in lista
 */
int gaseste_tranzactie(MyList* l, int zi, float suma){

    for(int i=0; i<size(l); i++){
        Tranzactie* t = get(l,i);
        if (t->zi == zi  && t->suma == suma)
            return i;

    }
    return -1;
}

/*
 * sterge tranzactia aflata pe pozitia id in lista
 */
void sterge_tranzactie(MyList* l, int id){

    for(int i=id; i< size(l)-1; i++)
        l->elemente[i] = l->elemente[i+1];

    l->lg--;
}
/*
 * modifica ziua
 */
void modifica_ziua(MyList* l, int id, int ziua){
    Tranzactie* t = get(l,id);
    t->zi=ziua;
    l->elemente[id] = t;
}

/*
 *  modifica suma
 */
void modifica_suma(MyList*l, int id, float suma){
    Tranzactie* t = get(l,id);
    t->suma = suma;
    l->elemente[id] = t;
}

/*
 * modifica tip
 */
void modifica_tip(MyList*l, int id, char* tip){
    Tranzactie* t = get(l,id);
    strcpy(t->tip,tip);
    l->elemente[id] = t;
}

/*
 * modifica descriere
 */
void modifica_descriere(MyList*l, int id, char* descriere){
    Tranzactie* t = get(l,id);
    strcpy(t->descriere,descriere);
    l->elemente[id] = t;
}

/*
Make a shallow copy of the list
return Mylist containing the same elements as l
*/
MyList* copyList(MyList* l) {
    MyList* rez = createEmpty();
    for (int i = 0; i < size(l); i++) {
        Tranzactie * p = get(l, i);
        add(rez, createTranzactie(p->zi,p->suma,p->tip,p->descriere));
    }
    return rez;
}

void testCreateList() {
    MyList* l = createEmpty();
    assert(capacitate(l) == 50);
    assert(size(l) == 0);
    destroy(l, (DestroyFunction) destroyTranzactie);
}
void testIterateList() {
    MyList* l = createEmpty();
    add(l, createTranzactie(12, 5,"Intrare","Paine"));
    add(l, createTranzactie(13,15, "Iesire", "Cafea"));
    assert(size(l) == 2);

    Tranzactie* t = get(l,0);

    assert(strcmp(t->tip,"Intrare") == 0);
    assert(strcmp(t->descriere,"Paine") == 0);
    assert(t->zi == 12);
    assert(t->suma == 5);

    t = get(l, 1);

    assert(strcmp(t->tip,"Iesire") == 0);
    assert(strcmp(t->descriere,"Cafea") == 0);
    assert(t->zi == 13);
    assert(t->suma == 15);

    l->capacitate = 2;
    add(l, createTranzactie(12, 5,"Intrare","Paine"));
    assert(l->capacitate == 7);
     t = get(l,2);

    assert(strcmp(t->tip,"Intrare") == 0);
    assert(strcmp(t->descriere,"Paine") == 0);
    assert(t->zi == 12);
    assert(t->suma == 5);

    destroy(l, (DestroyFunction) destroyTranzactie);

}

void testCopyList() {
    MyList* l = createEmpty();
    add(l, createTranzactie(12, 5,"Intrare","Paine"));
    add(l, createTranzactie(13,15, "Iesire", "Cafea"));
    MyList* l2 = copyList(l);
    assert(size(l2) == 2);
    Tranzactie* t = get(l2,0);
    assert(strcmp(t->tip,"Intrare")==0);
    destroy(l, (DestroyFunction) destroyTranzactie);
    destroy(l2, (DestroyFunction) destroyTranzactie);

}

void teststergetranzactie(){
    MyList* l = createEmpty();
    add(l, createTranzactie(12, 5,"Intrare","Paine"));
    add(l, createTranzactie(13,15, "Iesire", "Cafea"));
    int id = gaseste_tranzactie(l,12,5);
    Tranzactie* x = get(l,id);
    sterge_tranzactie(l,id);
    assert(size(l) == 1);
    Tranzactie* t = get(l,0);
    assert(strcmp(t->tip,"Iesire") == 0);
    assert(strcmp(t->descriere,"Cafea") == 0);
    assert(t->zi == 13);
    assert(t->suma == 15);
   // destroyTranzactie(&l.elemente[size(&l)+1]);
    destroy(l, (DestroyFunction) destroyTranzactie);
    destroyTranzactie(x);
}

void testmodifica(){

    MyList* l = createEmpty();
    add(l, createTranzactie(12, 5,"Intrare","Paine"));
   // add(&l, createTranzactie(13,15.5, "Iesire", "Cafea"));
    modifica_ziua(l,0,20);
  //  modifica_ziua(&l,1,15);
    modifica_suma(l,0,6);
  //  modifica_suma(&l,1,16.7);
    modifica_tip(l,0,"Iesire");
  //  modifica_tip(&l,1,"Intrare");
    modifica_descriere(l,0,"Lapte");
  //  modifica_descriere(&l,1,"Spanac");
    Tranzactie* t1 = get(l,0);
  //  Tranzactie t2 = get(&l, 1);
    assert(t1->zi==20);
 //   assert(t2.zi==15);
    assert(strcmp(t1->tip,"Iesire")==0);
  //  assert(strcmp(t2.tip,"Intrare")==0);
    assert(strcmp(t1->descriere,"Lapte")==0);
 //   assert(strcmp(t2->descriere,"Spanac")==0);
    destroy(l, (DestroyFunction) destroyTranzactie);

}

void testlistadeliste(){
    MyList* Tranzactii = createEmpty();
    add(Tranzactii, createTranzactie(12,5,"Intrare","Paine"));
    add(Tranzactii, createTranzactie(12,5,"Intrare","Cafea"));

    MyList* Tranzactii2 = createEmpty();

    MyList* undo = createEmpty();
    add(undo,Tranzactii);
    assert(size(undo)==1);
    add(undo,Tranzactii2);
    assert(size(undo)==2);

    destroy(undo, (DestroyFunction) destroyListaT);
}
