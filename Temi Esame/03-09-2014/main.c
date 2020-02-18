//
// Created by s259105 on 18/02/2020.
//

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char** argv){
    if(argc!=6) exit(1);
    FILE *fn,*fs,*fo;
    fn=fopen(argv[1],"r");
    fs=fopen(argv[2],"r");
    fo=fopen(argv[3],"w");
    if(fn==NULL || fs==NULL || fo==NULL) exit(2);
    Graph G=GRAPHload(fn);
    int k=atoi(argv[4]),m=atoi(argv[5]);

    if(GRAPHchecksol(G,fs,k,m)) printf("La soluzione rispetta i vincoli.\n");
    else printf("La soluzione NON rispetta i vincoli.\n");
    GRAPHnetvincoled(G,fo,k,m);

    GRAPHfree(G);
    fclose(fn);fclose(fs);fclose(fo);
    return 0;
}
