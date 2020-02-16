//
// Created by s259105 on 15/02/2020.
//

#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct node_ *link;
struct node_{
    int v;
    link next;
};
typedef struct{
    link h,z;
    int n;
}Lista;

Lista LISTAinit(void);
void LISTAfree(Lista l);
Lista  LISTAinsert(Lista l,int v);
Lista LISTAremove(Lista l);
Lista LISTAdup(Lista l1,Lista l2);
int LISTAcmp(Lista l1,Lista l2);
void LISTAstorage(FILE *fo,Lista l);


#endif //LIST_H
