//
// Created by s259105 on 19/01/2020.
//

#ifndef TITOLI_H
#define TITOLI_H
#define maxchar 20
#include "titolo.h"
#include "quotazioni.h"

typedef struct _titoli *titoli;

titoli TITOLIinit();
void TITOLIfree(titoli t);
titolo TITOLIinsertW(titoli T,char *cod);
titolo TITOLIsearch(titoli T,char *cod);


#endif //TITOLI_H
