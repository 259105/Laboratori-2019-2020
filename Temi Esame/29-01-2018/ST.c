#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"

struct symbtab {char **a; int maxN; int size;};

ST STinit(int maxN) {
  int i;
  ST st;
  st = malloc(sizeof(*st));
  if (st == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  st->a = malloc(maxN * sizeof(char) );
  if (st->a == NULL) {
        printf("Memory allocation error\n");
        free(st);
        return NULL;
  }
  for(i=0;i<maxN;i++){
      st->a[i]=malloc(sizeof(char)*11);
      if (st->a[i] == NULL) {
          printf("Memory allocation error\n");
          free(st);
          return NULL;
      }
  }
  for (i = 0; i < maxN; i++)
    st->a[i][0] = '\0';
  st->maxN = maxN;
  st->size = 0;
  return st;
}

void STfree(ST st) {
    for(int i=0;i<st->maxN;i++)
        free(st->a[i]);
  free(st->a);
  free(st);
}

int STcount(ST st) {
  return st->size;
}

int STinsert(ST st, char* val) {
  int i = st->size;
  if (st->size >= st->maxN) {
    st->a = realloc(st->a, (2*st->maxN)*sizeof(char*));
    if (st->a == NULL){
      printf("Memory allocation error\n");
      free(st);
      return -1;
    }
    for(int j=st->size;j<2*st->maxN;j++){
        st->a[j]=malloc(sizeof(char)*11);
        if (st->a[j] == NULL){
            printf("Memory allocation error\n");
            free(st);
            return -1;
        }
    }
    st->maxN = 2*st->maxN;
  }
  strcpy(st->a[i],val);
  st->size++;
  return i;
}

int STsearch(ST st, char* k) {
  int i;
  if (st->size == 0)
    return -1;
  for (i = 0; i  < st->size; i++)
    if (strcmp(k, st->a[i])==0)
      return i;
  return -1;
}

char* STsearchByindex(ST st,int index){
    return st->a[index];
}
