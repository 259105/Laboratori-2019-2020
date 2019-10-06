//
// Created by 259105 on 06/10/2019.
//

#include <stdio.h>
#include <stdlib.h>
#define max 20

void inizializzazionematrice(int matrice[][max],int n);
void inizializzazionevettore(int vettore[],int n);
void infoiniziali(int *s,int *g);
int leggifile(int matrice[][max],int s,int g);
void capolista(int matrice[][max],int s,int g);


int main(){
    int M[max][max]; //matrice rappresentativa del campionato
    int squadre,giornate;

    inizializzazionematrice(M,2);
    infoiniziali(&squadre,&giornate);
    squadre--;giornate--;
    if(leggifile(M,squadre,giornate)){
        capolista(M,squadre,giornate);
    }
    return 0;
}
void inizializzazionematrice(int matrice[][max],int n){
    int i,j;

    for (i=0;i<=max;i++){
        for (j=0;j<=max;j++){
            matrice[i][j]=n;
        }
    }
}

void inizializzazionevettore(int vettore[],int n){
    int i;

    for (i=0;i<=max;i++){
            vettore[i]=n;
    }
}

void infoiniziali(int *s,int *g){
    printf("Inserisci: <numero squadre> <numero giornate>\n");
    scanf("%d %d",s,g);
}

int leggifile(int matrice[][max],int s,int g){
    int i,j; //contatori
    FILE *fp;

    if((fp=fopen("campionato.txt","r"))==NULL){
        fprintf(stderr,"Errore file non trovato.\n");
        return 0;
    }
    for(i=0;i<=s;i++){
        for(j=0;j<=g;j++){
            fscanf(fp,"%d", &matrice[i][j]);
            if (matrice[i][j]!=1 && matrice[i][j]!=0 && matrice[i][j]!=3){
                fprintf(stderr,"Errore presente nel file numero diverso da 0,1 o 3");
                return 0;
            }
        }
    }
    return 1;
}

void capolista(int matrice[][max],int s,int g){
    int k=0,j=0;// contatore delle giornate e squadre
    int mx=0,i_mx=-1,totale[max];

    inizializzazionevettore(totale,0);
    for(k=0;k<=g;k++){
        for(j=0;j<=s;j++){
            totale[j]+=matrice[j][k];
            if(totale[j]>mx){
                mx=totale[j];
                i_mx=j;
            }
        }
        printf("La squadra capolista nella %d giornata e' %d con %d punti\n",k+1,i_mx+1,mx);
    }
}
