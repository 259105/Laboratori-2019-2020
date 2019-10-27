//
// Created by s259105 on 12/10/2019.
//

#include <stdio.h>
#define MAXR 50

/*
 * MIGLIORATO RISPETTO LAB_2
 *
 *  Creo un vettore di strutture fatto da 3 elementi: 0 per l'area massima e 1 e 2 per base e altezza rispettivamente
 *  Per ogni casella della matrice, mando le coordinate nella funzione riconosciregione che controlla quanto sono grandi
 *  base e altezza, durante il controllo l'intera area viene cambiata in 2 per non ricontrollarla.
 *  Avendo restituito i valori di Base e Altezza li confronto con i massimi e in caso li sostituisco. Stampo tutto.
 */

typedef struct {
    int r,c,h,b;
}rettangoli;

int leggimatrice(int M[][MAXR],int *nr,int *nc){ //Da domandare
    FILE *fp;
    int i,j;

    if((fp=fopen("matrice.txt","r"))==NULL){
        fprintf(stderr,"Errore apertura file");
        return 1;
    }
    fscanf(fp,"%d %d",nr,nc);
    for(i=0;i<*nr;i++){
        for(j=0;j<*nc;j++){
            fscanf(fp,"%d",&M[i][j]);
        }
    }
    return 0;
}

int riconosciRegione(int M[][MAXR],int nr,int nc,int r,int c,int *b,int *h){
    int y,x;//Servono per ciclo annidato che rende i valori del rettangolo trovato in 2
    if(M[r][c]==1){
        *b=1;
        *h=1;
        M[r][c]=2; //cambio il valore in 2 cosi non conto i rettangoli gia visti
        //controllo a destra
        while(M[r][c+*b]==1 && c+*b<=nc){
            M[r][c+*b]=2;
            *b+=1;
        }
        //controllo giù
        while(M[r+*h][c]==1 && r+*h<=nr){
            M[r+*h][c]=2;
            *h+=1;
        }
        //cambio i valori interni del rettangolo trovato in 2
        for(y=r+1;y<r+*h;y++){
            for(x=c+1;x<c+*b;x++){
                M[y][x]=2;
            }
        }
        return 1;
    }
    return 0;
}

void salvamassimo(rettangoli rett[],int r,int c,int b,int h,int n){
    rett[n].r=r;
    rett[n].c=c;
    rett[n].b=b;
    rett[n].h=h;
}

int main(){
    int M[MAXR][MAXR];
    int nr,nc,b,h;
    int r,c;
    rettangoli rett[3]={0};
    /*
     * 0 := Area massima
     * 1 := Base massima
     * 2 := Altezza massima
     */

    if(leggimatrice(M,&nr,&nc)){
        return 1;
    }

    printf("Rettangoli individuati:\n"
           "Posizione\tBase\tAltezza\tArea\n");

    for(r=0;r<nr;r++){
        for(c=0;c<nc;c++){
            if (riconosciRegione(M,nr,nc,r,c,&b,&h)) {
                printf("(%d,%d)\t\t%d\t%d\t%d\n",r,c,b,h,b*h);
            }
            //controllo i massimi
            if(b*h>rett[0].b*rett[0].h) {
                salvamassimo(rett,r,c,b,h,0);
            }
            if(b>rett[1].b){
                salvamassimo(rett,r,c,b,h,1);
            }
            if(h>rett[2].h){
                salvamassimo(rett,r,c,b,h,2);
            }
        }
    }
    printf("\nMax Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d",rett[1].r,rett[1].c,rett[1].b,rett[1].h,rett[1].b*rett[1].h);
    printf("\nMax Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d",rett[2].r,rett[2].c,rett[2].b,rett[2].h,rett[2].b*rett[2].h);
    printf("\nMax Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d",rett[0].r,rett[0].c,rett[0].b,rett[0].h,rett[0].b*rett[0].h);
    return 0;
}
