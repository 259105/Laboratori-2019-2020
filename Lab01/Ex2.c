//
// Created by s259105 on 06/10/2019.
// Finished on 08/10/2019
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Nf 200
#define Np 25
#define maxdiz 30

void ricodifica(char frase[],char codice[][Np+1],char parole[][Np+1],int n);
int cerca(char parole[][Np+1],char frase[],int n,int pos);
int sostituisci(int pos, char frase[],char parola[][Np+1],char ricod[][Np+1],int n);

int main(){
    char frase[Nf+1],parole[maxdiz][Np+1],codice[maxdiz][Np+1];
    int i,n;
    FILE *srg, *ric, *diz;

    if((srg=fopen("sorgente.txt","r"))==NULL){
        fprintf(stderr,"Errore apertura file SORGENTE");
        return 0;
    }
    if((ric=fopen("ricodificato.txt","w"))==NULL){
        fprintf(stderr,"Errore apertura file di scrittura.");
        return 0;
    }
    if((diz=fopen("dizionario.txt","r"))==NULL){
        fprintf(stderr,"Errore apertura file DIZIONARIO");
        return 0;
    }

    fscanf(diz,"%d",&n);
    for(i=0;i<n;i++){
        fscanf(diz,"%s %s",codice[i],parole[i]);
    }

    while(fgets(frase,200,srg)!=NULL){
        ricodifica(frase,codice,parole,n);
        fprintf(ric,"%s",frase);
    }
    fclose(srg);
}

void ricodifica(char frase[],char codice[][Np+1],char parole[][Np+1],int n){
    int i,posizione=0;
    for(i=0;i<n;i++){//Questo contatore lo uso per cambiare ogni volta parola da controllare nella frase
                    //Faccio un ciclo while cosi da poter controllare più volte la stessa parola nella stessa frase
                    //il while finisce quando non si trovano sostituzioni.
        while ((posizione = cerca(parole, frase,i,posizione))) {//Passo anche la posizone cosi quando va a continuare
                                                                //il nuovo ciclo non riparte da zero ma continua con la
                                                                //scansione iniale, facendo cosi si riduce di molto il
                                                                //numero di iterazioni
            sostituisci(posizione, frase, parole, codice,i);
        }
    }
}

int cerca(char parole[][Np+1],char frase[],int n,int pos){
    int i,j,k,l_frase,l_parola;
    //i=cont. che mi indica in che indice mi trovo nella stringa "frase"
    //j parte da i e itera per tante volte quanto è lunga la "parola" da trovare, questo mi serve per confrontare
    //la sottostringa con la parola del dizionario, che viene invece contata lettera per lettera da k.
    l_frase=strlen(frase);
    l_parola=strlen(parole[n]);


    for(i=pos;i<=(l_frase-l_parola);i++){ //la condizione l'ho scelta cosi nonostante esce fuori dall sotto-vettore di
                                                    //interesse per evitare eventuale errori di tipo \n o \0
        for(j=i,k=0;j<=i+l_parola-1;j++) { //-1 perche il contatore parte da 0, mentre la lunghezza della parola è
                                            //contata partendo da 1
            if(parole[n][k]==frase[j]){
                k++;
                if(k==l_parola){
                    return i;  //restituisco il contatore i che mi indica quando inzia la parte di parola da sostituire
                }
            }
        }
    }
    return 0;
}

int sostituisci(int pos, char frase[],char parola[][Np+1],char ricod[][Np+1],int n){
    int i,j,l_ricod,l_parola;
    char frase_supporto[Nf];
    //i= usato come cont. nella stringa "frase"
    //j= usato come cont. nella stringa "sostituzione"

    strcpy(frase_supporto,frase); //mi salvo la frase per non avere perdita di dati, come ad esempio avere una
                                //sostituzione troppo lunga può provocare perdita di dati.
    l_ricod=strlen(ricod[n]);
    l_parola=strlen(parola[n]);

    for(i=pos,j=0;j<l_ricod;i++,j++){ //sostituisco la parte di parola con il codice
        frase[i]=ricod[n][j];
    }
    while (i<Nf){  //proseguo sempre dallo stesso indice i fino a fine vettore copiando la frase di supporto.
        frase[i]=frase_supporto[i-l_ricod+l_parola];
        i++;
    }
    return 1;
}
