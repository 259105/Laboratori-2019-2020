//
// Created by s259105 on 18/11/2019.
//

#include <stdlib.h>
#include <stdio.h>
#define N_FILE "grafo.txt"

typedef struct archi{
    int u;
    int v;
}ARCHI;
int leggifile(int *pN,int *pE,ARCHI **pArchi){
    FILE *fp;
    int i;
    if((fp=fopen(N_FILE,"r"))==NULL){
        fprintf(stderr,"Errore apertura file");
        return 1;
    }
    fscanf(fp,"%d%d",pN,pE);
    //Alloco dinamicamente il vettore di strutture
    if((*pArchi=(ARCHI*)malloc((*pE)* sizeof(ARCHI)))==NULL){
        fprintf(stderr,"Errore memoria non allocata");
        return 1;
    }
    for(i=0;i<*pE;i++){
        fscanf(fp,"%d%d",&((*pArchi)[i].u),&((*pArchi)[i].v));
        printf("%d%d\n",(*pArchi)[i].u,(*pArchi)[i].v);//visualizzo gli archi
    }
    fclose(fp);
    return 0;
}
void stampa(int *sol,int k){
    int i;
    printf("{ ");
    for(i=0;i<k;i++)
        printf("%d ",sol[i]);
    printf("}\n");

}
int accettazione(int *sol,ARCHI *archi,int k,int E,int i,int cont){
    int j;
    if(i==E)// se sono arrivato alla fine, cioè non ci sono più archi da confrontare
        return cont;
    for(j=0;j<k;j++){//per ogni nodo della soluzione controllo se appartiene al'arco
        // appena trovo una uguaglianza fermo il ciclo e ricorro al arco successivo
        if(sol[j]==archi[i].u){
            cont++;
            break;
        }
        //uso break per creare la condizione di  or esclusivo (xor)
        else if(sol[j]==archi[i].v){
            cont++;
            break;
        }
    }
    return accettazione(sol,archi,k,E,i+1,cont); // sarà poi compito del powerset capire se count è uguale ad E
}
void powerset(int pos,int *sol,ARCHI *archi,int start,int k,int N,int E){
    int i,cont=0;
    if(pos>=k){
        if(k!=N-1){//tutti gli insiemi fatti da N-1 nodi sono vertex cover
            cont=accettazione(sol,archi,k,E,0,0);
        }
        if(cont==E || k>=N-1) // se il contatore è uguale al numero di archi allora è vertex cover
            stampa(sol,k);
        return;
    }
    for(i=start;i<N;i++){
        sol[pos]=i;
        powerset(pos+1,sol,archi,i+1,k,N,E);
    }
}

int main(void){
    int N,E;
    int *sol;
    ARCHI *archi=NULL;
    int i=0;

    if(leggifile(&N,&E,&archi))
        return 1;
    sol=malloc(N*sizeof(int));
     /* per la risoluzione del problema si cercano tutte le soluzioni possibili con un powerset a combinazioni semplici
     * e poi vengono scelte quelle che soddisfano un certo criterio
     */
    for(i=E-N+2;i<=N;i++)//perche tutti gli insiemi di cardinalità minore di E-N+2 non sono vertex cover
        powerset(0,sol,archi,0,i,N,E);
    return 0;
}
