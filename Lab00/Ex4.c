//
// Created by 259105 on 28/09/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20

int main(){
    int M[N][N],Mmax[N][N],err,somma=0,max=0,dimmax=0,nm; //variabili utili
    int nr,nc,dim; //input da file e tastiera
    int i,j,y,k,r=0,c=0; //contatori per indici
    char nfile[N+1];
    FILE *fp;

    do {
        err=0;
        printf("Inserisci il nome del file da aprire:\n");
        scanf("%s", nfile);
        if(strlen(nfile)>20){
            err=1;
            fprintf(stderr,"Errore hai inserito un nome file troppo lungo(max 20 char).\n");
        }
        if((fp=fopen(nfile,"r"))==NULL && err!=1){
            fprintf(stderr,"Errore file non trovato.\n");
            err=1;
        }
    }while (err==1);

    fscanf(fp,"%d %d",&nr,&nc);
    if(nr>20 && nc>20){
        fprintf(stderr,"Errore le righe e colonne del file sono troppo grandi.(max 20)\n");
        return 1;
    }

    while(!feof(fp)){
        for (i=0;i<nr;i++) {
            for (j = 0; j < nc; j++) {
                fscanf(fp,"%d",&M[i][j]);
            }
        }
    }
    if(nr<nc){
        nm=nr;
    }else{
        nm=nc;
    }

    do{
        printf("Inserisci la dimensione della sottomatrice quadrata: (se maggiore di %d termina programma)\n",nm);
        scanf("%d",&dim);

        if(dim<=nr && dim<=nc){
            for(i=0;i<=(nr-dim);i++){
                for(j=0;j<=(nc-dim);j++){
                    for(k=i;k<(i+dim);k++){
                        for(y=j;y<(j+dim);y++){
                            somma=somma+M[k][y];
                            printf("%d ",M[k][y]);
                        }
                        printf("\n");
                    }
                    if(somma>max){
                        for(k=i;k<(i+dim);k++){
                            for(y=j;y<(j+dim);y++){
                                Mmax[r][c]=M[k][y];
                                c++;
                            }
                            r++;c=0;
                        }
                        max=somma;dimmax=dim;
                        somma=0;
                        c=0;r=0;
                    }else{
                        somma=0;
                    }
                    printf("\n\n");
                }
            }
        }else{
            err=1;
        }
    }while (err==0);

    printf("La submatrice con la somma degli elementi massima e':\n");
    for (i=0;i<dimmax;i++) {
        for (j = 0; j < dimmax; j++) {
            printf("%d ",Mmax[i][j]);
        }
        printf("\n");
    }

    return 0;
}