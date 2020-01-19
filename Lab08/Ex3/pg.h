//
// Created by s259105 on 05/12/2019.
//
// IMPORTANTE.. PER CAPIRE AL MEGLIO IL PROGRAMMA BISOGNA AVERE ANCHE LO SCHEMA DELLE TABELLE

#ifndef PG_H
#define PG_H
#define MAX_EQUIP 8
#include "inv.h"

typedef struct{
    int inUso;
    int nEquip;
    linkInv vettEq[MAX_EQUIP];
}tabEquip_t;
typedef struct {
    char codice[7];
    char *nome;
    char *classe;
    tabEquip_t* equip;
    stat_t stat,statEff;
}pg_t;
typedef struct nodoPg_t *link;
struct nodoPg_t{
    pg_t val;
    link next;
};
typedef struct {
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

//Funzioni CREAZIONE
link creaNodo(pg_t val,link succ);
tabPg_t* creaListaPg();
tabEquip_t * creaListaEquip();
//Funzioni INSERIMENTO
void inserisciCodaPg(tabPg_t *tab,pg_t pg);
tabPg_t* inputPg();
void addPg(tabPg_t *tab);
//Funzioni FREE
void freeNodo(link nodo);
void freeLista(tabPg_t *tab);
//Funzioni STAMPA
void stampaSPg(link nodo);
void stampaPgR(link nodo);
void stampaPg(tabPg_t *tab);
int controllaOgg(link nodo,linkInv ogg);
void stampaInvDisp(tabInv_t *tab,link nodo);
void stampaEquip(link nodo);
void stampaStat(link nodo);
//Funzioni VARIE
link ricercaNodoR(char *key,link nodo);
void eliminaNodo(tabPg_t *tab);
//Funzioni STATISTICA
void aggiornaStat(link nodo);
void statistiche(tabPg_t *tabPg);
//Funzioni EQUIPAGGIAMENTO
void aggiungiEquip(link nodo,tabInv_t *tabInv);
void rimuoviEquip(link nodo);
void equipaggiamento(tabPg_t *tabPg,tabInv_t *tabInv);

#endif //PG_H
