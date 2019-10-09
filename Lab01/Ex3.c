//
// Created by s259105 on 08/10/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_MATRICE 300
#define MAX_FILE 20

void inizializza_matrice(int matrice[][MAX_MATRICE],int n);
void apri_file_salva_matrice(int matrice[][MAX_MATRICE],int *nr,int *nc);
void stampa_matrice(int matrice[][MAX_MATRICE],int nr,int nc);
int menu(int *selettore,int *indice,int *direzione,int *posizione);
void ruota(int M[][MAX_MATRICE],int n,int selettore, int direzione,int indice,int posizione);

//selettore 1=riga 2=colonna
//direzione -1=destra/su 1=sinistra/giu
int main(void){
    int M[MAX_MATRICE][MAX_MATRICE],nr,nc,selettore,indice,direzione,posizioni;

    inizializza_matrice(M,0);
    apri_file_salva_matrice(M,&nr,&nc);
    stampa_matrice(M,nr,nc);
    while(menu(&selettore,&indice,&direzione,&posizioni)){
        if(selettore==1)
            ruota(M,nc,selettore,direzione,indice,posizioni);
        else
            ruota(M,nr,selettore,direzione,indice,posizioni);
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
        for (i = 0; i < MAX_FILE; i++) {
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

void ruota(int M[][MAX_MATRICE],int n,int selettore, int direzione,int indice,int posizione){
    int i,j,V[MAX_MATRICE];
    //Vn è il vettore nuovo ovvero il vettore che contiene la "rotazione"
    if(posizione>n){
        posizione=posizione%(n);
    }
    if(direzione==1){
        posizione=n-posizione; //Trasformo la direzione da su a giu oppure da sinistra a destra
    }
    n--;//cosi è il numero di righe se comincio a contare da 0.
    indice--;// tengo in considerazione che devo contare da 0 in poi

    //selettore 1=riga 2=colonna
    //direzione -1=destra/giu 1=sinistra/su
    for(i=0,j=0;i<=n;i++){          //Prendo il vettore nella matrice che mi interessa
        if(i<=n-posizione)
            if(selettore==1)        //Sposto dal primo fino al n-spostamento
                V[i+posizione]=M[indice][i];
            else
                V[i+posizione]=M[i][indice];
        else {
            if(selettore==1) // sposto dal n-spostamento all'ultimo
                V[j] = M[indice][i];
            else
                V[j] = M[i][indice];
            j++;
        }
    }
    for(i=0;i<=n;i++){// Ricopio il vettore creato
        if(selettore==1)
            M[indice][i]=V[i];
        else
            M[i][indice]=V[i];
    }
}
