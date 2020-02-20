//
// Created by s259105 on 19/02/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc,char** argv){
    if(argc!=4) exit(1);
    FILE *fg;
    fg=fopen(argv[1],"r");
    if(fg==NULL) exit(2);
    int m=atoi(argv[3]);
    Graph G=GRAPHload(fg);

    GRAPHstore(G,stdout);//punto 1
    GRAPHpathsempl(G,argv[2]); //punto 2
    GRAPHbestpath(G,argv[2],m);  //punto 3

    GRAPHfree(G); fclose(fg);
    return 0;
}
