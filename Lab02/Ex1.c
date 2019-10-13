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

void calcolomassimo(int *massimo,int *massimo_x,int *massimo_y,int valore,int posizione_x,int posizione_y){
    if(valore>*massimo){
        *massimo=valore;
        *massimo_x=posizione_x;
        *massimo_y=posizione_y;
    }
}

int main(){
    int M[N][N];
    int nr,nc;
    int i,j,c=0,x,y; //contatori vari
    int max_b=0,max_b_x=0,max_b_y=0; //variabili utilizzate per ospitare tutti i massimi
    int max_h=0,max_h_x=0,max_h_y=0;
    int max_A=0,max_A_x=0,max_A_y=0;
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
                calcolomassimo(&max_A,&max_A_x,&max_A_y,rett[c].A,rett[c].pos_x,rett[c].pos_y);//massima Area
                calcolomassimo(&max_b,&max_b_x,&max_b_y,rett[c].b,rett[c].pos_x,rett[c].pos_y);//massima base
                calcolomassimo(&max_h,&max_h_x,&max_h_y,rett[c].h,rett[c].pos_x,rett[c].pos_y);//massima altezza
                c++;
            }
        }
    }
    printf("\nIl rettangolo con l'altezza maggiore e' posizionato in r:%d c:%d, con un'altezza di %d",max_h_x+1,max_h_y+1,max_h);
    printf("\nIl rettangolo con la larghezza maggiore e' posizionato in r:%d c:%d, con una larghezza di %d",max_b_x+1,max_b_y+1,max_b);
    printf("\nIl rettangolo con l'area maggiore e' posizionato in r:%d c:%d, con un'area di %d",max_A_x+1,max_A_y+1,max_A);
    return 0;
}
