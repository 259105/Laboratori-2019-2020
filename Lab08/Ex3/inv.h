//
// Created by s259105 on 05/12/2019.
//
// IMPORTANTE.. PER CAPIRE AL MEGLIO IL PROGRAMMA BISOGNA AVERE ANCHE LO SCHEMA DELLE TABELLE

#ifndef INV_H
#define INV_H

typedef struct {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;
typedef struct inv_s inv_t,*linkInv;
struct inv_s {
    char *nome;
    char *tipo;
    stat_t stat;
};
typedef struct{
    inv_t* vettInv;
    int nInv;
    int maxInv;
}tabInv_t;

tabInv_t* creaListaInv(int O);
tabInv_t* inputInv();
linkInv ricercaInv(char* key,tabInv_t *tabInv);
void stampaInv(tabInv_t *tab);
void stampaInvDett(char* key,tabInv_t *tabInv);
void inventario(tabInv_t *tabInv);
void freeElementoV(inv_t elemento);
void freeInventario(tabInv_t *tab);

#endif //INV_H
