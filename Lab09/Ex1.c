//
// Created by s259105 on 11/12/2019.
//
#include <stdio.h>
#include <stdlib.h>
#define file "att.txt"

typedef struct{
    int s,f;
}att;
int leggifile(att **v){
    FILE *fp;
    att *temp;
    int n,i;
    fp=fopen(file,"r");
    if(fp==NULL)
        exit(1);
    fscanf(fp,"%d",&n);
    temp=malloc(n*sizeof(att));
    for(i=0;i<n;i++)
        fscanf(fp,"%d%d",&temp[i].s,&temp[i].f);
    *v=temp;
    fclose(fp);
    return n;
}
int attcmp(att a1,att a2){
    return a1.s-a2.s;
}
void insertionSort(att *v,int n){
    int i,j,l=0,r=n-1;
    att x;
    for(i=l+1;i<=r;i++){
        x=v[i];
        j=i-1;
        while(j>=l && attcmp(x,v[j])<0){
            v[j+1]=v[j];
            j--;
        }
        v[j+1]=x;
    }
}
int inters(att *v,int a1,int a2){
    if(v[a1].s<=v[a2].s && v[a2].s<v[a1].f) //controllo se l'estremo sinitro di A2 è dentro A1
        return 1;
    if (v[a1].s<v[a2].f && v[a2].f<=v[a1].f)//controllo se l'estremo destro di A2 è dentro A1
        return 1;
    return 0; //non interseca
}
int dur(att sol){
    return sol.f-sol.s;
}
//funzione ricorsiva
  /*
int max(int i1,int i2){
    if(i1>i2) return i1;
    return i2;
}
int attSelR(att *v,int i){ // cerco la massima durata dell'sottoproblema
    int k,ris=dur(v[0]); //inizializzio la durata iniziale a quella della prima atività
    for(k=0;k<i;k++) //dall'attività 0 a quella i-esima
        if(!inters(v,k,i)) //controllo che l'attività k-esima non interseca l'attività i-esima
            ris=max(ris,dur(v[k+1])+attSelR(v,k)); // se la durata dell'attività k+1-esima + la durata massima del sottoproblema ottimo è maggiore di quella trovata precedentemente allora sovrascrivlia in ris
    return ris;
}
void attSel(int N, att *v){
    int ris=0,temp;
    for(int i=1;i<N;i++){ // per ogni sottoproblema
        temp=attSelR(v,i); //cerco il massimo attraverso una funzione ricorsiva
        if(temp>ris) ris=temp; //se la soluzione trovata è maggiore di quella precedente allora aggiorno
    }
    printf("\nDurata massima ottenibile: %d\n",ris);
}*/
void printAtt(att a){
    printf("(%d,%d)",a.s,a.f);
}
void attPrint(att *v, int *P, int i){
    if (P[i]==-1){//cond di terminazione
        printAtt(v[i]);
        return;
    }
    attPrint(v,P,P[i]);// Dato che P mi indica l'elemento scelto per la soluzione ottima lo uso per stampare fino ad arrivare alla condizione di terminazione
    printAtt(v[i]);
}
void attSel(int N, att *v){
    //è la stessa di quella ricorsiva ma fatta in modo iterativo
    int ris,*L,*P,last=0;
    //esistono in più iò vettore L := in cui per ogni indice indica la durata massima trova fino a quel momento
    // P: per ogni i-esimo elemento dice in che indice si trova l'elemento che è stato scelto per la soluzione ottima
    L=malloc(N* sizeof(int));
    P=malloc(N* sizeof(int));
    ris=L[0]=dur(v[0]); P[0]=-1;
    for(int i=1;i<N;i++){
        L[i]=dur(v[i]); P[i]=-1;
        for(int j=0;j<i;j++)
            if(!inters(v,j,i) && L[i]<(dur(v[j+1])+L[j])){ //stessa condizione della ricorsiva ma fatta in modo iterativo
                L[i]=dur(v[j+1])+L[j];
                P[i]=j;
            }
        //confronto se la soluzione ottima trovata è maggiore di quella precedente
        if(ris<=L[i]){
            ris=L[i];
            last=i;// è l'indice dell'ultimo elemento aggiunto alla soluzione ottima, serve per ricostrutire la soluzione
        }
    }
    attPrint(v,P,last);// stampo ricorsivamente partendo da las
    printf("\nDurata massima ottenibile: %d\n",ris);
}
int main(void){
    att *v;
    int n;
    n=leggifile(&v);
    printf("HAI INSERITO:\n%d attivita'\n",n);
    insertionSort(v,n); //bisogna avere il vettore delle attività ordinate
    for(int i=0;i<n;i++)
        printf("%d %d\n", v[i].s,v[i].f);
    attSel(n,v);
    free(v);
    return 0;
}
