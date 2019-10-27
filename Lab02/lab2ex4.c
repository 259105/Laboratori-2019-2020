//
// Created by s259105 on 16/10/2019.
//

// In questo esercizio bisogna comparare diverse tipologie di ordinamento dati:selection sort,insertion sort,shell sort

#include <stdio.h>
#include <stdlib.h>
#define max 100

typedef int ITEM;

typedef struct{
    int nscambi,niterest,niterint,totiter;
}DATI;

void ITEMcpy(ITEM v[],ITEM v1[],int n){
    int i;
    for(i=0;i<n;i++){
        v[i]=v1[i];
    }
}

int ITEM1min2(ITEM a,ITEM b){
    return a<b;
}
void SelectionSort(DATI dati,ITEM V[],int n){
    dati.niterest=0;
    dati.niterint=0;
    dati.nscambi=0;
    dati.totiter=0;
    int i,j,l=0,r=n-1,min;
    ITEM temp;
    for(i=l;i<=r;i++){
        min=i;
        dati.niterest++;
        printf("%d) ",dati.niterest);
        for(j=i+1;j<=r;j++){
            if(ITEM1min2(V[j],V[min])){
                min=j;
            }
            dati.niterint++;
        }
        printf("%d\n",dati.niterint);
        if(min!=i){
            temp=V[i];
            V[i]=V[min];
            V[min]=temp;
            dati.nscambi++;
        }
    }
    dati.totiter=dati.niterest*dati.niterint;
    printf("Scambi: %d; Iteazioni totali: %d",dati.nscambi,dati.totiter);
}

void InsertionSort(DATI dati,ITEM A[],int n){
    dati.niterest=0;
    dati.niterint=0;
    dati.nscambi=0;
    dati.totiter=0;
    int i,j,l=0,r=n-1;
    ITEM x;
    for(i=l+1;i<=r;i++){
        dati.niterest++;
        x=A[i];
        j=i-1;
        printf("%d) ",dati.niterest);
        while(j>=l && ITEM1min2(x,A[j])){
            A[j+1]=A[j];
            j--;
            dati.niterint++;
            dati.nscambi++;
        }
        printf("%d\n",dati.niterint);
        A[j+1]=x;
    }
    dati.totiter=dati.niterest*dati.niterint;
    printf("Scambi: %d; Iteazioni totali: %d",dati.nscambi,dati.totiter);
}

void ShellSort(DATI dati,ITEM A[],int n){
    dati.niterest=0;
    dati.niterint=0;
    dati.nscambi=0;
    dati.totiter=0;
    int i,j,l=0,r=n-1,h=1;
    ITEM temp;
    while(h<3/r){
        h=3*h+1;
    }
    while (h>=1) {
        for (i=l+h;i<=r;i++) {
            dati.niterest++;
            j=i;
            temp=A[j];
            printf("%d) ",dati.niterest);
            while (j>=l+h && ITEM1min2(temp,A[j-h])) {
                A[j] = A[j-h];
                j=j-h;
                dati.niterint++;
                dati.nscambi++;
            }
            printf("%d\n",dati.niterint);
            A[j]=temp;
        }
        h=h/3;
    }
    dati.totiter=dati.niterest*dati.niterint;
    printf("Scambi: %d; Iteazioni totali: %d",dati.nscambi,dati.totiter);
}

int main(){
    int s,i,j,l;
    ITEM V[max],V1[max];
    DATI dati={0};
    FILE *fp;

    if((fp=fopen("sort.txt","r"))==NULL){
        fprintf(stderr,"Errore lettura file");
        return 1;
    }
    fscanf(fp,"%d",&s);

    for(i=0;i<s;i++){
        fscanf(fp,"%d",&l);
        if(l<max){
            for(j=0;j<l;j++){
                fscanf(fp,"%d",&V[j]);
            }
        }else{
            fprintf(stderr,"Errore i numeri da ordinare sono maggiori del massimo supportato.\n");
            return 1;
        }
        ITEMcpy(V1,V,l);
        printf("\nSelectionSort riga %d\n",i);
        SelectionSort(dati,V1,l);
        printf("\nInsertionSort riga %d\n",i);
        ITEMcpy(V1,V,l);
        InsertionSort(dati,V1,l);
        printf("\nShellSort riga %d\n",i);
        ITEMcpy(V1,V,l);
        ShellSort(dati,V1,l);

    }
    return 0;
}
