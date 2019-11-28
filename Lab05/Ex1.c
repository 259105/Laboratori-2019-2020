//
// Created by s259105 on 10/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define file "brani.txt"
#define l_canzone 256
#define n_proposte 5

typedef struct{
    char **canzoni;
    int n_canzoni;
}PROPOSTE_S;

int A;
char **malloc2dR(int nr,int nc){
    char **m;
    int i;
    m=malloc(nr*sizeof(char *));
    for(i=0;i<nr;i++){
        m[i]=malloc(nc* sizeof(char));
    }
    return m;
}
void free2dR(PROPOSTE_S *p){
    int i,j;
    for(i=0;i<A;i++){
        for(j=0;j<p[i].n_canzoni;j++){
            free(p[i].canzoni[j]);
        }
        free(p[i].canzoni);
    }
    free(p);
}
PROPOSTE_S* leggiFile(void){
    FILE *fp;
    PROPOSTE_S *proposte;
    int C;
    int i,j;
    char nome_canzone[l_canzone];
    //int l_c;

    if((fp=fopen(file,"r"))==NULL){
        fprintf(stderr,"Errore lettura file, File non trovato.\n");
        return NULL;
    }

    fscanf(fp,"%d",&A);
    proposte=(PROPOSTE_S *)malloc(A* sizeof(PROPOSTE_S)); //alloco memoria per creare vettore di strutture
    //alcoritmo cubico
    for(i=0;i<A;i++){
        fscanf(fp,"%d",&C);
        proposte[i].n_canzoni=C;
        if(C>n_proposte){
            fprintf(stderr,"Errore la %d persona ha scelto piu' di %d canzoni",i,n_proposte);
            return NULL;
        }
        proposte[i].canzoni=(char **)malloc(C* sizeof(char *)); //alloco memoria per create vettore di puntatori
        for(j=0;j<C;j++){
            fscanf(fp,"%s",nome_canzone);
            proposte[i].canzoni[j]=strdup(nome_canzone);//strdup fa tutte le operazioni di sotto

            /*l_c=strlen(nome_canzone)+1;
            proposte[i].canzoni[j]=(char *)malloc(l_c* sizeof(char)); //è molto costoso in ambito di complessità
            strcpy(proposte[i].canzoni[j],nome_canzone);// alloco solo la memoria che mi serve per la canzone
            */
             }
    }
    return proposte;
}
int playlist(int pos,PROPOSTE_S *proposte,char **sol,int count){
    //uso il principio di moltiplicazione
    int i=0;
    if(pos>=A){
        for(i=0;i<A;i++){
            printf("%s",sol[i]);
            printf("\n");
        }
        printf("\n");
        return count+1;
    }
    for(i=0;i<proposte[pos].n_canzoni;i++){
        sol[pos]=proposte[pos].canzoni[i];
        count=playlist(pos+1,proposte,sol,count);
    }
    return count;
}
/*void stampastruttura(PROPOSTE_S *s){
    int i,j;
    for(i=0;i<A;i++){
        for(j=0;j<s[i].n_canzoni;j++){
            printf("%s\n",s[i].canzoni[j]);
        }
        printf("\n");
    }
}
 */
int main(void){
    PROPOSTE_S *proposte=NULL;
    char **sol;
    int count=0;

    if((proposte=leggiFile())==NULL)
        return 1;
    //stampastruttura(proposte);
    sol=malloc(A*sizeof(char)*l_canzone);
    count=playlist(0,proposte,sol,count);
    printf("%d",count);
    free2dR(proposte);
    return 0;
}
