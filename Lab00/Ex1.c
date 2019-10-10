//
// Created by 259105 on 27/09/2019.
//

#include <stdio.h>
#include <stdlib.h>
#define N 30

int main(){
    int v[N]={0} ,i=0,count=0,max=0,serie=0,p[15],n,j=0,f=0,k=0;

    printf("Inserisci vettore: (-1 per finale)\n");

    /*for(i=0;i<N;i++){ // inizializzo il vettore con tutti 0
        v[i]=0;
    }*/

    for(i=0;i<N && f!=1;i++){ // metto l'input nel vettore e mi fermo quando c'è il -1
        scanf("%d",&n);
        if(n!=-1){
            v[i]=n;
        }else{
            f=1;
        }
    }

    for(i=0;i<N;i++){  // controllo quanto è il numero massimo di numeri consecutivi diversi da 0
        if(v[i]==0){
            count=0;
        }else{
            count++;
            if(count==max){
                p[j]=i;
                j++;
                serie++;
            }
            if(count>max){
                max=count;
                j=0;
                p[j]=i;
                j++;
                serie=1;
            }
        }
    }

    while(k<serie){  // fase finale del print f stampo seguento la logica: prendo l'ultimo numero della serie in considerazione
        for(i=p[k]-max+1;i<=p[k];i++) // gli sottraggo quanto è grande la serie (è il massimo) e gli aggiungo 1 per far
            printf("%d",v[i]);       // tornare i conti, ripeto questo processo per tutte le serie prese prima.
        printf("\n");
        k++;
    }

    return 0;
}
