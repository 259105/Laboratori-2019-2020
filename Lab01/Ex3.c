//
// Created by s259105 on 08/10/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_MATRICE 300
#define MAX_FILE 20
#define MAX_COMADA 100

void inizializza_matrice(int matrice[][MAX_MATRICE],int n);
void apri_file_salva_matrice(int matrice[][MAX_MATRICE],int *nr,int *nc);
void stampa_matrice(int matrice[][MAX_MATRICE],int nr,int nc);
int menu(int *selettore,int *indice,int *direzione,int *posizione);
void ruota(int M[][MAX_MATRICE],int nr,int nc,int selettore, int direzione,int indice,int posizione);

//selettore 1=riga 2=colonna
//direzione -1=destra/su 1=sinistra/giu
int main(void){
    int M[MAX_MATRICE][MAX_MATRICE],nr,nc,selettore,indice,direzione,posizioni;

    inizializza_matrice(M,0);
    apri_file_salva_matrice(M,&nr,&nc);
    stampa_matrice(M,nr,nc);
    while(menu(&selettore,&indice,&direzione,&posizioni)){
        ruota(M,nr,nc,selettore,direzione,indice,posizioni);
        stampa_matrice(M,nr,nc);
    }
}

void inizializza_matrice(int matrice[][MAX_MATRICE],int n){
    int i,j;

    for(i=0;i<MAX_MATRICE;i++){
        for(j=0;j<MAX_MATRICE;j++){
            matrice[i][j]=n;
        }
    }
}

void stampa_matrice(int matrice[][MAX_MATRICE],int nr,int nc){
    int i,j;

    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            printf("%d",matrice[i][j]);
        }
        printf("\n");
    }
}

void apri_file_salva_matrice(int matrice[][MAX_MATRICE],int *nr,int *nc){
    int i,j;
    char file[MAX_FILE];
    FILE *fp;

    printf("Inserisci il nome del file da aprire (MAX 20 caratteri):\n");
    scanf("%s",file);
    while((fp=fopen(file,"r"))==NULL){
        fprintf(stderr,"Errore hai inserito il nome del file errato o troppo grande, riprova\n");
        printf("Inserisci il nome del file da aprire (MAX 20 caratteri):\n");
        scanf("%s",file);
    }

    fscanf(fp,"%d %d",nr,nc);
    for(i=0;i<*nr;i++){
        for(j=0;j<*nc;j++){
            fscanf(fp,"%d",&matrice[i][j]);
        }
    }
}

int menu(int *selettore,int *indice,int *direzione,int *posizione){
    char sel[MAX_FILE],dir[MAX_FILE];
    int i;

        printf("Inserisci comanda  nella forma  <selettore> <indice> <direzione> <posizioni>:\n"
               "<selettore>= 'riga', 'colonna' o 'fine';\n"
               "<indice>= quale indice della riga/colonna vuoi far muovere?\n"
               "<direzione>= 'destra' o 'sinistra' per le righe, 'su' o 'giu' per le colonne;\n"
               "<posizioni>= Inidicare di quante posizioni vuoi far compiere la rotazione.\n");
        scanf("%s", sel);
        if (strcmp(sel, "fine") == 0) {
            return 0;
        }
        scanf("%d %s %d", indice, dir, posizione);
        for (i = 0; i < MAX_FILE; i++) { //Questo serve per non avere problemi di maiuscolo o minuscolo
            sel[i] = tolower(sel[i]);
            dir[i] = tolower(dir[i]);
        }
        if (strcmp(sel, "riga")==0) {
            *selettore = 1;
            if (strcmp(dir, "destra") == 0) {
                *direzione = -1;
                return 1;
            } else if (strcmp(dir, "sinistra")==0) {
                *direzione = 1;
                return 1;
            }
        } else {
            *selettore = 2;
            if(strcmp(dir,"su")==0){
                *direzione=1;
                return 1;
            }else if(strcmp(dir,"giu")==0){
                *direzione=-1;
                return 1;
            }
        }
    return 0;
}

void ruota(int M[][MAX_MATRICE],int nr,int nc,int selettore, int direzione,int indice,int posizione){
    int i,j,V[MAX_MATRICE];
    //Vn è il vettore nuovo ovvero il vettore che contiene la "rotazione"
    //V il vettore iniziale non ruotato
    nc--;nr--;//prendo in considerzione che inizio a contare da 0;
    indice--;// tengo in considerazione che devo contare da 0 in poi



    //selettore 1=riga 2=colonna
    //direzione -1=destra/giu 1=sinistra/su

    if(selettore==1){
        //Riga
        if(posizione>nc){ //Questo serve in caso ci sono dei spostamenti maggiori della matrice stessa
                            //Prendo il resto della divisione rotazione_tot_posizione/lunghezza_riga/colonna
            posizione=posizione%(nc+1);//Faccio +1 perche mi servono le righe effettive e non quelle contate a partire
                                        // da 0.
        }
        if(direzione==1){
            posizione=nc+1-posizione; //Trasformo la direzione da sinistra a destra.
        }
        for(i=0,j=0;i<=nc;i++){          //Prendo il vettore nella matrice che mi interessa
            if(i<=nc-posizione)
                V[i+posizione]=M[indice][i]; //Sposto dal primo fino al n-spostamento
            else {
                V[j] = M[indice][i]; // sposto dal n-spostamento all'ultimo
                j++;
            }
        }
        for(i=0;i<=nc;i++){ // Ricopio il vettore creato
            M[indice][i]=V[i];
        }
    }else{
        //Colonna
        if(posizione>nr){
            posizione=posizione%(nr+1);//Faccio +1 perche mi servono le righe effettive e non quelle contate a partire
            // da 0.
        }
        if(direzione==1){
            posizione=nr+1-posizione; //Trasformo la direzione da su a giu.
        }
        for(i=0,j=0;i<=nr;i++){          //Prendo il vettore nella matrice che mi interessa
            if(i<=nr-posizione)
                V[i+posizione]=M[i][indice]; //Sposto dal primo fino al n-spostamento
            else {
                V[j] = M[i][indice]; // sposto dal n-spostamento all'ultimo
                j++;
            }
        }
        for(i=0;i<=nr;i++){ // Ricopio il vettore creato
            M[i][indice]=V[i];
        }
    }
}
