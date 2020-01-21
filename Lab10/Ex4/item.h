//
// Created by s259105 on 08/01/2020.
//

#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>

typedef struct item *Item;
typedef char *key;

key KEYget(Item val);
int KEYcompare(key k1,key k2);

Item ITEMnew(void);
void ITEMfree(Item val);
Item ITEMload(char *id_e,char *id_r);
Item ITEMsetvoid(Item val);
void ITEMshow(Item val);
int ITEMcompare(Item val1,Item val2);


#endif //ITEM_H
