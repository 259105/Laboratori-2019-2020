//
// Created by s259105 on 21/12/2019.
//
#include <stdio.h>

#include "matrici.h"
#include "pietre.h"
//serve per trovare il minimo
int min(int n,int n1){
    if(n<n1) return n;
    return n1;
}

int fZ(M m,P p);
int fR(M m,P p);
int fS(M m,P p);
int fT(M m,P p);
//Queste seguenti sono funzioni wrapper che servono a collegare l'ADT di 1a classe PIETRE con il quasi ADT MATRICI
//Non volevo "sporcare" matrici.c facendolo dipendere da pietre.h (ho pensato che potrei riutilizzarlo senza le pietre)
M WMinit(P p){
    return Minit(Pz(p)+1,Ps(p)+1,Pr(p)+1,Pt(p)+1);
}
void WMfree(M m,P p){
    Mfree(m,Pz(p)+1,Ps(p)+1,Pr(p)+1);
}
void WMinsert(int ****m,P p,int val){
    Minsert(m,Pz(p),Ps(p),Pr(p),Pt(p),val);
}
int WMextract(int ****m,P p){
    return Mextract(m,Pz(p),Ps(p),Pr(p),Pt(p));
}
void WMprint(int ****m,P p){
    Mprint(m,Pz(p)+1,Ps(p)+1,Pr(p)+1,Pt(p)+1);
}
//avevo intezione di metterele in un file link.h per non farle vedere nel main
//
int fZ(M m,P p){
    int P=Ptot(p),lz=0,lr=0;
    if(P==0)
        return 0; //se non ho più pietre ritorno 0

    if(WMextract(m->MZ,p)!=0) //se ho gia calcolato la pietra che inizia con z e che ha quelle pietre rimanenti
        lz=WMextract(m->MZ,p); // allora riutilizzo il calcolo fatto
    else if(Pz(p)>0) // se non l'ho ancora calcolato
        lz=1+fZ(m,Pdup_insert_remove(p,z,-1)); // allora mi calcolo la lunghezza massima della collana che si potrebbe avere
                                                // se iniziassi con uno zaffiro (per questo rimuovo uno zaffiro nella
                                                // collana chiamata in ricorsione), alla lunghezza massima trovata aggiungo 1
                                                // che sarebbe lo zaffiro iniziale

    if(WMextract(m->MR,p)!=0) //viene fatto lo stesso ragionamento ma con il rubino
        lr=WMextract(m->MR,p);
    else if(Pr(p)>0)
        lr=1+fR(m,Pdup_insert_remove(p,r,-1));

    if (lz>lr){ // scelgo tra le 2 lunghezze massime trovate quella massima
        WMinsert(m->MZ,p,lz); //la massima trovata la inserisco nella rispettiva matrice
        return lz;              //ritorno il valore trovato
    }else{
        WMinsert(m->MZ,p,lr);
        return lr;
    }
}
int fT(M m,P p){
    int P=Ptot(p),lz=0,lr=0;
    if(P==0)
        return 0;

    if(WMextract(m->MZ,p)!=0)
        lz=WMextract(m->MZ,p);
    else if(Pz(p)>0)
        lz=1+fZ(m,Pdup_insert_remove(p,z,-1));

    if(WMextract(m->MR,p)!=0)
        lr=WMextract(m->MR,p);
    else if(Pr(p)>0)
        lr=1+fR(m,Pdup_insert_remove(p,r,-1));

    if (lz>lr){
        WMinsert(m->MT,p,lz);
        return lz;
    }else{
        WMinsert(m->MT,p,lr);
        return lr;
    }
}
int fR(M m,P p){
    int P=Ptot(p),ls=0,lt=0;
    if(P==0)
        return 0;

    if(WMextract(m->MS,p)!=0)
        ls=WMextract(m->MS,p);
    else if(Ps(p)>0)
        ls=1+fS(m,Pdup_insert_remove(p,s,-1));

    if(WMextract(m->MT,p)!=0)
        lt=WMextract(m->MT,p);
    else if(Pt(p)>0)
        lt=1+fT(m,Pdup_insert_remove(p,t,-1));

    if (ls>lt){
        WMinsert(m->MR,p,ls);
        return ls;
    }else{
        WMinsert(m->MR,p,lt);
        return lt;
    }
}
int fS(M m,P p){
    int P=Ptot(p),ls=0,lt=0;
    if(P==0)
        return 0;

    if(WMextract(m->MS,p)!=0)
        ls=WMextract(m->MS,p);
    else if(Ps(p)>0)
        ls=1+fS(m,Pdup_insert_remove(p,s,-1));

    if(WMextract(m->MT,p)!=0)
        lt=WMextract(m->MT,p);
    else if(Pt(p)>0)
        lt=1+fT(m,Pdup_insert_remove(p,t,-1));

    if (ls>lt){
        WMinsert(m->MS,p,ls);
        return ls;
    }else{
        WMinsert(m->MS,p,lt);
        return lt;
    }
}

int main(void){
    M m=NULL;
    P p;
    int l[NP],max=0,sol;
    p=Pinit_insert(3,3,3,2);

    sol=Pz(p)+Ps(p)+min(Pr(p),Pt(p))*2+1;//formula che ho usato nel lab7ex1 per trovare la lunghezza

    m=WMinit(p);
    //WMprint(m->MZ,p);printf("\n");
    //chiama le 4 fuzioni
    l[z]=fZ(m,p);
    l[s]=fS(m,p);
    l[r]=fR(m,p);
    l[t]=fT(m,p);
    // e confronto i risultati, prendendo il massimo
    for(int i=0;i<NP;i++)
        if(l[i]>max)
            max=l[i];
    //stapo facendo il confronto con la MIA formula
    printf("%d %s",max,sol==max? "e' giusto\n":"e' sbagliato\n");  //confronto per vedere se è giusto o sbagliato
    //dai diversi test ho scoperto che a formula non funziona se ho 4 pietre in ugual quantità
    WMfree(m,p);//Dealloco tutto
    Pfree(p);

    return 0;
}
