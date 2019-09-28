//
// Created by 259105 on 28/09/2019.
//

#include <stdio.h>
#include <stdlib.h>
#define maxN 30

void ruota(int V[maxN], int N, int P, int dir);
void ruota(int V[maxN], int N, int P, int dir){
    int i,j=0,Vn[N];

    for(i=N-P-dir-1;i<=N-1;i++){
        Vn[j]=V[i];
        j++;
    }
    for(i=0;i!=N-P-dir-1;i++){
        Vn[j]=V[i];
        j++;
    }
    i=0;j=0;
    while(i!=N && j!=N){
        V[i]=Vn[j];
        i++;j++;
    }
}

int main(){
    int N,P,dir,V[maxN],i,err=0,s=0;

    while(err==0){
        printf("Inserisci la lunghezza del vettore:\n");
        scanf("%d", &N);
        if (N > maxN) {
            fprintf(stderr, "Errore la lunghezza è maggiore di 30.\n Re-inseriscilo.\n");
        }else{
            err=1;
        }
    }
    printf("Inserisci il vettore da ruotare:\n");
    for(i=0;i<N;i++){
        scanf("%d",&V[i]);
    }
    do {
        printf("Inserisci il numero di posizioni in cui ruotare(0 per terminare):\n");
        scanf("%d",&P);
        if(P==0){
            s=1;
        }
        if(P!=0){
            printf("Inserisci la direzione in cui ruotare(1 per Sx, -1 per Dx):\n");
            scanf("%d",&dir);
            ruota(V,N,P,dir);
            for (i=0;i<N;i++){
                printf("%d",V[i]);
            }
            printf("\n");
        }
    }while(s==0);

    return 0;
}
