//
// Created by s259105 on 15/02/2020.
//

#ifndef SOLUZIONE_H
#define SOLUZIONE_H
#include <stdio.h>

typedef struct{
    int k,t;
}Sol;

Sol* SOLvettload(FILE *fin,int N);
void SOLvettfree(Sol *sol);
Sol SOLcreate(int k,int t);
void SOLvettstorage(FILE *fo,Sol *sol,int N);

#endif //SOLUZIONE_H
