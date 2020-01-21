//
// Created by s259105 on 08/01/2020.
//

#ifndef ST_H
#define ST_H

#include "item.h"

typedef struct symbltab *ST;

ST STinit(int v);
void STfree(ST st);
int STcount(ST st);
void STinsert(ST st,Item val);
int STsearch(ST st,key val);
key STsearchByIndex(ST st,int n);
//void STsort(ST st,int n);
//void STdelete(ST st,key val);


#endif //ST_H
