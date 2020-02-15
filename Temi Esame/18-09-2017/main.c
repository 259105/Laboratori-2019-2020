//
// Created by s259105 on 15/02/2020.
//
#include <stdlib.h>
#include "Foresta.h"
#include "Soluzione.h"

int main(int argc,char** argv){
    if(argc!=5) exit(1);
    FILE *fk,*ff,*fe,*fs;
    Foresta F;
    Sol *sol;

    fk=fopen("habitat.txt","r");
    ff=fopen("fimilies.txt","r");
    fe=fopen("enimies.txt","r");
    fs=fopen("solution.txt","r");
    if(fk==NULL || ff==NULL || fe==NULL || fs==NULL)
        exit(2);
    F=FORESTAload(fk,ff,fe,argv[1],argv[2],argv[3],argv[4]);
    sol=SOLvettload(fs,FORESTAkoala(F));

    if(check(F,sol)) printf("La soluzione caricata rispetta i vincoli.\n");
    else printf("La soluzione caricata NON rispetta i vincoli.\n");
    bestalloc(F);

    SOLvettfree(sol);
    FORESTAfree(F);
    fclose(fk);fclose(ff);fclose(fe);fclose(fs);
    return 0;
}
