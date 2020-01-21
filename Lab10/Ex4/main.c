//
// Created by s259105 on 08/01/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int contariarchi(FILE *fp){
    int e=0,n;
    char a[30],b[30],c[30],d[30];
    fscanf(fp,"%s %s %s %s %d",a,b,c,d,&n);
    while (fscanf(fp,"%s %s %s %s %d",a,b,c,d,&n)==5) e++;
    e++;
    rewind(fp);
    return e;
}



void menu(Graph G){
    int cmd,end=0;
    while(end==0){
        fprintf(stdout,"Inserisci comando: \n"
                       "1 - Verifica se 3 vertici sono adiacenti (V. MADJ);\n"
                       "2 - Verifica se 3 vertici sono adiacenti (V. LADJ);\n"
                       "3 - Genera LADJ;\n"
                       "4 - Termina.\n");
        fscanf(stdin,"%d",&cmd);
        switch (cmd){
            case 1: if(GRAPHadiacentiMadj(G)) printf("Sono adiacenti.\n");
                    else printf("NON sono adiacenti.\n");
                break;
            case 2:  if(!GRAPHverifiaLadj(G)){ printf("Lista delle adiacenze non ancora creata.\n"); break;}
                    if(GRAPHadiacentiLadj(G)) printf("Sono adiacenti.\n");
                    else printf("NON sono adiacenti.\n");
                break;
            case 3: GRAPHladj(G);
                break;
            case 4: end=1;
                break;
            default: printf("Errore comando inserito non valido.\n");
        }
    }

}

int main(int argv,char *argc[]){
    FILE *fp;
    int E;
    Graph G;
    if(argv!=2){
        fprintf(stderr,"Errore numero di argomenti\n");
        exit(1);
    }
    fp=fopen(argc[1],"r");
    if(fp==NULL){
        fprintf(stderr,"Errore apertura file\n");
        exit(1);
    }
    E=contariarchi(fp);
    G=GRAPHload(fp,E*2);
    GRAPHstore(G,stdout);//stampa in ordine alfabetico
    menu(G);
    GRAPHfree(G);
    return 0;
}
