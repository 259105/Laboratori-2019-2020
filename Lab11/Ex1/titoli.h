//
// Created by s259105 on 19/01/2020.
//

#ifndef TITOLI_H
#define TITOLI_H
#define maxchar 20

#include "quotazioni.h"
typedef struct _titolo *titolo;
typedef struct _titoli *titoli;

titoli TITOLIinit();
void TITOLIfree(titoli t);
titolo TITOLIinsertW(titoli T,char *cod);
void TITOLOinsert(titolo t,quotazione q);
titolo TITOLIsearch(titoli T,char *cod);
quotazioni QbyT(titolo t);

#endif //TITOLI_H
