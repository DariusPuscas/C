#pragma once

#include "MyList.h"
/*
Add a pet to the store
*/

typedef int(*CompareSum)(Tranzactie*,Tranzactie*);

int addTranzactie(MyList* l,MyList *undo,int zi, float suma, char* tip, char* descriere);

/*
  Filter pets in the store 
  typeSubstring - cstring
  return all pets where typeSubstring is a substring of the type
*/
//MyList getAll(MyList* l, char* typeSubstring);

MyList* tranzactii_acelasi_tip(MyList* l , char* tip);

/*
 * tranzactii cu o suma mai mare decat una data
 */
MyList* tranzactii_suma(MyList*l, float suma);

/*
 * interschimba doua tranzactii
 */
void swap(Tranzactie* a, Tranzactie* b);

/*
 * tranzactii ordonate dupa suma
 */
void tranzactii_sort(MyList*l,CompareSum comp);

/*
 * tranzactii ordonate dupa zi
 */

/*
 * compara suma
 */
int compara_suma(Tranzactie* a, Tranzactie* b);
/*
 * compara ziua
 */
int compara_zi(Tranzactie* a, Tranzactie* b);
/*
 * compara suma si ziua
 */
int compara_suma_zi(Tranzactie* a, Tranzactie* b);

void testaddTranzactie();
void testfiltrare1();
void testfiltrare2();
void testfiltrare3();
void testfiltrare4();
void test_tranzactii_sort();
void test_sort();