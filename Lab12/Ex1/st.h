//
// Created by s259105 on 19/01/2020.
//

#ifndef ST_H
#define ST_H
#define MAXCHAR 30+1

typedef struct _st *st;

st STinit();
void STfree(st t);
int STsearch(st t,char *s);
char* STsearchByIndex(st t,int i);
void STinsert(st t,char *s);
#endif //ST_H
