//
// Created by s259105 on 19/01/2020.
//
#include <stdio.h>
#include "titoli.h"
#include "quotazioni.h"
#include "data.h"

void loadfile(titoli T){
    FILE *fp;
    titolo t;
    int term=1,n,valore,quantita;
    char nomefile[maxchar+1],cod[maxchar+1],data[11],ora[6];
    do{
        fprintf(stdout,"Inserisci nome File input:");
        fscanf(stdin,"%s",nomefile);
        fp=fopen(nomefile,"r");
        if(fp==NULL) {
            fprintf(stderr, "Errore apertura file");
            term=0;
        }
    }while(!term);
    while (fscanf(fp,"%s %d",cod,&n)==2){
        t=TITOLIinsertW(T,cod);
        for(int i=0;i<n;i++){
            fscanf(fp,"%s %s %d %d",data,ora,&valore,&quantita);
            TITOLOinsert(t,QUOTAZIONEinit(valore,quantita,DATAinit(data,ora)));
        }
    }

}

int main(void){
    titoli T;
    data d,d1;
    quotazione q;
    quotazioni Q;
    int term=0,cmd,soglia;
    char info1[maxchar];

    T=TITOLIinit();

    while(!term){
        fprintf(stdout,"Menu':\n"
                       "1 - Apri file;\n"
                       "2 - Quotazione di un titolo in una certa data;\n"
                       "3 - Quotazione minima e massima di un titolo in un intervallo di date;\n"
                       "4 - Quotazione minima e massima di un titolo;\n"
                       "5 - Bilancia albero di un titolo;\n"
                       "6 - Termina.\n");
        fscanf(stdin,"%d",&cmd);
        switch (cmd){
            case 1:
                loadfile(T);
                break;
            case 2:
                fprintf(stdout,"Inserisci codice titolo e data in formato gg/mm/aaaa:\n");
                fscanf(stdin,"%s %d/%d/%d",info1,&d.giorno,&d.mese,&d.anno);
                if((q=QUOTAZIONIsearch(QbyT(TITOLIsearch(T,info1)),d)).n!=0)
                    QUOTAZIONEprint(stdout,q);
                else
                    fprintf(stderr,"Quotazione non trovata\n");
                break;
            case 3:
                fprintf(stdout,"Inserisci codice titolo e intervallo date in formato gg/mm/aaaa:\n");
                fscanf(stdin,"%s %d/%d/%d %d/%d/%d",info1,&d.giorno,&d.mese,&d.anno,&d1.giorno,&d1.mese,&d1.anno);
                QUOTAZIONIsearchIntervalPrintMaxMin(QbyT(TITOLIsearch(T,info1)),d,d1,stdout);
                break;
            case 4:
                //è una variante dell'esercizio 3 ma con intervallo tutto il tempo
                fprintf(stdout,"Inserisci codice titolo:\n");
                fscanf(stdin,"%s",info1);
                d.anno=0,d.mese=0;d.giorno=0;
                Q=QbyT(TITOLIsearch(T,info1));
                QUOTAZIONIsearchIntervalPrintMaxMin(Q,d,QUOTAZIONImaxdataW(Q),stdout);
                break;
            case 5:
                fprintf(stdout,"Inserisci codice titolo e soglia minima per effettuare il bilanciamento:\n");
                fscanf(stdin,"%s %d",info1,&soglia);
                if(BilanciamentoSoglia(QbyT(TITOLIsearch(T,info1)),soglia))
                    fprintf(stdout,"Bilanciamento effettuato\n");
                else fprintf(stdout,"Bilanciamento non effettuato\n");
                break;
            case 6:
                term=1;
                break;
        }
    }
    TITOLIfree(T);
    return 0;
}
