//
// Created by s259105.
//
#include <string.h>
#include <ctype.h>
#include "mylib.h"
void minuscolo(char *s){
    int i=0;
    for(i=0;i<(int)strlen(s);i++)
        s[i]=tolower(s[i]);
}
int confronta_stringhe(char *s1,char *s2){
    char stri1[MAX_CHAR],stri2[MAX_CHAR];//Creo questo 2 nuove stringhe per non modificare i caratteri nella struct
    strcpy(stri1,s1);
    strcpy(stri2,s2);
    minuscolo(stri1);
    minuscolo(stri2);
    return strcmp(stri1,stri2);
}