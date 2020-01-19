//
// Created by s259105 on 05/12/2019.
//
// IMPORTANTE.. PER CAPIRE AL MEGLIO IL PROGRAMMA BISOGNA AVERE ANCHE LO SCHEMA DELLE TABELLE
//controllare il fatto dei codici dei personaggi
#include <stdio.h>
#define MAX_CHAR 50
#define MAX_EQUIP 8
#include "inv.h"
#include "pg.h"

typedef enum{
    add=1,del,equip,stat,inv,term,err
}cmd_e;

cmd_e leggiComando(){
    int cmd;
    printf("Inserire comando(1..5):\n"
           "1 - Aggiungi nuovo personaggio;\n"
           "2 - Elimina personaggio;\n"
           "3 - Aggiungi/rimuovi oggetto dall'equipaggiamento di un personaggio;\n"
           "4 - Visualizza statistiche di un personaggio;\n"
           "5 - Visualizza inventario;\n"
           "6 - Fine.\n");
    scanf("%d",&cmd);
    return cmd;
}

int main(void){
    tabPg_t *tabPg;
    tabInv_t *tabInv;
    cmd_e cmd;
    int continua=1;

    tabPg=inputPg();
    tabInv=inputInv();

    while (continua){
        cmd=leggiComando();
        switch(cmd){
            case add: addPg(tabPg); break;
            case del: eliminaNodo(tabPg); break;
            case equip: equipaggiamento(tabPg,tabInv); break;
            case stat: statistiche(tabPg); break;
            case inv: inventario(tabInv); break;
            case term: continua=0; break;
            default: fprintf(stderr,"Errore comando inserito errato.\n"); break;
        }
    }

    freeLista(tabPg);
    freeInventario(tabInv);
}
