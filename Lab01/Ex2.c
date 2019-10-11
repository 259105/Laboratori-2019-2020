//
// Created by s259105 on 06/10/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Nf 200
#define Np 25
#define maxdiz 30

void ricodifica(char frase[],char codice[][Np+1],char parole[][Np+1],int n,char frase_r[]){
    //in questa soluzione si controlla ogni parola sull'intera frase
    int i,j,y,x,z;
    //i := contatore delle singole parole del dizionario
    //j := contatore che si sposta da carattere in carattere nella frase principale
    //y := contatore che analizza gli l caratteri dopo j per controllare se le parole sono uguali
    //x := contatore usato per 2 scopi diversi: 1) contare i caratteri uguali 2) usato per la sostituzione dell codice
    //z := variabile di supporto usata per ricordarsi dov'era pos.
    int pos=0;//posizione del indice nella frase ricordificata
    int l_frase,l_parole,l_codice;//lunghezze delle stringhe riguardanti la frase,la parola, e il codice
    strcpy(frase_r,frase); //ripristino la frase utilizzata per la riga precedente in quella iniziale
    for(i=0;i<n;i++){//contatore delle parole
        l_frase=strlen(frase);
        l_codice=strlen(codice[i]);
        l_parole=strlen(parole[i]);
        for(j=0;j<l_frase+1;j++){//contatore che si sposta tra i caratteri della frase
            //Ho messo l_frase+1 cosi durante la sostituzione mi si sostituisce anche il \000 cosi da non creare problemi di \n
            for(y=j,x=0;y<j+l_parole;y++){ //contatore che confronta ogni carattere della frase con quello della parola da codificare
                if(parole[i][x]==frase[y]){
                    x++;//Il contatore x lo uso ora per vedere quanti caratteri della frase sono uguali a quelli della parola da sostituire
                    if(x==l_parole){
                        for(z=pos,x=0;pos<z+l_codice;pos++,x++) //adesso il contatore x lo riutilizzo per la sostituzione
                            frase_r[pos]=codice[i][x];
                        j=y+1;//dico di ripartire a contare da subito dopo la parola sostituita per non fare iterazioni inutili
                    }
                }else{
                    frase_r[pos]=frase[j];//se non ho trovato nessuna coincidenza mi sostituisce il carattere nella frase di supporto
                    pos++;
                    y=j+l_parole; //Uscita forzata dal ciclo
                }
            }
        }
        strcpy(frase,frase_r);//una volta controllata la prima parola copio la frase ricodificata nella frase principale cosi da poter cercare sostituzioni in quella ricodificata
        pos=0;//poichè sto facendo un'altro giro con un'altra parola da sostituire imposto la posizione della frase ricodificata a 0
    }
}


int main(){
    char frase[Nf+1],parole[maxdiz][Np+1],codice[maxdiz][Np+1],frase_r[Nf+1];
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
    for(i=0;i<n;i++)
        fscanf(diz,"%s %s",codice[i],parole[i]);

    while(fgets(frase,200,srg)!=NULL){
        ricodifica(frase,codice,parole,n,frase_r);
        fprintf(ric,"%s",frase_r);
    }
    fclose(srg);
}
