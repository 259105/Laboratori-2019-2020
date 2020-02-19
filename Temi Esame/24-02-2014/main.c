//
// Created by s259105 on 19/02/2020.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"

int main(int argc,char** argv){
    if(argc!=2) exit(1);
    FILE *fg;
    fg=fopen(argv[1],"r");
    if(fg==NULL) exit(2);
    Graph G=GRAPHload(fg);

    if(GRAPHcheckregolarita(G)) printf("Il grafo e' regolare.\n");
    else printf("Il grafo NON e' regolare.\n");

    char cmd[MAXC];
    printf("Inserisci vertice sorgente (\"fine\" per terminare):\n");
    scanf("%s",cmd);
    while (strcmp(cmd,"fine")!=0){
        GRAPHpathmax(G,cmd);
        printf("Inserisci vertice sorgente (\"fine\" per terminare):\n");
        scanf("%s",cmd);
    }

    GRAPHfree(G);
    fclose(fg);
    return 0;
}
