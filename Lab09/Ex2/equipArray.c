//
// Created by s259105 on 12/12/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "equipArray.h"

struct equipArray_s{
    int inUso;
    int vettEq[EQUIP_SLOT];
};

equipArray_t equipArray_init(){
    equipArray_t t=NULL;
    t=malloc(sizeof(*t));
    if(t==NULL) {
        fprintf(stderr, "Errore di allocazione");
        exit(1);
    }
    for(int i=0;i<EQUIP_SLOT;i++)
        t->vettEq[i]=-1; //inizializzo vettore di indici a -1
    t->inUso=0;
    return t;
}
void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUso;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    for(int i=0;i<EQUIP_SLOT;i++)
        if(equipArray->vettEq[i]!=-1)
            invArray_printByIndex(fp,invArray,equipArray_getEquipByIndex(equipArray,i));
}

int equipArray_menu(){
    int cmd;
    printf("\nSeleziona comando:\n"
           "1 - Aggiungi Equipaggiamento al PG;\n"
           "2 - Rimuovi Equipaggiamento al Pg;\n"
           "3 - Stampa equipaggiamento Pg;\n"
           "4 - Torna al menu'.\n");
    scanf("%d",&cmd);
    return cmd;
}
void equipArray_remove(equipArray_t equipArray,invArray_t invArray,stat_t *eq_stat){
    char label[LEN];
    int index,i;
    equipArray_print(stdout,equipArray,invArray);
    printf("\nInserisci nome oggetto da eliminare dall'equipaggiamento:\n");
    scanf("%s",label);
    if((index=invArray_searchByName(invArray,label))==-1){
        fprintf(stderr,"Errore oggetto non trovato\n");
        return;
    }
    for(i=0;i<EQUIP_SLOT && equipArray->vettEq[i]!=index;i++);
    equipArray->vettEq[i]=-1;
    equipArray->inUso--;
    *eq_stat=stat_differenza(*eq_stat,inv_getStat(invArray_getByIndex(invArray,index)));
}
void equipArray_insert(equipArray_t equipArray,invArray_t invArray,stat_t *eq_stat){
    char label[LEN];
    int index,i;
    equipArray_invArrayPrintDisp(stdout,equipArray,invArray);
    printf("\nInserisci nome oggetto da aggiungere nell'equipaggiamento:\n");
    scanf("%s",label);
    if((index=invArray_searchByName(invArray,label))==-1){
        fprintf(stderr,"Errore oggetto non trovato\n");
        return;
    }
    if(!equipArray_checkIndex(equipArray,index)){
        fprintf(stderr,"Errore oggetto gia' presente nell'intervallo\n");
        return;
    }
    for(i=0;i<EQUIP_SLOT && equipArray->vettEq[i]!=-1;i++);
    /*non faccio il controllo se è arrivato alla fine perché sono sicuro che c'è posto*/
    equipArray->vettEq[i]=index;
    equipArray->inUso++;
    *eq_stat=stat_somma(*eq_stat,inv_getStat(invArray_getByIndex(invArray,index)));
}
void equipArray_update(equipArray_t equipArray, invArray_t invArray,stat_t *eq_stat){
    if(equipArray_check(equipArray)==1){
        printf("\nL'Equipaggiamento e' pieno.\n");
        equipArray_remove(equipArray,invArray,eq_stat);
    } else if (equipArray_check(equipArray)==-1){
        printf("\nL'Equipaggiamento e' vuoto.\n");
        equipArray_insert(equipArray,invArray,eq_stat);
    }else{
        switch (equipArray_menu()){
            case 1: equipArray_insert(equipArray,invArray,eq_stat); break;
            case 2: equipArray_remove(equipArray,invArray,eq_stat); break;
            case 3: equipArray_print(stdout,equipArray,invArray);
            case 4: return;
        }
    }
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    return equipArray->vettEq[index];
}

int equipArray_check(equipArray_t equipArray){
    if(!equipArray_inUse(equipArray)) return -1;
    if(equipArray_inUse(equipArray)==EQUIP_SLOT) return 1;
    return 0;
}

int equipArray_checkIndex(equipArray_t equipArray,int index){
    /*faccio una ricerca lineare sull'equip, se è presente l'elemento ritorno 0*/
    for(int i=0;i<EQUIP_SLOT;i++)
        if(equipArray->vettEq[i]==index)
            return 0;//l'elemento è gia presente
    return 1;
}

void equipArray_invArrayPrintDisp(FILE *fp,equipArray_t equipArray,invArray_t invArray){
    //stampo solo gli elementi disponibili
    for(int i=0;i<invArray_getNinv(invArray);i++)
        if(equipArray_checkIndex(equipArray,i))
            invArray_printByIndex(fp,invArray,i);
}

