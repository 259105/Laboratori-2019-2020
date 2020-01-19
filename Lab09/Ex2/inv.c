//
// Created by s259105 on 11/12/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "inv.h"

void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp,"%d%d%d%d%d%d",&statp->hp,&statp->mp,&statp->atk,&statp->def,&statp->mag,&statp->spr);
}
void stat_print(FILE *fp, stat_t *statp, int soglia){
    //se la soglia è ==-1 significa che voglio vedere anche i numeri negativi
    //qualcosa mi puzzaa
    // se io sto stmpando l'inventario voglio vedere anche i numeri negativi
    fprintf(fp,"HP: %d\n"
               "MP: %d\n"
               "ATK: %d\n"
               "DEF: %d\n"
               "MAG: %d\n"
               "SPR: %d\n",
            soglia<0?statp->hp:(statp->hp<soglia?soglia:statp->hp),
            soglia<0?statp->mp:(statp->mp<soglia?soglia:statp->mp),
            soglia<0?statp->atk:(statp->atk<soglia?soglia:statp->atk),
            soglia<0?statp->def:(statp->def<soglia?soglia:statp->def),
            soglia<0?statp->mag:(statp->mag<soglia?soglia:statp->mag),
            soglia<0?statp->spr:(statp->spr<soglia?soglia:statp->spr));
}

void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp,"%s%s",invp->nome,invp->tipo);
    stat_read(fp,&invp->stat);
}
void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp,"\n%s %s\n",invp->nome,invp->tipo);
}

stat_t inv_getStat(inv_t *invp){
    return (invp->stat);
}
char* inv_getName(inv_t *invp){
    return (invp->nome);
}
stat_t stat_somma(stat_t b,stat_t eq){
    stat_t t;
    t.hp=b.hp+eq.hp;
    t.mp=b.mp+eq.mp;
    t.atk=b.atk+eq.atk;
    t.def=b.def+eq.def;
    t.mag=b.mag+eq.mag;
    t.spr=b.spr+eq.spr;
    return t;
}
stat_t stat_differenza(stat_t b,stat_t eq){
    stat_t t;
    t.hp=b.hp-eq.hp;
    t.mp=b.mp-eq.mp;
    t.atk=b.atk-eq.atk;
    t.def=b.def-eq.def;
    t.mag=b.mag-eq.mag;
    t.spr=b.spr-eq.spr;
    return t;
}
