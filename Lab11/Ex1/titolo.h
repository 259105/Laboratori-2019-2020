//
// Created by s259105 on 19/01/2020.
//

#ifndef TITOLO_H
#define TITOLO_H
#define maxchar 20
#include "quotazioni.h"

typedef struct _titolo *titolo;

void TITOLOinsert(titolo t,quotazione q);
titolo TITOLOinit(char *cod);
void TITOLOfree(titolo t);
quotazioni QbyT(titolo t);
char* CodbyT(titolo t);

#endif //TITOLO_H
