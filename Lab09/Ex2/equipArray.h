#ifndef EQUIPARRAY_H_DEFINED
#define EQUIPARRAY_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define EQUIP_SLOT 8

#include "invArray.h"

/* ADT di prima classe collezione di oggetti di equipaggiamento */
typedef struct equipArray_s *equipArray_t; 

/* creatore e disruttore */
equipArray_t equipArray_init();
void equipArray_free(equipArray_t equipArray);

/* quanti equipaggiamenti sono in uso */
int equipArray_inUse(equipArray_t equipArray);

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray);
/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray,stat_t *eq_stat);
/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index);

/* Si possono aggiungere altre funzioni se ritenute necessarie */
/*Un controllo sull'equip per vedere se è vuoto/pieno/niente*/
int equipArray_check(equipArray_t equipArray);
/*controllo se l'oggetto dell'inv da aggiungere è gia presente nell'equip*/
int equipArray_checkIndex(equipArray_t equipArray,int index);
int equipArray_menu();
void equipArray_remove(equipArray_t equipArray,invArray_t invArray,stat_t *eq_stat);
void equipArray_insert(equipArray_t equipArray,invArray_t invArray,stat_t *eq_stat);
void equipArray_invArrayPrintDisp(FILE *fp,equipArray_t equipArray,invArray_t invArray);

#endif
