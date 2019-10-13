//
// Created by s259105 on 12/10/2019.
//

#include <stdio.h>
#define N 50

typedef struct {
    int pos_x,pos_y,h,b,A;
}rettangoli;

int leggimatrice(int matrice[][N],int *nr,int *nc){
    FILE *fp;
    int i,j;

    if((fp=fopen("matrice.txt","r"))==NULL){
        fprintf(stderr,"Errore apertura file");
        return 1;
    }
    fscanf(fp,"%d %d",nr,nc);
    for(i=0;i<*nr;i++){
        for(j=0;j<*nc;j++){
            fscanf(fp,"%d",&matrice[i][j]);
        }
    }
    return 0;
}

int main(){
    int M[N][N];
    int nr,nc;
    int i,j,c=0,x,y; //contatori vari
    int c_b,c_h,c_A;
    rettangoli rett[N/2+1];

    if(leggimatrice(M,&nr,&nc)){
        return 1;
    }

    printf("Rettangoli individuati:\n"
           "Posizione\tBase\tAltezza\tArea\n");

    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if(M[i][j]==1){
                rett[c].pos_x=i;
                rett[c].pos_y=j;
                rett[c].b=1;
                rett[c].h=1;
                M[i][j]=2; //cambio il valore in 2 cosi non conto i rettangoli gia visti
                //controllo a destra
                while(M[i][j+rett[c].b]==1){
                    M[i][j+rett[c].b]=2;
                    rett[c].b++;
                }
                //controllo a sinistra
                while(M[i+rett[c].h][j]==1){
                    M[i+rett[c].h][j]=2;
                    rett[c].h++;
                }
                //calcolo Area
                rett[c].A=rett[c].b*rett[c].h;
                //cambio i valori interni del rettangolo trovato in 2
                for(y=i+1;y<i+rett[c].h;y++){
                    for(x=j+1;x<j+rett[c].b;x++){
                        M[y][x]=2;
                    }
                }
                //stampo il rettangolo trovato
                printf("%d)%d,%d\t\t%d\t%d\t%d\n",c+1,rett[c].pos_x+1,rett[c].pos_y+1,rett[c].b,rett[c].h,rett[c].A);
                //trovo i massimi e mi salvo il loro indice
                if(c==0){
                    c_A=c;
                    c_b=c;
                    c_h=c;
                }
                if(rett[c].A>rett[c_A].A)
                    c_A=c;
                if(rett[c].b>rett[c_b].b)
                    c_b=c;
                if(rett[c].h>rett[c_h].h)
                    c_h=c;
                c++;
            }
        }
    }
    printf("\nMax Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d",rett[c_b].pos_x,rett[c_b].pos_y,rett[c_b].b,rett[c_b].h,rett[c_b].A);
    printf("\nMax Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d",rett[c_A].pos_x,rett[c_A].pos_y,rett[c_A].b,rett[c_A].h,rett[c_A].A);
    printf("\nMax Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d",rett[c_h].pos_x,rett[c_h].pos_y,rett[c_h].b,rett[c_h].h,rett[c_h].A);
    return 0;
}
