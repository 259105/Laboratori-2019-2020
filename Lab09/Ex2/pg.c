//
// Created by s259105 on 12/12/2019.
//
#include <stdio.h>

#include "pg.h"

int pg_read(FILE *fp, pg_t *pgp){
    if(fscanf(fp,"%s%s%s%d%d%d%d%d%d",pgp->cod,pgp->nome,pgp->classe,&pgp->b_stat.hp,&pgp->b_stat.mp,&pgp->b_stat.atk,&pgp->b_stat.def,&pgp->b_stat.mag,&pgp->b_stat.spr)>0){
        pgp->eq_stat.spr=pgp->eq_stat.mag=pgp->eq_stat.def=pgp->eq_stat.atk=pgp->eq_stat.mp=pgp->eq_stat.hp=0;
        pgp->equip=equipArray_init();
        return 1;
    } else return 0;
}
void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}
void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    stat_t stat_e=stat_somma(pgp->b_stat,pgp->eq_stat);
    fprintf(fp,"\n%s %s %s\n",pgp->cod,pgp->nome,pgp->classe);
    stat_print(stdout,&stat_e,MIN_STAT);
    equipArray_print(stdout,pgp->equip,invArray);
}
void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip,invArray,&pgp->eq_stat);
}
