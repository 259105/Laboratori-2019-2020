//
// Created by s259105 on 15/10/2019.
//
/*
 * In questo esercizio leggo le sequenze e le salvo in un vettore di strutture, trasformando tutto in minuscolo per non
 * avere problemi. Leggo il file testo.txt una sola volta leggendo una parola alla volta attraverso la funzione "myfscanf"
 * (svolge lo stesso compito della %s fscanf, ma appena trova uno spazio o un segno di punteggiatura si ferma).
 * Controllo per ogni parola se contiene una sequenza, se si, mi salvo nella struct la parola stessa e in che posizione si trova
 * attaverso un contatore di parole nel testo.
 * Finisco di cercare occorrenze se: 1) non ci sono più parole contenenti sequenze 2) le parole trovate sono più di 10.
 * Il 2° viene fatto attraverso un'altro contatore che si incrementa ogni volta che trovo un'occorenza.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define mparola 25
#define mseq 20
#define mseqchar 5
#define moccor 10

typedef struct {
    int pos[moccor];
    char parolatrovata[moccor][mparola],sequenza[mseqchar];
}sequenze_s;

void minuscolo(char parola[]){
    int i,l_parola;
    l_parola=strlen(parola);
    for(i=0;i<l_parola;i++){
        parola[i]=tolower(parola[i]);
    }
}

int myfscanf(FILE *ft,char parola[],int *l){
    /*
     * Prendo carattere per carattere e lo inserisco nella i-esima posizione della stringa parola[i],appena trovo un
     * carattere non alfanumerico, esco dal ciclo e sostituisco il valore appena trovato con '\000';
     * Ripeto questa operazione finche non trovo una stringa lunga almeno 1 char, faccio questo controllo perche capita
     * di leggere un solo spazio o un solo segno di punteggiatura che mi avrebbero tornato una lunghezza =0;
     */
    char alfanum;
    int i;
    do {
        i=0;
        do {
            if ((fscanf(ft, "%c", &alfanum)) == 1) {
                alfanum = tolower(alfanum);
                parola[i] = alfanum;
                i++;
            } else {
                return 0;
            }
        } while (isalnum(alfanum));
        parola[i - 1] = '\000';
        *l = i - 1;
    }while (*l==0);
    return 1;
}

void stampa(sequenze_s sequenze[],int contatore[],int n){
    int i,j;
    for(i=0;i<n;i++){
        if(contatore[i]>0){
            printf("\n\nLa sequenza \"%s\" e' contenuta in:\n ",sequenze[i].sequenza);
            for(j=0;j<contatore[i];j++){
                    printf("%s (parola in posizione %d nel testo),\n ",sequenze[i].parolatrovata[j],sequenze[i].pos[j]);
            }
        }else{
            printf("\n\nLa sequenza \"%s\" non e' contenuta in nessuna parola.\n",sequenze[i].sequenza);
        }
    }
}

int main() {
    int n,i,x,l_parola,l_seq,cont=1,k=0,contiene=0;
    int contatore[mseq]={0};
    char parola[mparola];
    FILE *ft,*fs;
    sequenze_s sequenze[mseq];

    /*
     * contatore := conta quante occorreze sono state trovare, se sono +10 non ne cerca più per quella singola sequenza
     * cont := conta le parole nel testo
     */
    if((ft=fopen("testo.txt","r"))==NULL || (fs=fopen("sequenze.txt","r"))==NULL){
        fprintf(stderr,"Errore apertura file");
        return 1;
    }
    fscanf(fs,"%d",&n);
    for(i=0;i<n;i++){
        fscanf(fs,"%s",sequenze[i].sequenza);
        minuscolo(sequenze[i].sequenza);
    }
    /*
     * i := contatore delle sequenze
     * x := conta carattere per carattere nella parola per confrontarla con l'la sequenza.
     * k := usato per confrontare parola e sequenza
     */
    while(myfscanf(ft,parola,&l_parola)){
        for(i=0;i<n;i++){
            if(contatore[i]<10) {
                l_seq = strlen(sequenze[i].sequenza);
                for (x = 0; x <= l_parola - l_seq && !contiene; x++) {
                    k=0;
                      do {
                        if (parola[x+k] == sequenze[i].sequenza[k]) {
                            if (k == l_seq-1) { //perche l_seq inizia a contare da 1
                                contiene = 1;
                            }
                            k++;
                        }else{
                            k=l_seq; // uscita forzata dal ciclo
                        }
                    }while(k<l_seq);
                }
                if (contiene) {
                    sequenze[i].pos[contatore[i]] = cont;
                    strcpy(sequenze[i].parolatrovata[contatore[i]], parola);
                    contatore[i]++;
                    contiene = 0;
                }
            }
        }
        cont++;
    }
    stampa(sequenze,contatore,n);
    return 0;
}
