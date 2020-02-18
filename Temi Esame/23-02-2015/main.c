//
// Created by s259105 on 18/02/2020.
//
#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

void CountingSort(int *A, int N) {
    int i, l=0, r=N-1,k=0;
    //ricerca del massimo
    for(i=0;i<N;i++)
        if(A[i]>k)
            k=A[i];
    k++;
    int *C=calloc(k, sizeof(int)),*B=malloc(sizeof(int)*N);

    for (i = l; i <= r; i++)
        C[A[i]]++;

    for (i = 1; i < k; i++)
        C[i] += C[i-1];

    for (i = r; i >= l; i--) {
        B[C[A[i]]-1] = A[i];
        C[A[i]]--;
    }

    for (i = l; i <= r; i++)
        A[i] = B[i];
}

int main(int argc,char** argv){
    if(argc!=3) exit(1);
    FILE *fg,*fs;
    fg=fopen(argv[1],"r");
    fs=fopen(argv[2],"r");
    if(fg==NULL || fs==NULL) exit(2);
    Graph G=GRAPHload(fg);
    int **M,nv[2],*I=NULL,ni;
    int k,p;
    char label1[21],label2[21];
    M=GRAPHsolLoad(G,fs,nv);
    I=intersezione(G,M[0],M[1],nv[0],nv[1],&ni);
    Gpathstoreintersection(G,stdout,M,I,ni,nv);
    printf("Inserisci <k> <p> <sorgente> <destinazione>:\n");
    scanf("%d %d %s %s",&k,&p,label1,label2);
    GRAPHpathvincoled(G,stdout,k,p,label1,label2);
    GRAPHfree(G);
    fclose(fg);fclose(fs);
    return 0;
}
