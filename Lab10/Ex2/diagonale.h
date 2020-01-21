//
// Created by s259105 on 23/12/2019.
//

#ifndef DIAGONALE_H
#define DIAGONALE_H

#include "elemento.h"
#define MAXELEM 5

typedef struct diagonale_* diagonale;
struct diagonale_{//Quasi ADT diagonale
    elemento e[MAXELEM];
    int n_elem;
    float pnt;
    int diff;
};

diagonale DIAGONALEinit(void);
diagonale* DIAGONALEarrayinit(int n);
void DIAGONALEfree(diagonale t);
void DIAGONALEinsert(diagonale t,elemento elem);
void DIAGONALEremove(diagonale t);
void DIAGONALEcopy(diagonale t1,diagonale t2);

#endif //DIAGONALE_H
