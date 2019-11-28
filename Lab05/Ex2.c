//
// Created by s259105 on 10/11/2019.
//

#include <stdlib.h>
#include <stdio.h>
#define file "mat.txt"

int** malloc2dR(int nr,int nc){
    int i,**m;
    m=(int **)malloc(nr* sizeof(int*));
    for(i=0;i<nr;i++)
        m[i]=(int *)malloc(nc* sizeof(int));
    return m;
}
void free2dR(int **m,int nr){
    int i;
    for(i=0;i<nr;i++)
        free(m[i]);
    free(m);
}
int** leggifileealloca(int *nr,int *nc){
    FILE *fp;
    int i,j;
    int **m;
    if((fp=fopen(file,"r"))==NULL){
        fprintf(stderr,"Errore lettura file");
        return 0;
    }
    fscanf(fp,"%d %d",nr,nc);
    m=malloc2dR(*nr,*nc);
    for(i=0;i<*nr;i++)
        for(j=0;j<*nc;j++)
            fscanf(fp,"%d",&m[i][j]);
    return m;
}
void stampaBiancoNero(int *vb,int *vn,int nr,int nc){
    int i;
    //mi ricavo le dimensioni dei vettori bianco e nero
    int db,dn;
    if(nr%2 && nc%2){ //se sono dispari
        db=(nr*nc+1)/2;
        dn=(nr*nc+1)/2-1;
    }else //se sono pari
        db=dn=(nr*nc)/2;
    for(i=0;i<db;i++)
        printf("%d ",vb[i]);
    printf("\n");
    for(i=0;i<dn;i++)
        printf("%d ",vn[i]);
}
void separaestampa(int **mat, int nr, int nc,int *vb,int *vn){
    int i,j;
    int b=0,n=0;
    // d è la dimmensione dei vettori del bianco e del nero
    // se il prodotto tra nr e nc è pari allora d=nr*nc/2 senno d=(nr*nc+1)/2
    int d=((nr*nc)%2==0?nr*nc/2:(nr*nc+1)/2);
    // se le 2 dimensione della matrice sono dispari allora il vettore bianco è di un
    // elemento manggioe al vettore b
    int a=0;
    if(nr%2 && nc%2)
        a=1;
    vb=(int *)malloc( d*sizeof(int) );
    vn=(int *)malloc( (d-a)* sizeof(int) );
    for(i=0;i<nr;i++)
        for(j=0;j<nc;j++){
            if((i+j)%2==0)
                vb[b++]=mat[i][j];
            else
                vn[n++]=mat[i][j];
        }
    stampaBiancoNero(vb,vn,nr,nc);
}
void stampamatrice(int **m,int nr,int nc){
    int i,j;
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            printf("%d",m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(void){
    int **m=NULL;
    int nr,nc;
    int *vb=NULL,*vn=NULL;
    if((m=leggifileealloca(&nr,&nc))==NULL)
        return 1;
    stampamatrice(m,nr,nc);
    separaestampa(m,nr,nc,vb,vn);
    free2dR(m,nr);
    return 0;
}
