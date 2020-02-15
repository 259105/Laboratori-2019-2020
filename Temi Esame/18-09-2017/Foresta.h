//
// Created by s259105 on 15/02/2020.
//

#ifndef FORESTA_H
#define FORESTA_H
#include "Soluzione.h"
#include <stdio.h>

typedef struct foresta_ *Foresta;

Foresta FORESTAinit(char *N,char *T,char *S,char *m);
void FORESTAfree(Foresta F);
Foresta FORESTAload(FILE *fk,FILE *ff,FILE *fe,char *N,char *T,char *S,char *m);
int check(Foresta F,Sol *sol);
void bestalloc(Foresta F);
int FORESTAkoala(Foresta F);

#endif //FORESTA_H
