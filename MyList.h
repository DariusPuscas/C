#pragma once
#include "Tranzactie.h"

typedef void* ElemType;
typedef void (*DestroyFunction)(ElemType);
typedef struct{
    ElemType* elemente;
    int lg;
    int capacitate;
}MyList;

/*
  Creeaza o lista goala
*/
MyList* createEmpty();


void destroyListaT(MyList* l);


/*
  Distruge lista
*/
void destroy(MyList* l,DestroyFunction destroyFunction);

/*
  Get an element from the list
  poz - position of the element, need to be valid
  return element on the given position
*/
ElemType get(MyList* l, int poz);

/*
  return numarul de elemente din lista
*/
int size(MyList* l);

/*
  Add element into the list
  post: element is added to the end of the list
*/
void add(MyList* l, ElemType el);

/*
  Make a shallow copy of the list
  return Mylist containing the same elements as l
*/
MyList* copyList(MyList* l);

/*
 * gaseste o tranzactie
 * returneaza indexul, adica pozitia sa in lista
 */
int gaseste_tranzactie(MyList* l, int zi, float suma);

/*
 * sterge tranzactia aflata pe pozitia id in lista
 */
void sterge_tranzactie(MyList* l, int id);

/*
 * modifica ziua tranzactiei de pe pozitia id in lista
 */
void modifica_ziua(MyList*l, int id, int ziua);

/*
 * modifica suma tranzactiei de pe pozitia id in lista
 */
void modifica_suma(MyList*l, int id, float suma);

/*
 * modifica tipul tranzactiei de pe pozitia id in lista
 */
void modifica_tip(MyList*l, int id, char* tip);

/*
 * modifica descrierea tranzactiei de pe pozitia id in lista
 */
void modifica_descriere(MyList*l,int id, char* descriere);


void testCreateList();
void testIterateList();
void testCopyList();
void teststergetranzactie();
void testmodifica();
void testlistadeliste();