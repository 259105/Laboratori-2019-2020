//
// Created by s259105 on 04/12/2019.
//

#include <stdio.h>
#include <stdlib.h>
#define FILEScacchiera "board.txt"
#define FILETessere "tiles.txt"

typedef struct{
    int val;
    char color;
}tubo_t;
typedef struct{
    tubo_t vert;
    tubo_t oriz;
    int usata; //0 := non è usata 1:= è già usata
}tessera_t;

typedef struct {
    int n;  //indica il numero della tessera presa
    int orient;// 0:= come fa file (orizziondale-verticale) 1:= girato (verticale-orizzontale)
    // -1/-1 significa che la scacchiera è vuota
}scacchiera_t;

int b_val=0; //variabile globale

void ruotatessera(tessera_t *tessera,int k){
    tubo_t temp;
    temp=tessera[k].vert;
    tessera[k].vert=tessera[k].oriz;
    tessera[k].oriz=temp;
}
tessera_t* leggitessere(int *n){
    tessera_t* temp;
    FILE *fp;
    fp=fopen(FILETessere,"r");
    if(fp==NULL) exit(1);
    fscanf(fp,"%d%*c",n);
    temp=malloc(*n* sizeof(tessera_t));
    for(int i=0;i<*n;i++){
        fscanf(fp,"%c%d %c%d%*c",&temp[i].oriz.color,&temp[i].oriz.val,&temp[i].vert.color,&temp[i].vert.val);
        temp[i].usata=0;
    }
    fclose(fp);
    return temp;
}
scacchiera_t** malloc2d(int r,int c){
    int j;
    scacchiera_t **temp;
    temp=(scacchiera_t**)malloc(r*sizeof(scacchiera_t*));
    if(temp==NULL) exit(2);
    for(j=0;j<r;j++){
        temp[j]=(scacchiera_t*)malloc(c* sizeof(scacchiera_t));
        if(temp[j]==NULL) exit(2);
    }
    return temp;
}
scacchiera_t** leggiscacchiera(int *r,int *c,tessera_t *tessera){
    scacchiera_t **temp;
    FILE *fp;
    int ntess,orient;
    fp=fopen(FILEScacchiera,"r");
    if(fp==NULL){
        fprintf(stderr,"Errore file inserito non trovato");
        exit(1);
    }
    fscanf(fp,"%d%d",r,c);
    temp=malloc2d(*r,*c);
    for(int i=0;i<*r;i++)
        for(int j=0;j<*c;j++){
            fscanf(fp,"%d/%d",&ntess,&orient);
            // -1/-1 significa che la scacchiera è vuota
            temp[i][j].n=ntess;
            temp[i][j].orient=orient;
            if(orient==1)
                ruotatessera(tessera,ntess);
            tessera[ntess].usata=1;
        }
    fclose(fp);
    return temp;
}
void stampa(scacchiera_t **scacchiera,int r,int c){
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("%d/%d ",scacchiera[i][j].n,scacchiera[i][j].orient);
        }
        printf("\n");
    }
    printf("\nCon un valore: %d",b_val);
}
int calcolaval(scacchiera_t **scacchiera,tessera_t *tessera,int r,int c){
    //calcolo valori nelle colonne verticali
    int val=0,val_p;
    char colore;
    int i,j;
    for(i=0;i<r;i++){
        colore=tessera[scacchiera[i][0].n].oriz.color;//prendo colore della prima colonna
        val_p=val;
        for(j=0;j<c;j++){
            if(tessera[scacchiera[i][j].n].oriz.color==colore){// se ha lo stesso solore
                val+=tessera[scacchiera[i][j].n].oriz.val;
            }else{
                val=val_p;
                break;
            }
        }
    }
    for(i=0;i<c;i++){
        colore=tessera[scacchiera[0][i].n].vert.color;//prendo colore della prima colonna
        val_p=val;
        for(j=0;j<r;j++){
            if(tessera[scacchiera[j][i].n].vert.color==colore){// se ha lo stesso solore
                val+=tessera[scacchiera[j][i].n].vert.val;
            }else{
                val=val_p;
                break;
            }
        }
    }
    return val;
}
void aggiornamax(scacchiera_t **scacchiera,scacchiera_t **sol,int r,int c){
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            sol[i][j]=scacchiera[i][j];

}
void disp_sempl(scacchiera_t **scacchiera,tessera_t *tessere,scacchiera_t **b_sol,int r,int c,int n,int pos){
    int i,j,k,val_c;
    if(pos==r*c){//condizione di terminazione
        //controllo se è massimo
        val_c=calcolaval(scacchiera,tessere,r,c);
        if(val_c>b_val){
            //aggiorno i massimi
            aggiornamax(scacchiera,b_sol,r,c);
            b_val=val_c;
        }
        return;
    }
    i=pos/r;j=pos%c;
    if(scacchiera[i][j].orient!=-1 && scacchiera[i][j].n!=-1){//elemento della casella gia riempito
        disp_sempl(scacchiera,tessere,b_sol,r,c,n,pos+1);
        return;
    }
    for(k=0;k<n;k++){
        if(tessere[k].usata!=1){
            tessere[k].usata=1; // controllo che la tessera non è stata ancora presa e la segno come presa
            scacchiera[i][j].n=k;  scacchiera[i][j].orient=0; //orientamento originale
            disp_sempl(scacchiera,tessere,b_sol,r,c,n,pos+1);
            //cambio orientamento
            scacchiera[i][j].orient=1;
            ruotatessera(tessere,k);//ruota di 90* i 2 tubi, ovvero li inverte
            disp_sempl(scacchiera,tessere,b_sol,r,c,n,pos+1);
            // backtrack
            scacchiera[i][j].n=-1; scacchiera[i][j].orient=-1; tessere[k].usata=0; ruotatessera(tessere,k);
        }
    }
    return;
}


int main(void){
    tessera_t *tessere;
    scacchiera_t **scacchiera,**b_sol;
    int r,c,n;
    tessere=leggitessere(&n);
    scacchiera=leggiscacchiera(&r,&c,tessere);
    b_sol=malloc2d(r,c);
    disp_sempl(scacchiera,tessere,b_sol,r,c,n,0);
    stampa(b_sol,r,c);
    //fare le free
    return 0;
}
