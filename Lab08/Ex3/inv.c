//
// Created by s259105 on 05/12/2019.
//
// IMPORTANTE.. PER CAPIRE AL MEGLIO IL PROGRAMMA BISOGNA AVERE ANCHE LO SCHEMA DELLE TABELLE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inv.h"
#include "mylib.h"

tabInv_t* creaListaInv(int O){
    tabInv_t *temp;
    temp=(tabInv_t*)malloc(sizeof(tabInv_t));
    if(temp==NULL){
        fprintf(stderr,"Errore di allocazione.");
        exit(2);
    }
    temp->vettInv=(inv_t*)malloc(O*sizeof(inv_t));
    if(temp->vettInv==NULL){
        fprintf(stderr,"Errore di allocazione.");
        exit(2);
    }
    temp->nInv=O;
    temp->maxInv=0;
    return temp;
}
tabInv_t* inputInv(){
    tabInv_t *tab;
    int O;
    FILE *fp=fopen("inventario.txt","r");
    char nome[MAX_CHAR],tipo[MAX_CHAR];

    if(fp==NULL){
        fprintf(stderr,"Errore file non trovato.");
        exit(1);
    }
    fscanf(fp,"%d",&O);
    tab=creaListaInv(O);
    for(int i=0;i<O;i++){
        fscanf(fp,"%s%s%d%d%d%d%d%d",nome,tipo,&tab->vettInv[i].stat.hp,&tab->vettInv[i].stat.mp,&tab->vettInv[i].stat.atk,&tab->vettInv[i].stat.def,&tab->vettInv[i].stat.mag,&tab->vettInv[i].stat.spr);
        tab->vettInv[i].nome=strdup(nome);
        tab->vettInv[i].tipo=strdup(tipo);
        if(tab->vettInv[i].nome==NULL ||tab->vettInv[i].tipo==NULL){
            fprintf(stderr,"Errore di allocazione.");
            exit(2);
        }
    }
    return tab;
}
linkInv ricercaInv(char* key,tabInv_t *tabInv){
    int i;
    for(i=0;i<tabInv->nInv && confronta_stringhe(key,tabInv->vettInv[i].nome)!=0;i++);
    if(i==tabInv->nInv) return NULL;  //significa che non è stato trovato nulla
    return &(tabInv->vettInv[i]);
}
void stampaInv(tabInv_t *tab){//questo stampa tutto
    for(int i=0;i<tab->nInv;i++)
        printf("%s %s;\n",tab->vettInv[i].nome,tab->vettInv[i].tipo);
    printf("\n");
}
void stampaInvDett(char* key,tabInv_t *tabInv){
    linkInv oggetto;
    oggetto=ricercaInv(key,tabInv);
    printf("HP:%d MP:%d ATK:%d DEF:%d MAG:%d SPR:%d",oggetto->stat.hp,oggetto->stat.mp,oggetto->stat.atk,oggetto->stat.def,oggetto->stat.mag,oggetto->stat.spr);
}
void inventario(tabInv_t *tabInv){
    int cmd,term=0;
    char o[MAX_CHAR];
    do{
        printf("\nInserisci comando:\n"
               "1 - Visualizza Inventario;\n"
               "2 - Stampa dettagli oggetto <nome_oggetto>;\n"
               "3 - Torna al menu principale.\n");
        scanf("%d",&cmd);
        switch(cmd){
            case 1: stampaInv(tabInv); break;
            case 2: scanf("%s",o);
                    printf("Stampo dettagli di %s\n",o);
                    stampaInvDett(o,tabInv);
                    break;
            case 3: term=1; break;
            default: fprintf(stderr,"Errore comando inserito errato.\n"); break;
        }
    }while (!term);
}
void freeElementoV(inv_t elemento){
    free(elemento.nome);
    free(elemento.tipo);
}
void freeInventario(tabInv_t *tab){
    for(int i=0;i<tab->nInv;i++){
        freeElementoV(tab->vettInv[i]);
    }
    free(tab->vettInv);
    free(tab);
}
